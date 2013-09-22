/**
 * @file   TrivialSpacePartitioner.cpp
 * @author Bastien Brunnenstein
 */

#include "game/physics/TrivialSpacePartitioner.hpp"

#include "game/physics/Collisions.hpp"
#include "game/entities/Entity.hpp"
#include "game/entities/WorldEntity.hpp"

namespace
{
    void buildEntityList(SpacePartitioner::EntityList & entity_list, Entity * entity)
    {
        const Entity::EntityList & list = entity->getChilds();
        for (Entity::EntityList::iterator it = list.begin(); it != list.end(); ++it)
        {
            if ((*it)->isSolid())
                entity_list.insert((*it));

            buildEntityList(entity_list, *it);
        }
    }
}

void TrivialSpacePartitioner::updateEntities(WorldEntity * world)
{
    Entity::EntityList list;

    buildEntityList(list, world);

    for (Entity::EntityList::iterator it = list.begin(); it != list.end(); ++it)
    {
        Entity::EntityList::iterator it2 = it;
        ++it2;
        for (/**/ ; it2 != list.end(); ++it2)
        {
            //Collision::collides(*it, *it2);
        }
    }
}

SpacePartitioner::EntityList
TrivialSpacePartitioner::findEntitiesInRectangle(const sf::FloatRect & rectangle) const
{
    return EntityList();
}

SpacePartitioner::BodyList
TrivialSpacePartitioner::findBodiesInRectangle( const sf::FloatRect& rectangle) const
{
    return BodyList();
}
