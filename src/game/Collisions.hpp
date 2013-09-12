/**
 * @file   Collisions.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _COLLISIONS_HPP_
#define _COLLISIONS_HPP_

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

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


typedef struct CollisionData
{
    bool collides;

    CollisionMask collision_mask;

    sf::Vector2i push_out_vector;

} CollisionData;


namespace Collision
{
    void checkCollisionEntityTile(const Entity * entity, const MapTile * tile, CollisionData * output);

    void checkCollisionEntityEntity(const Entity * first, const Entity * second, CollisionData * output);

    /* force is the difference of velocity between the two objects (first_velocity - second_velocity)
     * it is used to get a good direction on CollisionData.push_out_vector
     */
    void checkCollision(const sf::FloatRect & first_bounds,  CollisionMask first_mask,  CollisionStyle first_style,
                        const sf::FloatRect & second_bounds, CollisionMask second_mask, CollisionStyle second_style,
                        const sf::Vector2f & force, CollisionData * output);
}

#endif // _COLLISIONS_HPP_
