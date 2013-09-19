/**
 * @file   Script.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _SCRIPT_HPP_
#define _SCRIPT_HPP_

#include "resources/Resources.hpp"

class Script
{
public:
            Script();

    bool    loadFromFile(const sf::String & filename);

};

typedef Resources::Handle<Script>   ScriptHandle;
typedef Resources::Manager<Script>  ScriptManager;

#endif // _SCRIPT_HPP_
