/**
 * @file   World.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "game/entities/Entity.hpp"

/**
 * The world is the root entity, father of everything.
 *
 * The world allocates identifiers to other entities.
 */
class World : public Entity
{
public:
                        World() : Entity(this)    {}

    virtual             ~World()                  {}

    /**
     * Entity#update function is exposed on the world entity.
     *
     * This will check collisions between all the entities and update them.
     *
     * @param elapsed_time
     */
    virtual void        update(sf::Time elapsed_time);

};

#endif // _WORLDE_HPP_
