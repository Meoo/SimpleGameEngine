/**
 * @file   Script.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _SCRIPT_HPP_
#define _SCRIPT_HPP_

#include "resources/Resources.hpp"

class Script;

typedef Resources::Handle<Script>   ScriptHandle;
typedef Resources::Manager<Script>  ScriptManager;

class Script
{
public:
            Script();

    bool    loadFromFile(const sf::String & filename);

};

//----

class ScriptInstance
{
public:
                ScriptInstance(const ScriptHandle & script);

    void        setString(const sf::String & param_name, const sf::String & value);
    sf::String  getString(const sf::String & param_name) const;

    void        setInt(const sf::String & param_name, int value);
    int         getInt(const sf::String & param_name) const;

    bool        update(sf::Time elapsed_time);

    // Result values for update function
    static const bool SCRIPT_CONTINUE = true;
    static const bool SCRIPT_FINISHED = false;

private:
    ScriptHandle    _script;

};

#endif // _SCRIPT_HPP_
