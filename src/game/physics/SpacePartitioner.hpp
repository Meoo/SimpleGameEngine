/**
 * @file   SpacePartitioner.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _SPACEPARTITIONER_HPP_
#define _SPACEPARTITIONER_HPP_

#include <set>

#include <SFML/Graphics/Rect.hpp>

#include "game/physics/Body.hpp"

class World;

/**
 * Allow a quicker resolution of collisions by grouping entities spatially.
 */
class SpacePartitioner
{
public:
    typedef std::set<Entity *>  EntityList; // TODO SpacePartitioner ConstEntityList?

    typedef std::set<Body>      BodyList; // TODO SpacePartitioner BodyList use pointers?

    /**
     * Virtual destructor for inheritance.
     */
    virtual             ~SpacePartitioner() {}

    /**
     * Rebuild the quadtree using given world.
     *
     * @param world
     */
    virtual void        updateEntities(World * world) = 0;

    // TODO SpacePartitioner def computeCollisions, computeCollisionsWithEntity

    /**
     * Find entites in a given rectangle.
     *
     * TODO ConstEntityList?
     *
     * @param rectangle
     * @return a set of entities intersecting with given rectangle.
     */
    virtual EntityList  findEntitiesInRectangle(const sf::FloatRect & rectangle) const = 0;

    /**
     * Find bodies in a given rectangle.
     *
     * @param rectangle
     * @return a set of bodies intersecting with given rectangle.
     */
    virtual BodyList    findBodiesInRectangle(const sf::FloatRect & rectangle) const = 0;

};

#endif // _SPACEPARTITIONER_HPP_
