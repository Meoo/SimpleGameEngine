/**
 * @file   Renderable.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

#include "game/render/Renderer.hpp"

/**
 * Base class for renderable objects.
 *
 * Renderable objects provide a depth parameter, allowing to automatically
 * draw the objects in the order you want.
 */
class Renderable
{
public:
    /**
     * Constructor.
     *
     * Push the object in the Renderer on construction.
     */
    explicit        Renderable(Renderer & renderer);

    /**
     * Constructor with depth parameter.
     *
     * Push the object in the Renderer on construction.
     *
     * @param depth Initial object depth.
     */
                    Renderable(Renderer & renderer, int depth);

    /**
     * Virtual destructor.
     *
     * Pop the object from the Renderer on destruction.
     */
    virtual         ~Renderable();


    /**
     * Get the current depth of the object.
     *
     * A higher value means the object will be behind.
     *
     * @return current depth value.
     */
    int             getDepth() const                        { return _depth; }

    /**
     * Change the depth of the object on the screen.
     *
     * A higher value means the object will be behind.
     *
     * @param depth New depth value.
     */
    void            setDepth(int depth)                     { _depth = depth; }


    /**
     * Get visibility state of the object
     *
     * An invisible object will not be drawn on screen.
     *
     * @return visibility state.
     */
    bool            isVisible() const                       { return _visible; }

    /**
     * Change the visibility of the object.
     *
     * An invisible object will not be drawn on screen.
     *
     * @param visible New visibility.
     */
    void            setVisible(bool visible)                { _visible = visible; }


protected:
    /**
     * Renderer must be friend in order to access the render function.
     */
    friend class    Renderer;

    /**
     * Actual render function. Overload it in child classes.
     */
    virtual void    render() const = 0;

    /**
     * Accessor to the Renderer, to be used in render function.
     *
     * @return The Renderer bound to this object.
     */
    Renderer &      getRenderer() const                     { return _renderer; }


private:
    /**
     * A renderable is bound to it's renderer.
     */
    Renderer &      _renderer;

    /**
     * Depth of the object on the screen.
     *
     * A higher value means the object will be behind.
     */
    int             _depth;

    /**
     * Visibility state of the object.
     */
    bool            _visible;

};

#endif // _RENDERABLE_HPP_
