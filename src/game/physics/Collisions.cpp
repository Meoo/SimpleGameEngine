/**
 * @file   Collisions.cpp
 * @author Bastien Brunnenstein
 */

#include "game/physics/Collisions.hpp"

#include <cassert>
#include <cmath>

#include "game/entities/Entity.hpp"
/*
namespace
{
    using Collision::CollisionData;
    typedef Entity::Vector Vector;
    typedef Entity::Bounds Bounds;

    bool checkSquareSquare(const Body & first, const Body & second, CollisionData & data)
    {
        // Bounds check
        Vector inertia(first.inertia - second.inertia);

        Bounds first_bounds(first.position + first.size / 2,
                            first.position - first.size / 2);
        Bounds second_bounds(second.position + second.size / 2,
                             second.position - second.size / 2);

        // Check for any intersection first
        Bounds intersect(first_bounds.getIntersection(second_bounds));

        if (intersect.isEmpty())
            return false;

        float max;

        // Horizontal check
        float left_dist = first_bounds.getUpperLimit().getX() - intersect.getUpperLimit().getX();
        float right_dist = first_bounds.getLowerLimit().getX() - intersect.getLowerLimit().getX();

        if (std::abs(left_dist) > std::abs(right_dist) + inertia.getX())
        {
            // TODO Left collision

            max = left_dist - inertia.getX();
        }
        else
        {
            // TODO Right collision

            max = right_dist + inertia.getX();
        }

        // Vertical check
        float top_dist = first_bounds.getUpperLimit().getY() - intersect.getUpperLimit().getY();
        float bot_dist = first_bounds.getLowerLimit().getY() - intersect.getLowerLimit().getY();

        if (std::abs(top_dist) > std::abs(bot_dist) + inertia.getY())
        {
            // TODO Top collision

            if (top_dist - inertia.getY() < max)
                return true;
        }
        else
        {
            // TODO Bottom collision

            if (bot_dist + inertia.getY() < max)
                return true;

        }

        return true;
    }
}

bool Collision::checkEntityCollisions(const Entity * first, const Entity * second, CollisionList & collisions)
{
    typedef Entity::BodyList BodyList;

    CollisionData   data;
    bool            collides = false;

    BodyList first_bodies  = first->getBodies(second->getBounds());
    BodyList second_bodies = second->getBodies(first->getBounds());

    for (BodyList::iterator itf = first_bodies.begin(); itf != first_bodies.end(); ++itf)
    {
        for (BodyList::iterator its = first_bodies.begin(); its != first_bodies.end(); ++its)
        {
            if (checkBodyCollisions(*itf, *its, data))
            {
                collisions.push_back(data);
                collides = true;
            }
        }
    }

    return collides;
}

bool Collision::checkBodyCollisions(const Body & first, const Body & second, CollisionData & data)
{
    // Collision masks
    if (!((data.second_group = static_cast<CollisionGroup>(first.group & second.mask))
    &&    (data.first_group = static_cast<CollisionGroup>(second.group & first.mask))))
        return false;

    // Actual collisions
    switch (first.shape)
    {
    case COLLISION_SHAPE_SQUARE:
        switch (second.shape)
        {
        case COLLISION_SHAPE_SQUARE:
            return checkSquareSquare(first, second, data);
            break;

            // TODO

        default:
            break;
        }
        break;

        // TODO

    default:
        break;
    }

    assert(false && "Collision style not implemented yet");
    return false;
}*/
