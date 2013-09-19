/**
 * @file   GameScreen.cpp
 * @author Bastien Brunnenstein
 */

#include "screens/GameScreen.hpp"

GameScreen::GameScreen()
{
}

Screen * GameScreen::update(sf::Time elapsed_time)
{
    _world.update(elapsed_time);
    return 0;
}

void GameScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(_world);
}
