/**
 * @file   Config.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>


/** User's configuration file name. */
const sf::String CONFIG_FILE        ("config");


/** @name Application's window configuration */
/**@{*/

const sf::String WINDOW_TITLE       ("Game name here");
const sf::String WINDOW_ICON        ("res/icon.png");
const unsigned   WINDOW_WIDTH       = 800;
const unsigned   WINDOW_HEIGHT      = 600;
const bool       WINDOW_FULLSCREEN  = false;
const bool       WINDOW_BORDERLESS  = false;
const bool       WINDOW_VSYNC       = true;
const unsigned   WINDOW_FRAMERATE   = 60;

/**@}*/


/** @name Pause screen configuration */
/**@{*/

const sf::String PAUSE_TITLE        ("PAUSE");
const sf::String PAUSE_SUBTITLE     ("Press P to resume the game");

/**@}*/


// Maximum "elapsed time" in update function
// This value means (if set to 40 ms) that the game simulation will
// start to slow down if your rendering get under 25 FPS
const sf::Time   UPDATE_MAX_DELTA   (sf::milliseconds(40));


/** @name Intro screen configuration */
/**@{*/

const sf::Time   INTRO_TIME         (sf::seconds(5.f));
const sf::Time   INTRO_TRANSITION   (sf::seconds(.5f));
const sf::String INTRO_TITLE        (WINDOW_TITLE);
const sf::String INTRO_SUBTITLE     ("Made by Bastien Brunnenstein");

/**@}*/


/** @name Resources and workers configuration */
/**@{*/

const bool       RESOURCES_THREADING    = true;
const unsigned   RESOURCES_WORKERS_MAX  = 8u;   // 1 min
const unsigned   RESOURCES_JOBS_MAX     = 128u; // 32 min

const sf::String RESOURCES_DEFAULT_FONT ("res/fonts/PoetsenOne-Regular.ttf");

/**@}*/


/** @name Main menu configuration */
/**@{*/

const sf::String MENU_BACKGROUND    ("res/menu.png");

const sf::Color  MENU_ITEM          (sf::Color::Black);
const sf::Color  MENU_SHADOW        (sf::Color::White);
const sf::Color  MENU_SELECTION     (0, 0, 192);

/** Set to false to completely disable loading a previously saved game */
const bool       MENU_LOAD_ENABLED    = true;

/** Set to false to completely disable options screen */
const bool       MENU_OPTIONS_ENABLED = true;

const sf::String MENU_NEW_GAME      ("New game");
const sf::String MENU_LOAD_GAME     ("Continue");
const sf::String MENU_OPTIONS       ("Options");
const sf::String MENU_QUIT          ("Quit");

const sf::String MENU_RESOLUTION    ("Resolution");

const sf::String MENU_MODE          ("Mode");
const sf::String MENU_WINDOWED      ("< Windowed >");
const sf::String MENU_BORDERLESS    ("< Borderless >");
const sf::String MENU_FULLSCREEN    ("< Fullscreen >");

const sf::String MENU_ACCEPT        ("Accept");
const sf::String MENU_CANCEL        ("Cancel");

const sf::String MENU_YES           ("Yes");
const sf::String MENU_NO            ("No");

/**@}*/


/**
 * Special exceptions that can be thrown, usually from screens.
 *
 * They are caught by the main loop.
 */
typedef enum Exception
{
    /**
     * Exception that cause the application to be closed.
     */
    EXCEPTION_EXIT,

    /**
     * Exception that cause the re-creation of game windows when thrown.
     *
     * Used to change the game resolution or window mode.
     * For example, you can't switch to fullscreen without closing the window.
     */
    EXCEPTION_RESTART,

} Exception;


/** Configuration variables and functions. */
namespace Config
{
    extern unsigned   width;        // = WINDOW_WIDTH
    extern unsigned   height;       // = WINDOW_HEIGHT
    extern bool       fullscreen;   // = WINDOW_FULLSCREEN
    extern bool       borderless;   // = WINDOW_BORDERLESS

    /** Save current configuration in CONFIG_FILE. */
    void save();

    /** Load configuration from CONFIG_FILE. */
    void load();

}

#endif // _CONFIG_HPP_
