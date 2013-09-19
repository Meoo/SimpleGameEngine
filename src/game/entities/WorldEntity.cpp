/**
 * @file   WorldEntity.cpp
 * @author Bastien Brunnenstein
 */

#include "game/entities/WorldEntity.hpp"

WorldEntity::WorldEntity()
    : _next_entity_id(0)
{
}

WorldEntity::~WorldEntity()
{
    // TODO free memory ~WorldEntity
}

sf::FloatRect WorldEntity::getBounds() const
{
    // TODO WorldEntity::getBounds
    return sf::FloatRect();
}

WorldEntity::BodyList WorldEntity::getBodies(const sf::FloatRect & area) const
{
    return BodyList();
}

void WorldEntity::update(sf::Time elapsed_time)
{
    // TODO WorldEntity::update collisions

    Entity::update(elapsed_time);

    // TODO WorldEntity::update free dead entities
}
