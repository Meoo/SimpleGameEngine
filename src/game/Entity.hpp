/**
 * @file   Entity.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

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

    virtual void onCollideTile  (const MapTile * tile,  const CollisionData * collision_data) = 0;

    virtual void onCollideEntity(const Entity * entity, const CollisionData * collision_data) = 0;

    //---- Accessors

    Id                      getId() const { return _id; }

    virtual CollisionStyle  getCollisionStyle() const = 0;

    virtual CollisionMask   getCollisionMask() const = 0;

    virtual sf::FloatRect   getBounds() const = 0;

    virtual sf::FloatRect   getRenderBounds() const { return getBounds(); }

    virtual sf::Vector2f    getVelocity() const = 0;

#ifndef NDEBUG
protected:
    void                    drawCollisionMask(sf::RenderTarget & target, sf::RenderStates states) const;
#endif

private:
    Id _id;

};

#endif // _ENTITY_HPP_
