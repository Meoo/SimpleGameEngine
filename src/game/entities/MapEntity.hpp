/**
 * @file   MapEntity.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _MAPENTITY_HPP_
#define _MAPENTITY_HPP_

#include "game/entities/Entity.hpp"

#include "game/Map.hpp"

/**
 * A map on the world.
 */
class MapEntity : public Entity
{
public:
                    MapEntity(const MapHandle & map, const MapOffset & offset);

    virtual         ~MapEntity();

    sf::FloatRect   getBounds() const;

    BodyList        getBodies(const sf::FloatRect & hint = sf::FloatRect()) const;

private:
    MapHandle _map;

};

#endif // _MAPENTITY_HPP_
