/**
 * @file   Config.cpp
 * @author Bastien Brunnenstein
 */

#include "Config.hpp"

#include <iostream>
#include <fstream>

namespace Config
{
    unsigned   width       = WINDOW_WIDTH;
    unsigned   height      = WINDOW_HEIGHT;
    bool       fullscreen  = WINDOW_FULLSCREEN;
    bool       borderless  = WINDOW_BORDERLESS;
}

void Config::save()
{
    std::ofstream file (CONFIG_FILE.toAnsiString().c_str());

    if (!file.is_open())
    {
        std::cerr << "Unable to write configuration file : "
                  << CONFIG_FILE.toAnsiString() << std::endl;
        return;
    }

    file << "width " << Config::width << "\n"
         << "height " << Config::height << "\n"
         << "fullscreen " << ((int) Config::fullscreen) << "\n"
         << "borderless " << ((int) Config::borderless) << std::endl;

    file.flush();
}

void Config::load()
{
    std::ifstream file (CONFIG_FILE.toAnsiString().c_str());
    std::string text;

    if (!file.is_open())
        return;

    file >> std::ws;
    while (!file.eof())
    {
        file >> text;

        if (text == std::string("width"))
        {
            int w;
            file >> w;
            Config::width = w;
        }
        else if (text == std::string("height"))
        {
            int h;
            file >> h;
            Config::height = h;
        }
        else if (text == std::string("fullscreen"))
        {
            bool f;
            file >> f;
            Config::fullscreen = f;
        }
        else if (text == std::string("borderless"))
        {
            bool b;
            file >> b;
            Config::borderless = b;
        }
        else
        {
            std::cerr << "Unknown configuration option : "
                      << text << std::endl;
            file >> text;
        }

        file >> std::ws;
    }
}
