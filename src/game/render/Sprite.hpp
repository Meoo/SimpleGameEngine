/**
 * @file   Sprite.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include <SFML/Graphics.hpp>

#include "resources/Resources.hpp"
#include "game/render/Renderable.hpp"

/**
 * Renderable sprite.
 *
 * Used to draw 2D images on the scene.
 * Also provide a handle to the texture in order to manage resources.
 */
class Sprite : public Renderable, public sf::Sprite
{
public:
    /**
     * Constructor.
     *
     * @param renderer
     */
    explicit        Sprite(Renderer & renderer);

    /**
     * Constructor.
     *
     * @param renderer
     * @param texture Texture of the sprite.
     */
                    Sprite(Renderer & renderer, const TextureHandle & texture);

    /**
     * Constructor.
     *
     * @param renderer
     * @param texture Texture of the sprite.
     * @param rectangle Rectangle in the texture to use.
     */
                    Sprite(Renderer & renderer, const TextureHandle & texture, const sf::IntRect & rectangle);

    /**
     * Destructor
     */
    virtual         ~Sprite() {}


    /**
     * Change the texture used by this Sprite.
     *
     * @param texture
     * @param resetRect
     */
    void            setTexture(const TextureHandle & texture, bool resetRect = false);

    /**
     * Get the texture used by this Sprite.
     *
     * Shadows sf::Sprite::getTexture function.
     *
     * @return Texture used by this Sprite.
     */
    const TextureHandle & getTexture() const        { return _texture; }


protected:
    virtual void    render() const;


private:
    /**
     * Handle to the texture being used.
     */
    TextureHandle   _texture;


    // Shadows sf::Sprite::setTexture function
    // Use the new setTexture instead
    void            setTexture(const sf::Texture & texture, bool resetRect = false);

};

#endif // _SPRITE_HPP_
