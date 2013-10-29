/**
 * @file   Entity.cpp
 * @author Bastien Brunnenstein
 */

#include "game/entities/Entity.hpp"

#include <cassert>

#include <SFML/Graphics.hpp>

#include "Config.hpp"
#include "game/entities/WorldEntity.hpp"

Entity::Entity(Entity * parent)
    : _parent(parent), _dead(false), _active(true), _solid(true), _visible(true), _first_pointer(0)
{
    assert(parent);

    _parent->addChild(this);
}

Entity::~Entity()
{
    assert(!_parent);

    // Release all childs
    for (EntityList::iterator it = _childs.begin(); it != _childs.end(); ++it)
    {
        Entity * child = (*it);

        child->_parent = 0;
        delete child;
    }

    // Clean all weak pointers
    for (Pointer * p = _first_pointer; p != 0; p = p->_next)
        p->_entity = 0;
}

void Entity::setParent(Entity * parent)
{
    assert(parent);

    _parent->removeChild(this);
    _parent = parent;
    _parent->addChild(this);
}

#ifndef NDEBUG

void Entity::drawDebug(sf::RenderTarget & target, sf::RenderStates states) const
{
    for (EntityList::iterator it = _childs.begin(); it != _childs.end(); ++it)
        (*it)->drawDebug(target, states);

    if (!isSolid()) return;

    sf::VertexArray vertarray(sf::LinesStrip);

    const sf::Vector2f & view_size = target.getView().getSize();
    const sf::Vector2f & view_cent = target.getView().getCenter();

    Bounds view_bounds(Vector(view_cent.x - view_size.x / 2, view_cent.y - view_size.y / 2),
                       Vector(view_cent.x + view_size.x / 2, view_cent.y + view_size.y / 2));

    BodyList list = getBodies(view_bounds);

    for (BodyList::iterator it = list.begin(); it != list.end(); ++it)
    {
        Vector half_size = (*it).size / 2;
        Vector center = (*it).position;
        Vector inertia = (*it).inertia;

        switch((*it).shape)
        {
        case COLLISION_SHAPE_SQUARE:
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

/*        case COLLISION_SHAPE_DIAMOND:
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

        case COLLISION_SHAPE_OCTAGON:
            // TODO Entity::drawDebug check COLLISION_SHAPE_OCTAGON draw
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX() * .4f, center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX() * .4f, center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY() * .4f), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() - half_size.getY() * .4f), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX() * .4f, center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX() * .4f, center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() - half_size.getY() * .4f), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() + half_size.getY() * .4f), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX() * .4f, center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

        case COLLISION_SHAPE_CIRCLE:
            // TODO Entity::drawDebug implement COLLISION_SHAPE_CIRCLE draw
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

        case COLLISION_SHAPE_CORNER_TOP_LEFT:
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

        case COLLISION_SHAPE_CORNER_TOP_RIGHT:
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

        case COLLISION_SHAPE_CORNER_BOTTOM_LEFT:
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

        case COLLISION_SHAPE_CORNER_BOTTOM_RIGHT:
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

        case COLLISION_SHAPE_TRIANGLE_UP:
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

        case COLLISION_SHAPE_TRIANGLE_DOWN:
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

        case COLLISION_SHAPE_TRIANGLE_LEFT:
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;

        case COLLISION_SHAPE_TRIANGLE_RIGHT:
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() - half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() - half_size.getX(), center.getY() + half_size.getY()), DEBUG_DRAW_SHAPE_COLOR));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + half_size.getX(), center.getY()), DEBUG_DRAW_SHAPE_COLOR));
            break;*/

        default:
            assert(false && "Unable to draw invalid shape");
            break;
        }

        target.draw(vertarray);
        vertarray.clear();

        if (inertia.getLength() > 0)
        {
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX(), center.getY()), DEBUG_DRAW_INERTIA_COLOR_B));
            vertarray.append(sf::Vertex(sf::Vector2f(
                    center.getX() + inertia.getX() * DEBUG_DRAW_INERTIA_SCALE,
                    center.getY() + inertia.getY() * DEBUG_DRAW_INERTIA_SCALE),
                                        DEBUG_DRAW_INERTIA_COLOR_E));

            target.draw(vertarray);
        }
    }
}

#endif

Entity::Entity()
    : _parent(0), _dead(false), _active(true), _solid(false), _visible(true), _first_pointer(0)
{
}

void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    if (isVisible())
        onDraw(target, states);

    for (EntityList::const_iterator it = _childs.begin(); it != _childs.end(); ++it)
        target.draw(**it);
}

void Entity::update(sf::Time elapsed_time)
{
    // Update self
    if (isActive())
        onUpdate(elapsed_time);

    // Update childs
    for (EntityList::iterator it = _childs.begin(); it != _childs.end(); ++it)
    {
        Entity * child = (*it);

        child->update(elapsed_time);

        if (child->isDead())
            onChildDeath(child);
    }

    // Release dead childs
    for (EntityList::iterator it = _childs.begin(); it != _childs.end(); /**/)
    {
        Entity * child = (*it);

        if ((*it)->isDead())
        {
            _childs.erase(it);

            child->_parent = 0;
            delete child;
        }

        ++it;
    }
}

void Entity::addChild(Entity * entity)
{
    assert(entity);
    assert(_childs.find(entity) == _childs.end());

    _childs.insert(entity);
}

void Entity::removeChild(Entity * entity)
{
    assert(entity);
    assert(_childs.find(entity) != _childs.end());

    _childs.erase(entity);
}

// ----

Entity::Pointer::Pointer()
    : _entity(0), _previous(0), _next(0)
{
}

Entity::Pointer::Pointer(Entity * pointee)
    : _entity(pointee), _previous(0)
{
    if (pointee)
    {
        _next->_previous = this;
        pointee->_first_pointer = this;
        _next = pointee->_first_pointer;
    }
    else
    {
        _next = 0;
    }
}

Entity::Pointer::Pointer(const Pointer & copy)
    : _entity(copy._entity), _previous(const_cast<Pointer*>(&copy)), _next(copy._next)
{
    copy._next = this;
}

Entity::Pointer::~Pointer()
{
    reset();
}

void Entity::Pointer::reset()
{
    if (_entity)
    {
        if (!_previous)
        {
            _entity->_first_pointer = _next;
        }
        else
        {
            _previous->_next = _next;
        }
        _next->_previous = _previous;
    }
}

void Entity::Pointer::reset(Entity * pointee)
{
    reset();

    _entity = pointee;
    if (pointee)
    {
        _previous = 0;
        _next = _entity->_first_pointer;
        _next->_previous = this;
        _entity->_first_pointer = this;
    }
}
