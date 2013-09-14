/**
 * @file   Main.cpp
 * @author Bastien Brunnenstein
 */

#include <exception>

#include <SFML/Graphics.hpp>

#include "Config.hpp"

#include "screens/Screen.hpp"
#include "screens/IntroScreen.hpp"
#include "screens/PauseScreen.hpp"
#include "screens/ExceptionScreen.hpp"

#include "resources/Async.hpp"
#include "resources/Manager.hpp"

#ifndef NDEBUG
#include <iostream>
#include <iomanip>
#endif

int main(int argc, char ** argv)
{
    Config::load();

    // Start resources system
    Async::initialize();

    // Create first screen : Intro
    Screen * current_screen = new IntroScreen();

    // Prepare render window
    sf::RenderWindow window;

    // Pause screen
    bool pause_screen_active = false;

    // Prevent recursive exceptions
    bool exception_happened = false;

#ifndef NDEBUG
    // Total runtime FPS counter
    sf::Clock total_clock;
    unsigned total_fps_counter = 0;

    // Performance counters
    sf::Time perf_event;
    sf::Time perf_update;
    sf::Time perf_draw;
    sf::Time perf_display;
#endif

    // Handle window restart (to change resolution, set to fullscreen...)
    bool restart = true;
    while (restart)
    {
        restart = false;

        // Create window
        window.create(sf::VideoMode(Config::width, Config::height), WINDOW_TITLE,
                      Config::fullscreen ? sf::Style::Fullscreen : (Config::borderless ? sf::Style::None : sf::Style::Titlebar | sf::Style::Close));
        window.setKeyRepeatEnabled(false);
        window.setMouseCursorVisible(false);
        window.setVerticalSyncEnabled(WINDOW_VSYNC);
        window.setFramerateLimit(WINDOW_FRAMERATE);
        {
            // Load icon, then free the sf::Image
            sf::Image icon;
            icon.loadFromFile(WINDOW_ICON);
            window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }

        // Normalize view to default size, avoiding a lot of work to handle other resolutions
        // On the other hand, reduces the quality when the default resolution is not used
        window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));

        // TODO Make the view ratio independent and draw black borders ?

        // Start global clock
        sf::Clock global_clock;
        sf::Time time_last_frame;

#ifndef NDEBUG
        // FPS counter
        sf::Clock fps_clock;
        unsigned fps_counter = 0;
#endif

        // Main loop
        while (window.isOpen())
        {
            try
            {
#ifndef NDEBUG
                perf_event -= total_clock.getElapsedTime();
#endif

                // Events
                sf::Event event;
                while (window.pollEvent(event))
                {
                    switch(event.type)
                    {
                    case sf::Event::KeyPressed:

                        // Toggle pause with PAUSE_KEY
                        if (!pause_screen_active && Config::pause_enabled
                            && event.key.code == PAUSE_KEY)
                        {
                            current_screen = new PauseScreen(current_screen);
                            pause_screen_active = true;
                            continue;
                        }

                        // Exit with Alt+F4
                        if (event.key.code == sf::Keyboard::F4 && event.key.alt)
                        {
                            window.close();
                            continue;
                        }

                        current_screen->onKeyPressed(event.key.code);
                        break;

                    // Pause automatically if the focus is lost
                    case sf::Event::LostFocus:
                        if (!pause_screen_active && Config::pause_enabled)
                        {
                            current_screen = new PauseScreen(current_screen);
                            pause_screen_active = true;
                        }
                        break;

                    // Quit if the window is closed
                    case sf::Event::Closed:
                        window.close();
                        break;

                    default:
                        break;
                    }
                }

#ifndef NDEBUG
                perf_event += total_clock.getElapsedTime();
#endif


                // Handle clock
                sf::Time time_now = global_clock.getElapsedTime();
                sf::Time elapsed_time = time_now - time_last_frame;
                time_last_frame = time_now;

                // Cap elapsed time
                if (elapsed_time > UPDATE_MAX_DELTA)
                    elapsed_time = UPDATE_MAX_DELTA;


#ifndef NDEBUG
                perf_update -= total_clock.getElapsedTime();
#endif


                // Update
                // Whenever a new screen is selected, update it before rendering
                Screen * next_screen;
                while((next_screen = current_screen->update(elapsed_time)) != 0)
                {
                    if (pause_screen_active)
                        pause_screen_active = false;

                    current_screen = next_screen;
                }
#ifndef NDEBUG
                perf_update += total_clock.getElapsedTime();
                perf_draw -= total_clock.getElapsedTime();

                // Debug background
                // It changes color so you can easily see if there is a visual leak on the screen
                {
                    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
                    background.setFillColor(sf::Color(
                            std::abs(((total_clock.getElapsedTime().asMilliseconds() / 11) % 510) - 255),
                            std::abs(((total_clock.getElapsedTime().asMilliseconds() / 36) % 510) - 255),
                            std::abs(((total_clock.getElapsedTime().asMilliseconds() / 24) % 510) - 255)));
                    window.draw(background);
                }
#endif

                // Draw
                window.draw(*current_screen);

#ifndef NDEBUG
                perf_draw += total_clock.getElapsedTime();
                perf_display -= total_clock.getElapsedTime();
#endif

                // Display
                window.display();

#ifndef NDEBUG
                perf_display += total_clock.getElapsedTime();
#endif

            }
            catch (const std::exception & e)
            {
                std::cerr << "Exception caught : " << e.what() << std::endl;

                if (exception_happened)
                    throw e;

                exception_happened = true;
                Config::pause_enabled = false;

                // TODO Should not be deleted, dumped maybe
                delete current_screen;
                current_screen = new ExceptionScreen(e);
            }
            catch (const Exception & e)
            {
#ifndef NDEBUG
                // Not critical, only display on DEBUG
                std::cerr << "Special exception " << e << " caught!" << std::endl;
#endif
                switch(e)
                {
                case EXCEPTION_EXIT:
                    window.close();
                    break;

                case EXCEPTION_RESTART:
                    window.close();
                    restart = true;
                    break;
                }
            }
            catch(...)
            {
                std::cerr << "Unknown exception caught!" << std::endl;

                if (exception_happened)
                {
                    window.close();
                    break;
                }

                exception_happened = true;
                Config::pause_enabled = false;

                // TODO Should not be deleted, dumped maybe
                delete current_screen;
                current_screen = new ExceptionScreen(std::runtime_error("Unknown exception caught!"));
            }

#ifndef NDEBUG
            // Display FPS results every 600 frames (10s)
            if ((++fps_counter) == 600)
            {
                std::cout << "FPS : " << (600 / fps_clock.getElapsedTime().asSeconds()) << std::endl;
                fps_clock.restart();
                fps_counter = 0;
            }
            ++total_fps_counter;
#endif
        } // while (window.isOpen())

    } // while (restart)

#ifndef NDEBUG
    sf::Time perf_total = total_clock.getElapsedTime();

    std::cout << "Average FPS : " << (total_fps_counter / perf_total.asSeconds()) << std::endl
              << "Time elapsed in the different sections (in %) :" << std::endl
              << std::setprecision(1) << std::fixed
              << "Events  : " << (perf_event / perf_total) * 100 << std::endl
              << "Update  : " << (perf_update / perf_total) * 100 << std::endl
              << "Draw    : " << (perf_draw / perf_total) * 100 << std::endl
              << "Display : " << (perf_display / perf_total) * 100 << std::endl
              << "Other   : " << (1 - (perf_event + perf_update + perf_draw + perf_display) / perf_total) * 100 << std::endl;
#endif

    // Delete the current_screen
    delete current_screen;

    // Release resources and workers
    Async::terminate();

    // Clean resources properly
    // If debug is enabled, issue warning when ressources are still referenced
    GlobalManager::cleanAndClear();

    return 0;
}
