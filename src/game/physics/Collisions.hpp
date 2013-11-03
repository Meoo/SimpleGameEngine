/**
 * @file   Collisions.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _COLLISIONS_HPP_
#define _COLLISIONS_HPP_

#include "game/physics/Body.hpp"

#include <vector>

class Entity;

namespace Collision
{
    // TODO Collisions...

    typedef struct CollisionData
    {
        /**
         * The collision groups the first body collided with.
         */
        CollisionGroup first_group;

        /**
         * The collision groups the second body collided with.
         */
        CollisionGroup second_group;

    } CollisionData;

    typedef std::vector<CollisionData> CollisionList;

    /**
     * Check for collisions between two entitites.
     *
     * @param first First entity.
     * @param second Second entity.
     * @param[out] collisions CollisionList object to be filled by this function.
     * @return @c true if at least one collision is detected.
     */
    bool checkEntityCollisions(const Entity * first, const Entity * second, CollisionList & collisions);

    /**
     * Check for collisions between two bodies.
     *
     * @param first First body.
     * @param second Second body.
     * @param[out] data CollisionData structure to be filled by this function.
     * @return @c true if a collision is detected.
     */
    bool checkBodyCollisions(const Body & first, const Body & second, CollisionData & data);

}

#endif // _COLLISIONS_HPP_
