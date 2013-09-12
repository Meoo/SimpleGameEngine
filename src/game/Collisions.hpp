/**
 * @file   Collisions.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _COLLISIONS_HPP_
#define _COLLISIONS_HPP_

class Entity;
struct MapCoord;
struct MapTile;

typedef enum CollisionMask
{
    COLLISION_MASK_WORLD            = 1 << 0,

    COLLISION_MASK_WATER            = 1 << 1,
    COLLISION_MASK_TOXIC            = 1 << 2,
    COLLISION_MASK_SLOW             = 1 << 3,

    COLLISION_MASK_MAGIC            = 1 << 4,
    COLLISION_MASK_GHOST            = 1 << 5,

    COLLISION_MASK_EVENT            = 1 << 7,

    COLLISION_MASK_PROJECTILE       = 1 << 8,
    COLLISION_MASK_MAGIC_MISSILE    = 1 << 9,

    COLLISION_MASK_TRAP_SPIKE       = 1 << 12,
    COLLISION_MASK_TRAP_SUPERSPIKE  = 1 << 13,
    COLLISION_MASK_TRAP_TRIGGER     = 1 << 14,

} CollisionMask;

typedef enum CollisionStyle
{
    COLLISION_STYLE_NONE = 0,

    COLLISION_STYLE_BOUNDING_BOX,

    COLLISION_STYLE_CORNER_TOP_LEFT,
    COLLISION_STYLE_CORNER_TOP_RIGHT,
    COLLISION_STYLE_CORNER_BOTTOM_LEFT,
    COLLISION_STYLE_CORNER_BOTTOM_RIGHT,

    COLLISION_STYLE_HALF_TOP,
    COLLISION_STYLE_HALF_BOTTOM,
    COLLISION_STYLE_HALF_LEFT,
    COLLISION_STYLE_HALF_RIGHT,

    COLLISION_STYLE_PLATFORM_ONE_WAY,
    COLLISION_STYLE_PLATFORM_TWO_WAYS,

    COLLISION_STYLE_SPIKE_UP,
    COLLISION_STYLE_SPIKE_DOWN,
    COLLISION_STYLE_SPIKE_LEFT,
    COLLISION_STYLE_SPIKE_RIGHT,

    COLLISION_STYLE_DIAMOND,
    COLLISION_STYLE_OCTAGON,

    COLLISION_STYLE_MAX,

} CollisionStyle;

// Entity - Tile collision data
typedef struct MapTileCollision
{
    const struct MapCoord & tile_position;

    const struct MapTile & tile;

    CollisionMask collision_mask;

} MapTileCollision;

// Entity - Entity collision data
typedef struct EntityCollision
{
    const Entity * first;

    const Entity * second;

    CollisionMask collision_mask;

} EntityCollision;

#endif // _COLLISIONS_HPP_
