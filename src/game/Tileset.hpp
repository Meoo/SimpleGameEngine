/**
 * @file   Tileset.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _TILESET_HPP_
#define _TILESET_HPP_

#include "resources/Resources.hpp"

#include <cassert>

typedef unsigned TileId;

class Tileset
{
public:
    // tile_width & tile_height : size of a single tile in pixels
    // tiles_columns & tiles_rows : number of vertical / horizontal tiles in the texture
    Tileset(unsigned tile_width, unsigned tile_height, unsigned tiles_columns, unsigned tiles_rows)
        : _width(tile_width), _height(tile_height), _columns(tiles_columns), _rows(tiles_rows)
    {}

    sf::IntRect getTextureRect(TileId tile_id) const
    {
        assert(tile_id >= 0 && tile_id < (_columns * _rows));
        return sf::IntRect((tile_id % _columns) * _width, (tile_id / _rows) * _height, _width, _height);
    }

private:
    unsigned _width;
    unsigned _height;
    unsigned _columns;
    unsigned _rows;

};

#endif // _TILESET_HPP_
