/**
 * @file   Config.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>


const sf::String CONFIG_FILE        ("config");


const sf::String WINDOW_TITLE       ("Game name here");
const sf::String WINDOW_ICON        ("res/icon.png");
const unsigned   WINDOW_WIDTH       = 800;
const unsigned   WINDOW_HEIGHT      = 600;
const bool       WINDOW_FULLSCREEN  = false;
const bool       WINDOW_BORDERLESS  = false;
const bool       WINDOW_VSYNC       = true;
const unsigned   WINDOW_FRAMERATE   = 60;


// Maximum "elapsed time" in update function
// This value means (if set to 40 ms) that the game simulation will
// start to slow down if your rendering get under 25 FPS
const sf::Time   UPDATE_MAX_DELTA   (sf::milliseconds(40));


const sf::Time   INTRO_TIME         (sf::seconds(5.f));
const sf::Time   INTRO_TRANSITION   (sf::seconds(.5f));
const sf::String INTRO_TITLE        (WINDOW_TITLE);
const sf::String INTRO_SUBTITLE     ("Made by Bastien Brunnenstein");


const sf::String PAUSE_TITLE        ("PAUSE");
const sf::String PAUSE_SUBTITLE     ("Press P to resume the game");


const bool       RESOURCES_THREADING    = true;
const unsigned   RESOURCES_WORKERS_MAX  = 8u;   // 1 min
const unsigned   RESOURCES_JOBS_MAX     = 128u; // 32 min

const sf::String RESOURCES_DEFAULT_FONT ("res/fonts/PoetsenOne-Regular.ttf");


const sf::String MENU_BACKGROUND    ("res/menu.png");

const sf::Color  MENU_ITEM          (sf::Color::Black);
const sf::Color  MENU_SHADOW        (sf::Color::White);
const sf::Color  MENU_SELECTION     (0, 0, 192);

const bool       MENU_LOAD_ENABLED  = true;
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


const sf::String ERROR_STRING       ("<<<ERROR>>>");


typedef enum Exception
{
    EXCEPTION_EXIT,
    EXCEPTION_RESTART,

} Exception;


// Configuration variables, implemented in Main.cpp
namespace Config
{
    extern unsigned   width;        // = WINDOW_WIDTH
    extern unsigned   height;       // = WINDOW_HEIGHT
    extern bool       fullscreen;   // = WINDOW_FULLSCREEN
    extern bool       borderless;   // = WINDOW_BORDERLESS

    void save();
    void load();

}

#endif // _CONFIG_HPP_
