/**
 * @file   TrivialSpacePartitioner.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _TRIVIALSPACEPARTITIONER_HPP_
#define _TRIVIALSPACEPARTITIONER_HPP_

#include "game/physics/SpacePartitioner.hpp"

class TrivialSpacePartitioner : public SpacePartitioner
{
public:
                TrivialSpacePartitioner() {}

    virtual     ~TrivialSpacePartitioner() {}

    void        updateEntities(World * world);

    EntityList  findEntitiesInRectangle(const sf::FloatRect & rectangle) const;

    BodyList    findBodiesInRectangle(const sf::FloatRect & rectangle) const;

};

#endif // _TRIVIALSPACEPARTITIONER_HPP_
