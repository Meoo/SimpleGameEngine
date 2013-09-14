/**
 * @file   Main.cpp
 * @author Bastien Brunnenstein
 */

#include <SFML/Graphics.hpp>

#include "Config.hpp"
#include "screens/Screen.hpp"
#include "screens/IntroScreen.hpp"
#include "resources/Async.hpp"
#include "resources/Resources.hpp"
#include "resources/Manager.hpp"

#ifndef NDEBUG
#include <iostream>
#endif

int main(int argc, char ** argv)
{
    Config::load();

    // Start resources system
    Async::initialize();

    // Preload default font (used in Pause screen)
    FontHandle font_handle(FontManager::find(RESOURCES_DEFAULT_FONT));

    // Create first screen : Intro
    Screen * current_screen = new IntroScreen();

    // Prepare render window
    sf::RenderWindow window;

    // Handle window restart (to change resolution, set to fullscreen...)
    bool restart = true;
    while(restart)
    {
        restart = false;

        // Pause variables and drawables
        bool pause = false;

        sf::RectangleShape pause_black_screen(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        sf::Text pause_text(PAUSE_TITLE, font_handle.get(), 100);
        sf::Text pause_text2(PAUSE_SUBTITLE, font_handle.get(), 50);
        pause_text.setStyle(sf::Text::Bold);
        pause_black_screen.setFillColor(sf::Color(0, 0, 0, 128));
        pause_text.setOrigin(pause_text.getLocalBounds().width/2, pause_text.getLocalBounds().height/2);
        pause_text2.setOrigin(pause_text2.getLocalBounds().width/2, pause_text2.getLocalBounds().height/2);
        pause_text.setColor(sf::Color::White);
        pause_text2.setColor(sf::Color::White);
        pause_text.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - 90);
        pause_text2.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + 60);

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
            // Events
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch(event.type)
                {
                case sf::Event::KeyPressed:

                    // Toggle pause with P
                    if (event.key.code == sf::Keyboard::P)
                    {
                        pause = !pause;
                        continue;
                    }

                    // Exit with Alt+F4
                    if (event.key.code == sf::Keyboard::F4 && event.key.alt)
                    {
                        window.close();
                        continue;
                    }

                    if (!pause)
                        current_screen->onKeyPressed(event.key.code);
                    break;

                // Pause automatically if the focus is lost
                case sf::Event::LostFocus:
                    pause = true;
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
            if (!pause)
            {
                try
                {
                    // Whenever a new screen is selected, update it before rendering
                    Screen * next_screen;
                    while((next_screen = current_screen->update(elapsed_time)) != 0)
                    {
                        current_screen = next_screen;
                    }
                }
                catch (const Exception & e)
                {
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
            }

            // Draw
#ifndef NDEBUG
            window.clear(sf::Color::Green);
#endif

            window.draw(*current_screen);

            // Draw pause screen
            if (pause)
            {
                window.draw(pause_black_screen);
                window.draw(pause_text);
                window.draw(pause_text2);
            }

            // Display
            window.display();

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

    // Release the default font (used for Pause screen)
    font_handle.reset();

    // Release resources and workers
    Async::terminate();

    // Clean resources properly
    // If debug is enabled, issue warning when ressources are still referenced
    GlobalManager::cleanAndClear();

    return 0;
}
