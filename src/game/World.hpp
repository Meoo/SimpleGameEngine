/**
 * @file   World.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include <SFML/Graphics.hpp>

#include "game/Map.hpp"
#include "game/Entity.hpp"
#include "game/Script.hpp"

namespace World
{
//----vvvv
    // offset : coordinate of the top-left tile of the Map on the World
    void        pushMap(const MapHandle & map, const MapCoord & offset);

    // Insert a newly created entity onto the World
    Entity::Id  pushEntity(Entity * entity);

    // Play a script
    void        pushScript(ScriptInstance * script);
//----^^^^


    Entity *    getEntity(Entity::Id entity_id);

    Entity *    getEntity(const sf::String & global_name);


    // Update the whole World
    void        update(sf::Time elapsed_time);

    // Render the whole World
    void        render(sf::RenderTarget & target);

} // namespace World

#endif // _WORLD_HPP_
