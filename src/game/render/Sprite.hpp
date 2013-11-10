/**
 * @file   Sprite.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include <SFML/Graphics.hpp>

#include "resources/Resources.hpp"
#include "game/render/Renderable.hpp"

class Sprite : public Renderable, public sf::Sprite
{
public:
    explicit        Sprite(Renderer & renderer);

                    Sprite(Renderer & renderer, const TextureHandle & texture);

                    Sprite(Renderer & renderer, const TextureHandle & texture, const sf::IntRect & rectangle);

    virtual         ~Sprite() {}


    void            setTexture(const TextureHandle & texture, bool resetRect = false);

    // Shadows sf::Sprite::getTexture function
    const TextureHandle & getTexture() const        { return _texture; }


protected:
    virtual void    render() const;


private:
    TextureHandle   _texture;


    // Shadows sf::Sprite::setTexture function
    void            setTexture(const sf::Texture & texture, bool resetRect = false);

};

#endif // _SPRITE_HPP_
