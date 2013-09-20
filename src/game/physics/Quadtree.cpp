/**
 * @file   Quadtree.cpp
 * @author Bastien Brunnenstein
 */

#include "game/physics/Quadtree.hpp"

#include <cmath>

#include "Config.hpp"
#include "game/entities/Entity.hpp"

/*
namespace
{
    inline sf::IntRect calcBounds(const Entity * entity)
    {
        // The IntRect must INCLUDE the FloatRect
        const sf::FloatRect & rect = entity->getBounds();
        int left   = std::floor(rect.left);
        int top    = std::floor(rect.top);
        int width  = std::ceil(rect.left + rect.width - (float) left);
        int height = std::ceil(rect.top + rect.height - (float) top);
        return sf::IntRect(left, top, width, height);
    }
}

Quadtree::Quadtree(const sf::IntRect & bounds, unsigned depth)
    : _bounds(bounds),
      _vertical_middle(_bounds.left + _bounds.width / 2),
      _horizontal_middle(_bounds.top + _bounds.height / 2),
      _depth(depth),
      _subtree_top_left(0),    _subtree_top_right(0),
      _subtree_bottom_left(0), _subtree_bottom_right(0),
      _entities(0)
{
    // If the minimum size is reached, the quadtree is forced to be a leaf
    if ((unsigned) _bounds.width <= QUADTREE_MINIMUM_SIZE
     || (unsigned) _bounds.height <= QUADTREE_MINIMUM_SIZE)
        _depth = 0;
}

Quadtree::~Quadtree()
{
    delete _subtree_top_left;
    delete _subtree_top_right;
    delete _subtree_bottom_left;
    delete _subtree_bottom_right;
}

void Quadtree::pushEntity(const Entity * entity)
{
    pushEntityInternal(entity, calcBounds(entity));
}

void Quadtree::pushEntityInternal(const Entity * entity, const sf::IntRect & entity_bounds)
{
    if (_depth == 0)
    {
        _entities.push_back(entity);
        return;
    }
    // Ok so the creation of subtrees is tricky
    // Top left block size is (b.width / 2, b.height / 2)
    // Bottom right block size is (b.width -b.width / 2, b.height - b.height / 2)
    //   and have the offset (b.width / 2, b.height / 2) from the origin (b.left, b.top)
    // TODO Quadtree Check that the implementation is correct... After some tests it looks like everything is ok...

    if (entity_bounds.left < _horizontal_middle)
    {
        // Left
        if (entity_bounds.top < _vertical_middle)
        {
            // Top Left
            if (!_subtree_top_left)
                _subtree_top_left = new Quadtree(sf::IntRect(_bounds.left, _bounds.top,
                                                             _bounds.width / 2, _bounds.height / 2),
                                                 _depth - 1);
            _subtree_top_left->pushEntityInternal(entity, entity_bounds);
        }
        if ((entity_bounds.top + entity_bounds.height) >= _vertical_middle)
        {
            // Bottom Left
            if (!_subtree_bottom_left)
                _subtree_bottom_left = new Quadtree(sf::IntRect(_bounds.left, _bounds.top + _bounds.height / 2,
                                                                _bounds.width / 2, _bounds.height - _bounds.height / 2),
                                                    _depth - 1);
            _subtree_bottom_left->pushEntityInternal(entity, entity_bounds);
        }
    }
    if ((entity_bounds.left + entity_bounds.width) >= _horizontal_middle)
    {
        // Right
        if (entity_bounds.top < _vertical_middle)
        {
            // Top Right
            if (!_subtree_top_right)
                _subtree_top_right = new Quadtree(sf::IntRect(_bounds.left + _bounds.width / 2, _bounds.top,
                                                              _bounds.width - _bounds.width / 2, _bounds.height / 2),
                                                  _depth - 1);
            _subtree_top_right->pushEntityInternal(entity, entity_bounds);
        }
        if ((entity_bounds.top + entity_bounds.height) >= _vertical_middle)
        {
            // Bottom Right
            if (!_subtree_bottom_right)
                _subtree_bottom_right = new Quadtree(sf::IntRect(_bounds.left + _bounds.width / 2, _bounds.top,
                                                                 _bounds.width - _bounds.width / 2, _bounds.height / 2),
                                                     _depth - 1);
            _subtree_bottom_right->pushEntityInternal(entity, entity_bounds);
        }
    }
}

void Quadtree::process(CallbackFunction callback_function) const
{
    if (_depth == 0)
    {
        for (EntityIterator it = _entities.begin(); it != _entities.end(); ++it)
            for (EntityIterator it2 = (it + 1); it2 != _entities.end(); ++it2)
                callback_function(*it, *it2);
    }
    else
    {
        if (_subtree_top_left)
            _subtree_top_left->process(callback_function);

        if (_subtree_top_right)
            _subtree_top_right->process(callback_function);

        if (_subtree_bottom_left)
            _subtree_bottom_left->process(callback_function);

        if (_subtree_bottom_right)
            _subtree_bottom_right->process(callback_function);
    }
}

void Quadtree::processSingleEntity(const Entity* entity, CallbackFunction callback_function) const
{
    processSingleEntityInternal(entity, callback_function, calcBounds(entity));
}

void Quadtree::processSingleEntityInternal(const Entity* entity, CallbackFunction callback_function, const sf::IntRect & entity_bounds) const
{
    if (_depth == 0)
    {
        for (EntityIterator it = _entities.begin(); it != _entities.end(); ++it)
            callback_function(entity, *it);
    }
    else
    {
        if (entity_bounds.left < _horizontal_middle)
        {
            // Left
            if (entity_bounds.top < _vertical_middle)
            {
                // Top Left
                if (_subtree_top_left)
                    _subtree_top_left->processSingleEntityInternal(entity, callback_function, entity_bounds);
            }
            if ((entity_bounds.top + entity_bounds.height) >= _vertical_middle)
            {
                // Bottom Left
                if (_subtree_bottom_left)
                    _subtree_bottom_left->processSingleEntityInternal(entity, callback_function, entity_bounds);
            }
        }
        if ((entity_bounds.left + entity_bounds.width) >= _horizontal_middle)
        {
            // Right
            if (entity_bounds.top < _vertical_middle)
            {
                // Top Right
                if (_subtree_top_right)
                    _subtree_top_right->processSingleEntityInternal(entity, callback_function, entity_bounds);
            }
            if ((entity_bounds.top + entity_bounds.height) >= _vertical_middle)
            {
                // Bottom Right
                if (_subtree_bottom_right)
                    _subtree_bottom_right->processSingleEntityInternal(entity, callback_function, entity_bounds);
            }
        }
    }
}
*/
