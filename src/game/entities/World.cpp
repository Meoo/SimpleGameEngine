/**
 * @file   World.cpp
 * @author Bastien Brunnenstein
 */

#include "game/entities/World.hpp"

World::World(Renderer& renderer)
    : Entity(this), _renderer(renderer)
{
}

void World::update(sf::Time elapsed_time)
{
    // TODO World::update collisions

    Entity::update(elapsed_time);
}
