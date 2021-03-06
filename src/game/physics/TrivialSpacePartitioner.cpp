/**
 * @file   TrivialSpacePartitioner.cpp
 * @author Bastien Brunnenstein
 */

#include "game/physics/TrivialSpacePartitioner.hpp"

#include <algorithm>
#include <vector>

#include "game/physics/Collisions.hpp"
#include "game/entities/Entity.hpp"
#include "game/entities/World.hpp"
/*
namespace
{
    void buildEntityList(std::vector<Entity *> & entity_list, Entity * entity)
    {
        const Entity::EntityList & list = entity->getChilds();
        for (Entity::EntityList::iterator it = list.begin(); it != list.end(); ++it)
        {
            if ((*it)->isSolid())
                entity_list.push_back((*it));

            buildEntityList(entity_list, *it);
        }
    }

    bool orderComparator(const Entity * first, const Entity * second)
    {
        return first->getBounds().getLowerLimit().getX() < second->getBounds().getLowerLimit().getX();
    }
}

void TrivialSpacePartitioner::updateEntities(World * world)
{
    std::vector<Entity *> list;

    ::buildEntityList(list, world);

    std::sort(list.begin(), list.end(), ::orderComparator);

    // TODO TrivialSpacePartitioner:: move that block to computeCollisions
    for (std::vector<Entity *>::iterator it = list.begin(); it != list.end(); ++it)
    {
        float x_up = (*it)->getBounds().getUpperLimit().getX();

        std::vector<Entity *>::iterator it2 = it;
        ++it2;
        for (/ ** / ; it2 != list.end(); ++it2)
        {
            if ((*it2)->getBounds().getLowerLimit().getX() > x_up) break;

            //Collision::collides(*it, *it2);
        }
    }
}

SpacePartitioner::EntityList
TrivialSpacePartitioner::findEntitiesInRectangle(const sf::FloatRect & rectangle) const
{
    // TODO TrivialSpacePartitioner::findEntitiesInRectangle
    return EntityList();
}

SpacePartitioner::BodyList
TrivialSpacePartitioner::findBodiesInRectangle( const sf::FloatRect& rectangle) const
{
    // TODO TrivialSpacePartitioner::findBodiesInRectangle
    return BodyList();
}*/
