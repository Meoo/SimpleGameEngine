/**
 * @file   Renderer.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <deque>

#include <SFML/Graphics.hpp>

class Renderable;

/**
 * Renderer, used to render scenes.
 *
 * Renderable objects are bound to a Renderer on construction.
 * It allow the Renderer to actually manage the objects.
 */
class Renderer
{
public:
    /**
     * Constructor.
     */
                        Renderer();

    /**
     * Destructor.
     */
                        ~Renderer() {}


    /**
     * Render the scene on screen.
     *
     * @param target Render target.
     */
    void                render(sf::RenderTarget & target) const;


    /**
     * Get current render target. May change between every frame.
     *
     * @return Current SFML render target.
     */
    sf::RenderTarget &  getRenderTarget() { return *_render_target; }


protected:
    /**
     * Renderable must be friend in order to access push and pop functions.
     */
    friend class        Renderable;

    /**
     * Push a renderable in the list of objects to be rendered.
     *
     * @param renderable Object to insert.
     */
    void                push(const Renderable * renderable);

    /**
     * Pop a renderable out of the list of objects to be rendered.
     *
     * @param renderable Object to remove.
     */
    void                pop(const Renderable * renderable);


private:
    typedef const Renderable * RPtr;

    /**
     * Comparator used to sort the render list.
     */
    struct RenderComp
    {
        bool operator() (RPtr a, RPtr b) const;

    } _comparator;

    /**
     * Current render target. May change between every frame.
     */
    mutable sf::RenderTarget *  _render_target;

    /**
     * Render list, containing every objects to be rendered.
     *
     * As the objects' depth may change, the list is sorted again every frame.
     */
    mutable std::deque<RPtr>    _render_list;

};

#endif // _RENDERER_HPP_
