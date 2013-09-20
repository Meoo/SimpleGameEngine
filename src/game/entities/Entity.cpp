/**
 * @file   Entity.cpp
 * @author Bastien Brunnenstein
 */

#include "game/entities/Entity.hpp"

#include <cassert>

#include "game/entities/WorldEntity.hpp"

Entity::Entity(Entity * parent)
    : _id(parent->getWorld()->allocateEntityId())
    , _parent(parent), _dead(false), _active(true), _solid(true), _visible(true)
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
}

Entity * Entity::findEntity(Id entity_id)
{
    for (EntityList::iterator it = _childs.begin(); it != _childs.end(); ++it)
        if ((*it)->getId() == entity_id)
            return (*it);

    return 0;
}

const Entity * Entity::findEntity(Id entity_id) const
{
    for (EntityList::const_iterator it = _childs.begin(); it != _childs.end(); ++it)
        if ((*it)->getId() == entity_id)
            return (*it);

    return 0;
}

void Entity::setParent(Entity * parent)
{
    assert(parent);

    _parent->removeChild(this);
    _parent = parent;
    _parent->addChild(this);
}

void Entity::drawDebug(sf::RenderTarget & target, sf::RenderStates states) const
{
    // TODO Entity::drawDebug implement
}

Entity::Entity()
    : _id(0), _parent(0), _dead(false), _active(true), _solid(false), _visible(true)
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
        else
            ++it;
    }
}

void Entity::addChild(Entity * entity)
{
    assert(entity);
    assert(_childs.find(entity) == _childs.end());

    _childs.insert(entity);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // TODO Entity::draw implement
    // onDraw(hint rect);
}


void Entity::removeChild(Entity * entity)
{
    assert(entity);
    assert(_childs.find(entity) != _childs.end());

    _childs.erase(entity);
}
