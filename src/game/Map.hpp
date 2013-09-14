/**
 * @file   Map.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <SFML/System/String.hpp>

#include "game/Collisions.hpp"
#include "game/Tileset.hpp"
#include "resources/Resources.hpp"

class Entity;

// Coordinates, in tiles
typedef struct MapCoord
{
    int x;

    int y;

} MapCoord;

//----

typedef struct MapTile
{
    MapCoord position;

    CollisionMask collision_group;

    CollisionStyle collision_style;

    TileId tile;

} MapTile;

//----

typedef struct MapInfo
{
    sf::String  filename;

    MapCoord    offset;

} MapInfo;

//----

class Map
{
public:
    typedef std::vector<MapInfo> MapSurroundings;

                Map();

                ~Map();

    bool        loadFromFile(const sf::String & filename);

    // Populate this Map in the World, creating entities and running scripts
    void        populate(const MapCoord & map_offset) const;


    unsigned    getWidth() const;

    unsigned    getHeight() const;

    const MapTile & getTile(unsigned x, unsigned y) const;

    const MapSurroundings & getSurroundingMaps() const;

private:
    typedef struct EntityInfo
    {
        MapCoord    offset;

        sf::String  global_name;

    } EntityInfo;

    typedef std::vector<EntityInfo> Entities;

    MapTile *       _tiles;

    Tileset         _tileset;

    TextureHandle   _tileset_texture;

    MapSurroundings _surroundings;

    Entities        _entities;

};

#endif // _MAP_HPP_
