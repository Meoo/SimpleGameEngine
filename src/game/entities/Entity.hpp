/**
 * @file   Entity.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <set>

#include <SFML/System/Time.hpp>

class World;

/**
 * Common interface for entities.
 *
 * Anything that exist on the world, or that can affect the world should be
 * an entity.
 *
 * Do not store a pointer to an Entity, instead, use Entity::Pointer, which is
 * a weak pointer using double linked lists.
 */
class Entity
{
public:
    class                               Pointer;

    class                               ConstPointer;

    typedef std::set<Entity *>          EntityList;

    typedef std::set<const Entity *>    ConstEntityList;


    //---- Constructor & Destructor

    /**
     * Constructor.
     *
     * @param parent of this entity.
     */
    explicit                Entity(Entity * parent);

    /**
     * Virtual destructor for inheritance.
     *
     * Release child entities and remove itself from it's parent list.
     */
    virtual                 ~Entity();


    //---- Accessors

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
     * TODO Entity::getChilds use iterators instead?
     *
     * @return
     */
    const EntityList &      getChilds()                 { return _childs; }

    /**
     * Get all the childs of this entity. (const)
     *
     * TODO Entity::getChilds use const iterators instead?
     *
     * @return
     */
    ConstEntityList         getChilds() const           { return ConstEntityList(_childs.begin(), _childs.end()); }

    /**
     * Get the world this entity is in.
     *
     * @return world
     */
    World *           getWorld()                  { return _world; }

    /**
     * Get the world this entity is in.
     *
     * @return world
     */
    const World *     getWorld() const            { return _world; }

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
     * An entity is active by default.
     *
     * You should use this function on entites that doesn't move or think,
     * such as MapEntity, as it will help optimizing the collisions.
     *
     * If you want an inactive entity to move, use #wake first, as inactive
     * entities can be handled specially in a SpacePartitioner. TODO Entity & activity, use a dirty flag instead?
     *
     * An inactive entity will still receive callbacks, and it's childs will
     * stil be updated if they are active.
     *
     * @return
     */
    bool                    isActive() const            { return _active; }


protected:
    //---- Callbacks

    // TODO Entity::onCollide def

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
     * @note Dead childs are removed from the child list at the end of
     *       the frame.
     *
     * @param child
     */
    virtual void            onChildDeath(const Entity * child) {}


private:
    /**
     * World have to be friend to use the constructor #Entity().
     */
    friend class World;

    /**
     * Weak pointer must have access to the first pointer property.
     */
    friend class Pointer;

    // ----

    /**
     * Parent of this entity.
     *
     * World have himself as parent, and should be the only one.
     */
    Entity *                _parent;

    /**
     * World this entity is in.
     *
     * It can be equal to the parent. World have itself as world.
     */
    World * const           _world;

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
     * Childs of this entity.
     */
    EntityList              _childs;

    /**
     * Head of the Pointer's double linked list.
     */
    Pointer *               _first_pointer;

    // ----

    /**
     * Special constructor to be used only by World.
     *
     * Set parent to null pointer, and inactive.
     *
     * @param this_world A pointer to the world, which should be "this".
     */
                            Entity(World * this_world);

    /**
     * Update this entity, and all child entities.
     *
     * #doUpdate is called if the entity is active.
     *
     * @param elapsed_time
     *
     * @see #onUpdate
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

};

// ----

/**
 * Weak pointer for entites.
 *
 * It uses a double linked list to keep track of all the pointers pointing
 * to an Entity.
 */
class Entity::Pointer
{
public:
    /**
     * Create an empty Entity pointer.
     */
                    Pointer();

    /**
     * Value constructor. Create pointer pointing to an Entity.
     *
     * @param pointee
     */
                    Pointer(Entity * pointee);

    /**
     * Copy constructor.
     */
                    Pointer(const Pointer & copy);

    /**
     * Destructor.
     */
                    ~Pointer();

    /**
     * Get the pointer, or NULL if the Entity does not exist.
     *
     * @return a pointer to an Entity, or NULL.
     */
    Entity *        get() const     { return _entity; }

    /**
     * Reset the pointer, so it does not point to anything.
     */
    void            reset();

    /**
     * Reset the pointer, so it point to another Entity.
     *
     * @param entity
     */
    void            reset(Entity * pointee);

private:
    /**
     * We must friend Entity so it can create
     */
    friend class    Entity;

    /**
     * Entity pointed by this Pointer.
     */
    Entity *        _entity;

    /**
     * Previous pointer in the double linked list.
     */
    mutable Pointer * _previous;

    /**
     * Next pointer in the double linked list.
     */
    mutable Pointer * _next;
};

// ----

/**
 * Weak pointer for entites (constant version).
 *
 * It uses a double linked list to keep track of all the pointers pointing
 * to an Entity.
 */
class Entity::ConstPointer
{
public:
    /**
     * Create an empty Entity pointer.
     */
                    ConstPointer()
                        {}

    /**
     * Value constructor. Create pointer pointing to an Entity.
     *
     * @param pointee
     */
                    ConstPointer(const Entity * pointee)
                        : _pointer(const_cast<Entity*>(pointee)) {}

    /**
     * Copy constructor.
     */
                    ConstPointer(const ConstPointer & copy)
                        : _pointer(copy._pointer) {}

    /**
     * Pointer conversion constructor.
     */
                    ConstPointer(const Pointer & copy)
                        : _pointer(copy) {}

    /**
     * Get the pointer, or NULL if the Entity does not exist.
     *
     * @return a pointer to an Entity, or NULL.
     */
    const Entity *  get() const
                        { return _pointer.get(); }

    /**
     * Reset the pointer, so it does not point to anything.
     */
    void            reset()
                        { _pointer.reset(); }

    /**
     * Reset the pointer, so it point to another Entity.
     *
     * @param entity
     */
    void            reset(const Entity * pointee)
                        { _pointer.reset(const_cast<Entity*>(pointee)); }

private:
    /**
     * Wrapped Enitity Pointer.
     */
    Pointer         _pointer;

};

#endif // _ENTITY_HPP_
