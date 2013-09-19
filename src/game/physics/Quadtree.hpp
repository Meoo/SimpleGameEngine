/**
 * @file   Quadtree.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _QUADTREE_HPP_
#define _QUADTREE_HPP_

#include <vector>

#include <SFML/Graphics/Rect.hpp>

#include "game/physics/SpacePartitioner.hpp"

class Entity;


/**
 * Quadtree division's minimum width and height.
 *
 * This is not really a minimum as the size can be under it.
 * A quadtree will not be subdivised furthermore if either it's width or height
 * is inferior or equal to this value.
 *
 * Minimum value : 1, default value : 4
 */
const unsigned   QUADTREE_MINIMUM_SIZE  = 4u;

/**
 * Default depth value for a Quadtree.
 *
 * This value is used as a default parameter and can be overrided manually.
 * A smaller depth result in more pairs created, while a higher depth result
 * in less pairs created, but a higher cost to insert elements into the Quadtree.
 *
 * A value between 2 and 4 should be used.
 *
 * Default value : 3
 */
const unsigned   QUADTREE_DEFAULT_DEPTH = 3u;


/**
 * Space partitioner using a quadtree.
 *
 * Allow a quicker resolution of collisions by grouping entities spatially.
 */
class Quadtree : public SpacePartitioner // TODO Quadtree must be redone using SpacePartitioner functions
{
public:
    typedef void (*CallbackFunction) (const Entity * first, const Entity * second);

    /**
     * Create a Quadtree with given bounds and depth.
     *
     * If an entity is out of bounds, it will still be able to collide other
     * entities, but this case should be an exception.
     * You can have up to (4 ^ depth) subdivisions in a quadtree.
     *
     * @param bounds Square that should be enclosing every entity.
     * @param depth is the maximum depth of the quadtree
     */
            Quadtree(const sf::IntRect & bounds, unsigned depth = QUADTREE_DEFAULT_DEPTH);

            ~Quadtree();

    /**
     * Insert an entity into the quadtree.
     *
     * This function will create sub-quadtrees as needed.
     *
     * @param entity
     */
    void    pushEntity(const Entity * entity);

    /**
     * Call a function for every pair of entities that could possibly collides.
     *
     * @param callback_function
     */
    void    process(CallbackFunction callback_function) const;

    /**
     * Call a function for every entity that could possibly collide with given entity.
     *
     * The entity given to this function is passed as the first parameter of callback function.
     *
     * @param entity
     * @param callback_function
     */
    void    processSingleEntity(const Entity * entity, CallbackFunction callback_function) const;

private:
    typedef std::vector<const Entity *> EntityList;
    typedef EntityList::const_iterator  EntityIterator;

    /**
     * Internal function used to put entity_bounds in cache.
     *
     * @see pushEntity
     *
     * @param entity
     * @param entity_bounds entity's @c integer bounds, enclosing it's @c float bounds.
     */
    void    pushEntityInternal(const Entity * entity, const sf::IntRect & entity_bounds);

    /**
     * Internal function used to put entity_bounds in cache.
     *
     * @see processSingleEntity
     *
     * @param entity
     * @param callback_function
     * @param entity_bounds entity's @c integer bounds, enclosing it's @c float bounds.
     */
    void    processSingleEntityInternal(const Entity * entity, CallbackFunction callback_function, const sf::IntRect & entity_bounds) const;

    sf::IntRect     _bounds;

    int             _vertical_middle;
    int             _horizontal_middle;

    unsigned        _depth;

    Quadtree *      _subtree_top_left;
    Quadtree *      _subtree_top_right;
    Quadtree *      _subtree_bottom_left;
    Quadtree *      _subtree_bottom_right;

    EntityList      _entities;

};

#endif // _QUADTREE_HPP_
