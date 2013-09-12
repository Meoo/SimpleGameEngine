/**
 * @file   GameScreen.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _GAMESCREEN_HPP_
#define _GAMESCREEN_HPP_

#include "Screen.hpp"

#include "resources/Resources.hpp"
#include "game/Animation.hpp"
#include "game/Tileset.hpp"

class GameScreen : public Screen
{
public:
    GameScreen();

    virtual ~GameScreen() {}

    virtual Screen * update(sf::Time elapsed_time);

    virtual void onKeyPressed(sf::Keyboard::Key key);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    AnimationSetHandle anim;

    AnimationInstance animi;

    TextureHandle texture;

    Tileset tileset;

};

#endif // _GAMESCREEN_HPP_
