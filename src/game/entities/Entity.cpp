/**
 * @file   Entity.cpp
 * @author Bastien Brunnenstein
 */

#include "game/entities/Entity.hpp"

#include "game/entities/WorldEntity.hpp"

Entity::Entity(Entity * parent)
    : _id(parent->getWorld()->allocateEntityId())
    , _parent(parent), _dead(false), _active(true), _solid(true)
{
    _parent->addChild(this);
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
    _parent->removeChild(this);
    _parent = parent;
    _parent->addChild(this);
}

void Entity::drawDebug(sf::RenderTarget & target, sf::RenderStates states) const
{
    // TODO implement Entity::drawDebug
}

Entity::Entity()
    : _id(0), _parent(0), _dead(false), _active(true), _solid(false)
{
}

void Entity::update(sf::Time elapsed_time)
{
    if (isActive())
        onUpdate(elapsed_time);

    for (EntityList::iterator it = _childs.begin(); it != _childs.end(); ++it)
    {
        Entity * child = (*it);

        child->update(elapsed_time);

        if (child->isDead())
            onChildDeath(child);
    }
}

void Entity::addChild(Entity * entity)
{
    _childs.insert(entity);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // TODO implement Entity::draw
    // onDraw(hint rect);
}

void Entity::removeChild(Entity * entity)
{
    _childs.erase(entity);
}
