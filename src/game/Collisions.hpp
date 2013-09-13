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

    // Team collisions, used (for example) to prevent player projectiles hitting his allies
    COLLISION_MASK_GROUP_PLAYERS    = 1 << 1,
    COLLISION_MASK_GROUP_ENEMIES    = 1 << 2,
    COLLISION_MASK_GROUP_NEUTRAL    = 1 << 3,

    // Used by trigger entities and tiles
    COLLISION_MASK_SPECIAL_TRIGGER  = 1 << 4,

    // Special tile types with side effects
    COLLISION_MASK_SPECIAL_WATER    = 1 << 5,
    COLLISION_MASK_SPECIAL_TOXIC    = 1 << 6,
    COLLISION_MASK_SPECIAL_SLOW     = 1 << 7,

} CollisionMask;


typedef enum CollisionStyle
{
    COLLISION_STYLE_NONE = 0,

    // Square
    COLLISION_STYLE_BOUNDING_BOX,

    // Other regular shapes
    COLLISION_STYLE_DIAMOND,
    COLLISION_STYLE_OCTAGON,

    // Corners
    COLLISION_STYLE_CORNER_TOP_LEFT,
    COLLISION_STYLE_CORNER_TOP_RIGHT,
    COLLISION_STYLE_CORNER_BOTTOM_LEFT,
    COLLISION_STYLE_CORNER_BOTTOM_RIGHT,

    // Triangles
    COLLISION_STYLE_SPIKE_UP,
    COLLISION_STYLE_SPIKE_DOWN,
    COLLISION_STYLE_SPIKE_LEFT,
    COLLISION_STYLE_SPIKE_RIGHT,

    COLLISION_STYLE_MAX,

} CollisionStyle;


typedef struct CollisionData
{
    bool collides;

    sf::Vector2i push_out_vector;

} CollisionData;


namespace Collision
{
    void checkCollisionEntityTile(const Entity * entity, const MapTile * tile, CollisionData * output);

    void checkCollisionEntityEntity(const Entity * first, const Entity * second, CollisionData * output);

    /* force is the difference of velocity between the two objects (first_velocity - second_velocity)
     * it is used to get a good direction on CollisionData.push_out_vector
     */
    void checkCollision(const sf::FloatRect & first_bounds,  CollisionStyle first_style,
                        const sf::FloatRect & second_bounds, CollisionStyle second_style,
                        const sf::Vector2f & force, CollisionData * output);
}

#endif // _COLLISIONS_HPP_
