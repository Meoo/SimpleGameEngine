/**
 * @file   Sprite.cpp
 * @author Bastien Brunnenstein
 */

#include "game/render/Sprite.hpp"

Sprite::Sprite(Renderer & renderer)
    : Renderable(renderer)
{
}

Sprite::Sprite(Renderer & renderer, const TextureHandle & texture)
    : Renderable(renderer), sf::Sprite(texture.get()), _texture(texture)
{
}

Sprite::Sprite(Renderer & renderer, const TextureHandle & texture, const sf::IntRect & rectangle)
    : Renderable(renderer), sf::Sprite(texture.get(), rectangle), _texture(texture)
{
}

void Sprite::setTexture(const TextureHandle & texture, bool resetRect)
{
    _texture.reset(texture);
    sf::Sprite::setTexture(texture.get(), resetRect);
}

void Sprite::render() const
{
    getRenderer().getRenderTarget().draw(*this);
}
