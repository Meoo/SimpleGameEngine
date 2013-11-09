/**
 * @file   World.cpp
 * @author Bastien Brunnenstein
 */

#include "game/entities/World.hpp"

#include "game/physics/TrivialSpacePartitioner.hpp"

void World::update(sf::Time elapsed_time)
{
    // TODO WorldEntity::update collisions

    Entity::update(elapsed_time);
}
