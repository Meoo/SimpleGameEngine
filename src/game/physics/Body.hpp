/**
 * @file   Body.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _BODY_HPP_
#define _BODY_HPP_

#include <Mw/Math/Vector2.hpp>

class Entity;

//----

typedef enum CollisionGroup
{
    COLLISION_MASK_NONE             = 0,

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

    // Use -1 trick to set all bits to 1
    COLLISION_MASK_ANY              = -1u

} CollisionGroup;

//----

/**
 * Enumeration of every collision shape avaiable.
 */
typedef enum CollisionShape
{
    COLLISION_SHAPE_NONE = 0,           //!< Should not be used

    // Regular shapes
    COLLISION_SHAPE_SQUARE,
    COLLISION_SHAPE_DIAMOND,
    COLLISION_SHAPE_OCTAGON,
    COLLISION_SHAPE_CIRCLE,

    // Corners
    COLLISION_SHAPE_CORNER_TOP_LEFT,
    COLLISION_SHAPE_CORNER_TOP_RIGHT,
    COLLISION_SHAPE_CORNER_BOTTOM_LEFT,
    COLLISION_SHAPE_CORNER_BOTTOM_RIGHT,

    // Triangles
    COLLISION_SHAPE_TRIANGLE_UP,
    COLLISION_SHAPE_TRIANGLE_DOWN,
    COLLISION_SHAPE_TRIANGLE_LEFT,
    COLLISION_SHAPE_TRIANGLE_RIGHT,

    COLLISION_STYLE_MAX,                //!< Number of shapes avaiable

} CollisionShape;

//----

/**
 * Representation of a physical body in the world.
 */
class Body
{
    typedef mw::math::Vector2<float> Vector;

public:
    /**
     * Custom user data (can be used to identify the body).
     */
    void *          user_data;

    /**
     * Position (center) of this body in the world.
     */
    Vector          position;

    /**
     * Size of this body.
     */
    Vector          size;

    /**
     * Inertia of this body.
     */
    Vector          inertia;

    /**
     * Shape of this body.
     */
    CollisionShape  shape;

    /**
     * Collision group of this body.
     */
    CollisionGroup  group;

    /**
     * Collision mask of this body.
     */
    CollisionGroup  mask;

};

#endif // _BODY_HPP_
