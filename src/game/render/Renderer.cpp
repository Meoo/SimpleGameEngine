/**
 * @file   Renderer.cpp
 * @author Bastien Brunnenstein
 */

#include <algorithm>
#include <cassert>

#include "game/render/Renderer.hpp"
#include "game/render/Renderable.hpp"

Renderer::Renderer()
    : _render_target(0)
{
}

Renderer::~Renderer()
{
}

void Renderer::render(sf::RenderTarget & target) const
{
    _render_target = &target;

    std::make_heap(_render_list.begin(), _render_list.end(), _comparator);

    for (std::deque<RPtr>::iterator it = _render_list.begin();
            it != _render_list.end(); ++it)
    {
        (*it)->render();
    }
}

void Renderer::push(const Renderable * renderable)
{
    assert(renderable);

    _render_list.push_back(renderable);
    std::push_heap(_render_list.begin(), _render_list.end(), _comparator);
}

void Renderer::pop(const Renderable * renderable)
{
    assert(renderable);

    for (std::deque<RPtr>::iterator it = _render_list.begin();
            it != _render_list.end(); ++it)
    {
        if (*it == renderable)
        {
            _render_list.erase(it);
            return;
        }
    }

    assert(false && "Renderable not found in render list");
}

bool Renderer::RenderComp::operator () (RPtr a, RPtr b) const
{
    return a->getDepth() < b->getDepth();
}
