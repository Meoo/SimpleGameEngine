/**
 * @file   Renderable.cpp
 * @author Bastien Brunnenstein
 */

#include "game/render/Renderable.hpp"

Renderable::Renderable(Renderer & renderer)
    : _renderer(renderer), _depth(0), _visible(true)
{
    _renderer.push(this);
}

Renderable::Renderable(Renderer & renderer, int depth)
    : _renderer(renderer), _depth(depth), _visible(true)
{
    _renderer.push(this);
}

Renderable::~Renderable()
{
    _renderer.pop(this);
}
