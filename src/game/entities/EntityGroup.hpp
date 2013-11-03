/**
 * @file   EntityGroup.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _ENTITYGROUP_HPP_
#define _ENTITYGROUP_HPP_

#include "game/entities/Entity.hpp"

/**
 * A group of entities.
 *
 * Basically, it's a non solid, non visible and non active Entity.
 */
class EntityGroup : public Entity
{
public:
                        EntityGroup(Entity * parent) : Entity(parent)
                            { setActive(false); }

    virtual             ~EntityGroup()
                            {}

};

#endif // _ENTITYGROUP_HPP_
