/**
 * @file   Renderable.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

#include "game/render/Renderer.hpp"

class Renderable
{
public:
                    Renderable(Renderer & renderer);

    explicit        Renderable(Renderer & renderer, int depth);

    virtual         ~Renderable();


    int             getDepth() const                        { return _depth; }

    void            setDepth(int depth)                     { _depth = depth; }


    bool            isVisible() const                       { return _visible; }

    void            setVisible(bool visible)                { _visible = visible; }


protected:
    friend class    Renderer;

    virtual void    render() const = 0;

    Renderer &      getRenderer() const                     { return _renderer; }


private:
    Renderer &      _renderer;

    int             _depth;

    bool            _visible;

};

#endif // _RENDERABLE_HPP_
