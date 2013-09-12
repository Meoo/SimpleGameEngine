/**
 * @file   Collisions.cpp
 * @author Bastien Brunnenstein
 */

#include "game/Collisions.hpp"

#include <iostream>
#include <cmath>

#include "game/Entity.hpp"
#include "game/Map.hpp"

void Collision::checkCollisionEntityTile(const Entity * entity, const MapTile * tile,
                                         CollisionData * output)
{
    sf::FloatRect rect(tile->position.x, tile->position.y, 1, 1);
    checkCollision(entity->getBounds(), entity->getCollisionMask(), entity->getCollisionStyle(),
                   rect, tile->collision_mask, tile->collision_style,
                   entity->getVelocity(), output);
}

void Collision::checkCollisionEntityEntity(const Entity * first, const Entity * second,
                                           CollisionData * output)
{
    checkCollision(first->getBounds(), first->getCollisionMask(), first->getCollisionStyle(),
                   second->getBounds(), second->getCollisionMask(), second->getCollisionStyle(),
                   (first->getVelocity() - second->getVelocity()), output);
}

void Collision::checkCollision(const sf::FloatRect & first_bounds, CollisionMask first_mask, CollisionStyle first_style,
                               const sf::FloatRect & second_bounds, CollisionMask second_mask, CollisionStyle second_style,
                               const sf::Vector2f & force, CollisionData * output)
{
    if (!first_bounds.intersects(second_bounds))
    {
        output->collides = false;
        return;
    }

    // TODO Handle every collision style
    if ((first_style != COLLISION_STYLE_BOUNDING_BOX) || (second_style != COLLISION_STYLE_BOUNDING_BOX))
        std::cerr << "Only COLLISION_STYLE_BOUNDING_BOX are handled actually" << std::endl;

    // TODO Collisions ... :(
    output->collides = false;
}
