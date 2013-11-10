/**
 * @file   World.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "game/entities/Entity.hpp"
#include "game/render/Renderer.hpp"

#include "game/render/Sprite.hpp"

/**
 * The world is the root entity, father of everything.
 *
 * The world allocates identifiers to other entities.
 */
class World : public Entity
{
public:
    /**
     * World constructor.
     *
     * @param renderer The Renderer entities in this world will depend on.
     */
    explicit            World(Renderer & renderer);

    /**
     * Virtual destructor.
     */
    virtual             ~World() {}

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
     * Renderer used to display this world.
     */
    Renderer & _renderer;

};

#endif // _WORLDE_HPP_
