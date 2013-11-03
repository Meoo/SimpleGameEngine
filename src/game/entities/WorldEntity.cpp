/**
 * @file   WorldEntity.cpp
 * @author Bastien Brunnenstein
 */

#include "game/entities/WorldEntity.hpp"

#include "game/physics/TrivialSpacePartitioner.hpp"

void WorldEntity::update(sf::Time elapsed_time)
{
    // TODO WorldEntity::update collisions

    Entity::update(elapsed_time);
}
