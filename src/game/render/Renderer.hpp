/**
 * @file   Renderer.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <deque>

#include <SFML/Graphics.hpp>

class Renderable;

class Renderer
{
public:
                        Renderer();

                        ~Renderer();


    void                render(sf::RenderTarget & target) const;


    sf::RenderTarget &  getRenderTarget() { return *_render_target; }


protected:
    friend class        Renderable;

    void                push(const Renderable * renderable);

    void                pop(const Renderable * renderable);


private:
    typedef const Renderable * RPtr;

    struct RenderComp
    {
        bool operator() (RPtr a, RPtr b) const;

    } _comparator;

    mutable sf::RenderTarget * _render_target;

    mutable std::deque<RPtr> _render_list;

};

#endif // _RENDERER_HPP_
