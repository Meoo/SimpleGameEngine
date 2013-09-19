/**
 * @file   GameScreen.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _GAMESCREEN_HPP_
#define _GAMESCREEN_HPP_

#include "screens/Screen.hpp"

#include "game/entities/WorldEntity.hpp"

class GameScreen : public Screen
{
public:
                        GameScreen();

    virtual             ~GameScreen() {}

    virtual Screen *    update(sf::Time elapsed_time);

protected:
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    WorldEntity         _world;

};

#endif // _GAMESCREEN_HPP_
