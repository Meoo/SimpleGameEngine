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

    // Handle window restart (to change resolution, set to fullscreen...)
    bool restart = true;
    while(restart)
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

                // Handle clock
                sf::Time elapsed_time = global_clock.getElapsedTime();
                global_clock.restart();

                // Cap elapsed time
                if (elapsed_time > UPDATE_MAX_DELTA)
                    elapsed_time = UPDATE_MAX_DELTA;


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
                // Debug green screen
                window.clear(sf::Color::Green);
#endif

                // Draw
                window.draw(*current_screen);


                // Display
                window.display();

            }
            catch (const std::exception & e)
            {
                std::cerr << "Exception caught : " << e.what() << std::endl;

                if (exception_happened)
                    throw e;

                exception_happened = true;
                Config::pause_enabled = false;

                // TODO Should not be deleted
                delete current_screen;
                current_screen = new ExceptionScreen(e);
            }
            catch (const Exception & e)
            {
                std::cerr << "Integer exception caught!" << std::endl;
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
                window.close();
            }

#ifndef NDEBUG
            // Display FPS results every 600 frames (10s)
            if ((++fps_counter) == 600)
            {
                std::cout << "FPS : " << (600 / fps_clock.getElapsedTime().asSeconds()) << std::endl;
                fps_clock.restart();
                fps_counter = 0;
            }
#endif
        }

    } // while(restart)

    // Delete the current_screen
    delete current_screen;

    // Release resources and workers
    Async::terminate();

    // Clean resources properly
    // If debug is enabled, issue warning when ressources are still referenced
    GlobalManager::cleanAndClear();

    return 0;
}
