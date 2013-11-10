/**
 * @file   GameScreen.cpp
 * @author Bastien Brunnenstein
 */

#include "screens/GameScreen.hpp"

#include "Config.hpp"

GameScreen::GameScreen()
    : _world(_renderer)
{
#ifndef NDEBUG
    _debug = false;
#endif
}

Screen * GameScreen::update(sf::Time elapsed_time)
{
    _world.update(elapsed_time);
    return 0;
}

void GameScreen::onKeyPressed(sf::Keyboard::Key key)
{
#ifndef NDEBUG
    if (key == DEBUG_KEY)
        _debug = !_debug;
#endif
}

void GameScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    /* TODO GameScreen::draw Draw everything
#ifndef NDEBUG
    if (_debug)
        _world.drawDebug(target, states);
#endif*/

    _renderer.render(target);
}
