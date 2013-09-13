/**
 * @file   Quadtree.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _QUADTREE_HPP_
#define _QUADTREE_HPP_

#include <vector>

#include <SFML/Graphics/Rect.hpp>

class Entity;

class Quadtree
{
public:
    typedef void (*CallbackFunction) (const Entity * first, const Entity * second);

    // depth is the maximum depth of the quadtree
    // You can have up to (4 ^ depth) subdivisions in a quadtree
            Quadtree(const sf::IntRect & bounds, unsigned depth);

            ~Quadtree();

    void    pushEntity(const Entity * entity);

    // Call a function for every pair of entities that could possibly collides
    void    process(CallbackFunction callback_function) const;

    // Call a function for every entity that could possibly collide with given entity
    // The entity given to this function is passed as the first parameter of callback function
    void    processSingleEntity(const Entity * entity, CallbackFunction callback_function) const;

private:
    typedef std::vector<const Entity *> EntityList;
    typedef EntityList::const_iterator  EntityIterator;

    // entity_bounds is cached by pushEntity
    void    pushEntityInternal(const Entity * entity, const sf::IntRect & entity_bounds);

    // entity_bounds is cached by processSingleEntity
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
