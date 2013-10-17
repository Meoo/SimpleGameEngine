/**
 * @file   WorldEntity.cpp
 * @author Bastien Brunnenstein
 */

#include "game/entities/WorldEntity.hpp"

#include "game/physics/TrivialSpacePartitioner.hpp"

WorldEntity::WorldEntity()
    : _next_entity_id(0), _space_partitioner(new TrivialSpacePartitioner())
{
    setActive(false);
    setVisible(false);
    setSolid(false);
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
    _space_partitioner->updateEntities(this);

    // TODO WorldEntity::update collisions

    Entity::update(elapsed_time);
}
