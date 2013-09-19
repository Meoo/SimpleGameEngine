/**
 * @file   Map.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <SFML/System/String.hpp>

#include "game/physics/Body.hpp"
#include "resources/Resources.hpp"

#include "game/Tileset.hpp"

//----

typedef struct MapOffset
{
    unsigned    x;

    unsigned    y;

} MapOffset;

//----

typedef struct MapInfo
{
    sf::String  filename;

    MapOffset   offset;

} MapInfo;

//----

class Map
{
public:
    typedef std::vector<MapInfo> MapSurroundings;

                Map();

                ~Map() {}

    bool        loadFromFile(const sf::String & filename);

    // Populate this Map in the World, creating entities and running scripts
    void        populate(const MapOffset & map_offset) const;


    unsigned    getWidth() const;

    unsigned    getHeight() const;

    // TODO const MapTile & getTile(unsigned x, unsigned y) const;

    const MapSurroundings & getSurroundingMaps() const;

private:
    typedef struct EntityInfo
    {
        MapOffset   offset;

        sf::String  global_name;

    } EntityInfo;

    typedef std::vector<EntityInfo> Entities;

    // TODO MapTile *       _tiles;

    Tileset         _tileset;

    TextureHandle   _tileset_texture;

    MapSurroundings _surroundings;

    Entities        _entities;

};

typedef Resources::Handle<Map>  MapHandle;
typedef Resources::Manager<Map> MapManager;

#endif // _MAP_HPP_
