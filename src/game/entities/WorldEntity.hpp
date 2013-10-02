/**
 * @file   WorldEntity.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _WORLDENTITY_HPP_
#define _WORLDENTITY_HPP_

#include "game/entities/Entity.hpp"

/**
 * The world is the root entity, father of everything.
 *
 * The world allocates identifiers to other entities.
 */
class WorldEntity : public Entity
{
public:
                        WorldEntity();

    virtual             ~WorldEntity()                  {}

    virtual Vector      getOrigin() const               { return Vector(); }

    virtual Bounds      getBounds() const;

    virtual BodyList    getBodies(const Bounds & area = Bounds()) const;

    /**
     * Entity#update function is exposed on the world entity.
     *
     * This will check collisions between all the entities and update them.
     *
     * @param elapsed_time
     */
    virtual void        update(sf::Time elapsed_time);

protected:
    friend class Entity;

    /**
     * Return an unique identifier for a new entity.
     *
     * _next_entity_id is initialized to 0, so we can have to use pre
     * incrementation as 0 is reserved for the world.
     *
     * @return
     */
    Id                      allocateEntityId()              { return ++_next_entity_id; }

private:
    /**
     * Next unique identifier for entities.
     *
     * Initialized to 0, and pre incremented in #allocateEntityId.
     */
    Id                      _next_entity_id;

    //----

    /**
     * Private virtual function, only overrided by WorldEntity.
     *
     * @return this.
     *
     * @see Entity#getWorld
     * @see Entity#getWorldImpl
     */
    virtual WorldEntity *   getWorldImpl()                  { return this; }

    /**
     * Private virtual function, only overrided by WorldEntity. (const)
     *
     * @return this.
     *
     * @see Entity#getWorld
     * @see Entity#getWorldImpl
     */
    virtual const WorldEntity * getWorldImpl() const        { return this; }

    /**
     * Private virtual function, only overrided by WorldEntity. (const)
     *
     * @return Origin vector (0, 0).
     *
     * @see Entity#getWorldOrigin
     * @see Entity#getWorldOriginImpl
     */
    virtual Vector          getWorldOriginImpl() const      { return Vector(); }

};

#endif // _WORLDENTITY_HPP_
