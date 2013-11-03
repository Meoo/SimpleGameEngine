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
                        WorldEntity()                   {}

    virtual             ~WorldEntity()                  {}

    /**
     * Entity#update function is exposed on the world entity.
     *
     * This will check collisions between all the entities and update them.
     *
     * @param elapsed_time
     */
    virtual void        update(sf::Time elapsed_time);


private:
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

};

#endif // _WORLDENTITY_HPP_
