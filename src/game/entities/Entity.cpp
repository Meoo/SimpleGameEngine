/**
 * @file   Entity.cpp
 * @author Bastien Brunnenstein
 */

#include "game/entities/Entity.hpp"

#include <cassert>

#include <SFML/Graphics.hpp>

#include "Config.hpp"
#include "game/entities/WorldEntity.hpp"

Entity::Entity(Entity * parent)
    : _parent(parent), _world(parent->getWorld()), _dead(false), _active(true), _first_pointer(0)
{
    assert(parent);

    _parent->addChild(this);
}

Entity::~Entity()
{
    assert(!_parent);

    // Release all childs
    for (EntityList::iterator it = _childs.begin(); it != _childs.end(); ++it)
    {
        Entity * child = (*it);

        child->_parent = 0;
        delete child;
    }

    // Clean all weak pointers
    for (Pointer * p = _first_pointer; p != 0; p = p->_next)
        p->_entity = 0;
}

void Entity::setParent(Entity * parent)
{
    assert(parent);

    _parent->removeChild(this);
    _parent = parent;
    _parent->addChild(this);
}

Entity::Entity(WorldEntity * this_world)
    : _parent(0), _world(this_world), _dead(false), _active(false), _first_pointer(0)
{
}

void Entity::update(sf::Time elapsed_time)
{
    // Update self
    if (isActive())
        onUpdate(elapsed_time);

    // Update childs
    for (EntityList::iterator it = _childs.begin(); it != _childs.end(); ++it)
    {
        Entity * child = (*it);

        child->update(elapsed_time);

        if (child->isDead())
            onChildDeath(child);
    }

    // Release dead childs
    for (EntityList::iterator it = _childs.begin(); it != _childs.end(); /**/)
    {
        Entity * child = (*it);

        if ((*it)->isDead())
        {
            _childs.erase(it);

            child->_parent = 0;
            delete child;
        }

        ++it;
    }
}

void Entity::addChild(Entity * entity)
{
    assert(entity);
    assert(_childs.find(entity) == _childs.end());
    assert(entity->_world == _world);

    _childs.insert(entity);
}

void Entity::removeChild(Entity * entity)
{
    assert(entity);
    assert(_childs.find(entity) != _childs.end());

    _childs.erase(entity);
}

// ----

Entity::Pointer::Pointer()
    : _entity(0), _previous(0), _next(0)
{
}

Entity::Pointer::Pointer(Entity * pointee)
    : _entity(pointee), _previous(0)
{
    if (pointee)
    {
        _next->_previous = this;
        pointee->_first_pointer = this;
        _next = pointee->_first_pointer;
    }
    else
    {
        _next = 0;
    }
}

Entity::Pointer::Pointer(const Pointer & copy)
    : _entity(copy._entity), _previous(const_cast<Pointer*>(&copy)), _next(copy._next)
{
    copy._next = this;
}

Entity::Pointer::~Pointer()
{
    reset();
}

void Entity::Pointer::reset()
{
    if (_entity)
    {
        if (!_previous)
        {
            _entity->_first_pointer = _next;
        }
        else
        {
            _previous->_next = _next;
        }
        _next->_previous = _previous;
    }
}

void Entity::Pointer::reset(Entity * pointee)
{
    reset();

    _entity = pointee;
    if (pointee)
    {
        _previous = 0;
        _next = _entity->_first_pointer;
        _next->_previous = this;
        _entity->_first_pointer = this;
    }
}
