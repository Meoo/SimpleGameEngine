/**
 * @file   Entity.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include "game/Collisions.hpp"

class Entity : public sf::Drawable
{
public:
    typedef unsigned Id;

    //---- Constructor & Destructor

    // Note that the entity must be pushed onto the World to exist
    Entity(Id id) : _id(id) {}

    virtual ~Entity() {}

    //---- Functions

    virtual void update(sf::Time elapsed_time) = 0;

    //---- Callbacks

    virtual void onCollideTile(const MapTileCollision & collision_data) = 0;

    virtual void onCollideEntity(const EntityCollision & collision_data) = 0;

    //---- Accessors

    Id                      getId() const { return _id; }

    virtual CollisionStyle  getCollisionStyle() = 0;

    virtual CollisionMask   getCollisionMask() = 0;

    virtual sf::FloatRect   getBounds() = 0;

    virtual sf::FloatRect   getRenderBounds() { return getBounds(); }

    virtual sf::Vector2f    getVelocity() = 0;

private:
    Id _id;

};

#endif // _ENTITY_HPP_
