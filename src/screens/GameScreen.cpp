/**
 * @file   GameScreen.cpp
 * @author Bastien Brunnenstein
 */

#include "screens/GameScreen.hpp"
#include <iostream>

GameScreen::GameScreen()
    : anim(AnimationSetManager::find("res/animations/robot.txt")),
      animi(anim),
      texture(TextureManager::find("res/textures/robot.png")),
      tileset(32, 32, 4, 4)
{
    animi.resetAnimation(anim.get().getAnimationId("walk_right"));
}

Screen * GameScreen::update(sf::Time elapsed_time)
{
    animi.update(elapsed_time);
    return 0;
}

void GameScreen::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Space)
        animi.resetAnimation(anim.get().getAnimationId("jumping"));

    if (key == sf::Keyboard::Left)
        animi.resetAnimation(anim.get().getAnimationId("walk_left"));

    if (key == sf::Keyboard::Right)
        animi.resetAnimation(anim.get().getAnimationId("walk_right"));
}

void GameScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    sf::IntRect texrect = tileset.getTextureRect(animi.getTileId());
    sf::Sprite sprite(texture.get(), texrect);
    sprite.setPosition(400-16, 300-16);
    target.draw(sprite);
}
