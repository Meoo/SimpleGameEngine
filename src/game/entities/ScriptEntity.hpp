/**
 * @file   ScriptEntity.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _SCRIPTENTITY_HPP_
#define _SCRIPTENTITY_HPP_

#include "game/entities/Entity.hpp"
#include "game/Script.hpp"

/**
 * An entity driven by a Script.
 */
class ScriptEntity : public Entity
{
public:
                    ScriptEntity(const ScriptHandle & script);

    virtual         ~ScriptEntity();

    void            setString(const sf::String & param_name, const sf::String & value);
    sf::String      getString(const sf::String & param_name) const;

    void            setInt(const sf::String & param_name, int value);
    int             getInt(const sf::String & param_name) const;

private:
    ScriptHandle    _script;
};

#endif // _SCRIPTENTITY_HPP_
