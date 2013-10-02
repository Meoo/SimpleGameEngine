/**
 * @file   WorldEntity.cpp
 * @author Bastien Brunnenstein
 */

#include "game/entities/WorldEntity.hpp"

WorldEntity::WorldEntity()
    : _next_entity_id(0)
{
}

Entity::Bounds WorldEntity::getBounds() const
{
    // TODO WorldEntity::getBounds
    return Bounds();
}

WorldEntity::BodyList WorldEntity::getBodies(const Bounds & area) const
{
    return BodyList();
}

void WorldEntity::update(sf::Time elapsed_time)
{
    // TODO WorldEntity::update collisions

    Entity::update(elapsed_time);
}
