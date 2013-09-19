/**
 * @file   Entity.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <set>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>

#include "game/physics/Body.hpp"

class WorldEntity;

/**
 * Common interface for entities.
 *
 * Anything that exist on the world, or that can affect the world should be
 * an entity.
 */
class Entity : public sf::Drawable
{
public:
    typedef unsigned                    Id;

    typedef std::set<Entity *>          EntityList;

    typedef std::set<const Entity *>    ConstEntityList;

    typedef std::set<Body>              BodyList; // TODO use pointers?


    //---- Constructor & Destructor

    /**
     * Constructor.
     *
     * @param parent of this entity.
     */
    explicit                Entity(Entity * parent);

    /**
     * Virtual destructor for inheritance.
     */
    virtual                 ~Entity() {}


    //---- Functions

    /**
     * Find a child entity with given id.
     *
     * @param entity_id
     * @return Entity with this identifier or null pointer.
     */
    Entity *                findEntity(Id entity_id);

    /**
     * Find a child entity with given id. (const)
     *
     * @param entity_id
     * @return Entity with this identifier or null pointer.
     */
    const Entity *          findEntity(Id entity_id) const;


    //---- Accessors

    /**
     * Get the unique identifier of this entity.
     *
     * @return identifier
     */
    Id                      getId() const               { return _id; }

    /**
     * Get the origin of this entity, relative to it's parent.
     *
     * @return
     */
    virtual sf::Vector2f    getOrigin() const = 0;

    /**
     * Get the origin of this entity, relative to the world.
     *
     * @return
     */
    sf::Vector2f            getWorldOrigin() const      { return getWorldOriginImpl(); }

    /**
     * Change the parent of this entity.
     *
     * @param parent
     */
    void                    setParent(Entity * parent);

    /**
     * Get the parent of this entity.
     *
     * @return parent
     */
    Entity *                getParent()                 { return _parent; }

    /**
     * Get the parent of this entity. (const)
     *
     * @return parent
     */
    const Entity *          getParent() const           { return _parent; }


    /**
     * Get all the childs of this entity.
     *
     * TODO use iterators instead?
     *
     * @return
     */
    const EntityList &      getChilds()                 { return _childs; }

    /**
     * Get all the childs of this entity. (const)
     *
     * TODO use const iterators instead?
     *
     * @return
     */
    ConstEntityList         getChilds() const           { return ConstEntityList(_childs.begin(), _childs.end()); }

    /**
     * Get the world this entity is in.
     *
     * @return world
     */
    WorldEntity *           getWorld()                  { return getWorldImpl(); }

    /**
     * Get the world this entity is in.
     *
     * @return world
     */
    const WorldEntity *     getWorld() const            { return getWorldImpl(); }

    /**
     * Get the physical bounds of this entity.
     *
     * The returned rectangle should be as small as possible, as it will be
     * used by Quadtree to locate this entity in the world.
     *
     * @note Child entities does not have to be in it's parent's bounds.
     *
     * @return rectangle covering the physical representation of the entity.
     */
    virtual sf::FloatRect   getBounds() const = 0;

    /**
     * Get bodies representing physically this entity.
     *
     * All the bodies should be included in the rectangle returned by
     * #getBounds, or collisions will be chaotic.
     *
     * If you do not want your entity to be solid, return an empty list
     * and use #setSolid to set the entity to a non solid state.
     *
     * TODO const return?
     *
     * @param area (optional) rectangle which the returned bodies should
     *             intersect with.
     *             It is a hint used to reduce the number of results.
     *             If no area is given, all bodies should be returned.
     *
     * @return
     */
    virtual BodyList        getBodies(const sf::FloatRect & area = sf::FloatRect()) const = 0;

    /**
     * Get the visual bounds of this entity.
     *
     * The returned rectangle should be as small as possible, as it will be
     * used by draw functions to optimize out this entity when it is
     * out of the screen.
     *
     * @return rectangle covering the visual representation of the entity.
     */
    virtual sf::FloatRect   getRenderBounds() const     { return getBounds(); }

    /**
     * Mark this entity as dead.
     *
     * Killing an entity will also kill it's childrens.
     *
     * @see #isDead
     */
    void                    kill()                      { _dead = true; }

    /**
     * Check if this entity is marked for removal.
     *
     * An entity with this flag will be removed from the World before next
     * frame, and it's direct parent will be notified.
     *
     * @return
     *
     * @see #onChildDeath
     */
    bool                    isDead() const              { return _dead; }

    /**
     * Set the activity state of this entity.
     *
     * @param active
     *
     * @see #isActive
     */
    void                    setActive(bool active)      { _active = active; }

    /**
     * Check if this entity is active or inactive.
     *
     * An inactive entity won't see it's #update function called.
     *
     * Entities are active by default.
     *
     * You should use this function on entites that doesn't move or think,
     * such as MapEntity, as it will help optimizing the collisions.
     *
     * If you want an inactive entity to move, use #wake first, as inactive
     * entities can be handled specially in a SpacePartitioner. TODO use a dirty flag instead?
     *
     * An inactive entity will still receive callbacks, and it's childs will
     * stil be updated if they are active.
     *
     * @return
     */
    bool                    isActive()                  { return _active; }

    /**
     * Set the solidity state of this entity.
     *
     * @param solid
     *
     * @see #isSolid
     */
    void                    setSolid(bool solid)        { _solid = solid; }

    /**
     * Check if this entity is solid or not.
     *
     * A solid entity will be able to collide with other entities, even
     * if #getBodies return value is not empty.
     *
     * An entity is solid by default.
     *
     * @return
     */
    bool                    isSolid()                   { return _solid; }

#ifndef NDEBUG
    /**
     * Draw this entity's and all child entities' collision masks.
     *
     * @param target
     * @param states
     */
    void                    drawDebug(sf::RenderTarget & target, sf::RenderStates states) const;
#endif


protected:
    //---- Callbacks

    // TODO onCollide

    /**
     * Called every frame.
     *
     * This function will not be called if the entity is inactive.
     *
     * An entity is updated before it's childrens.
     *
     * @param elapsed_time
     */
    virtual void            onUpdate(sf::Time elapsed_time) {}

    /**
     * Called when a direct child of this entity dies.
     *
     * @note Dead childs are not removed from the child list before this
     *       function is called.
     *
     * @param child
     */
    virtual void            onChildDeath(const Entity * child) {}

    // TODO onDraw(hint rect)

    void                    draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
    /**
     * WorldEntity have to be friend to use the constructor #Entity(), and
     * to override #getWorldImpl.
     */
    friend WorldEntity;

    // ----

    /**
     * Unique identifier for this entity.
     *
     * Identifier 0 is reserved for the WorldEntity.
     */
    Id                      _id;

    /**
     * Parent of this entity.
     *
     * WorldEntity have a null pointer as parent, and it should be the only one.
     */
    Entity *                _parent;

    /**
     * Flag indicating if this entity should be withdrawn out of the World.
     *
     * @see #isDead
     */
    bool                    _dead;

    /**
     * Flag indicating if this entity is active.
     *
     * An inactive entity won't see it's #update function called.
     *
     * @see #isActive
     */
    bool                    _active;

    /**
     * Flag indicating if this entity is solid.
     *
     * A non-solid entity won't be able to collide anything.
     *
     * @see #isSolid
     */
    bool                    _solid;

    /**
     * Childs of this entity.
     */
    EntityList              _childs;

    // ----

    /**
     * Special constructor to be used only by WorldEntity.
     *
     * Set id to 0 and parent to null pointer.
     */
                            Entity();

    /**
     * Update this entity, and all child entities.
     *
     * #doUpdate is called if the entity is active.
     *
     * @param elapsed_time
     *
     * @see #doUpdate
     */
    void                    update(sf::Time elapsed_time);

    /**
     * Internal function used by #setParent to add a child to this entity.
     *
     * @param entity
     */
    void                    addChild(Entity * entity);

    /**
     * Internal function used by #setParent to remove a child from this entity.
     *
     * @note Because it is internal, this function should never fail, and will throw
     *       an exception if parameter entity is not a child of this entity.
     *
     * @param entity
     */
    void                    removeChild(Entity * entity);

    /**
     * Private virtual function, only overrided by WorldEntity.
     *
     * @return the world this entity is in.
     *
     * @see #getWorld
     * @see WorldEntity#getWorldImpl
     */
    virtual WorldEntity *   getWorldImpl()              { return _parent->getWorld(); }

    /**
     * Private virtual function, only overrided by WorldEntity. (const)
     *
     * @return the world this entity is in.
     *
     * @see #getWorld
     * @see WorldEntity#getWorldImpl
     */
    virtual const WorldEntity * getWorldImpl() const    { return _parent->getWorld(); }

    /**
     * Private virtual function, only overrided by WorldEntity.
     *
     * @return the origin of this entity, relative to the world.
     *
     * @see #getWorld
     * @see WorldEntity#getWorldImpl
     */
    virtual sf::Vector2f    getWorldOriginImpl() const  { return _parent->getWorldOrigin() + getOrigin(); }

};

#endif // _ENTITY_HPP_
