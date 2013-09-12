/**
 * @file   IntroScreen.cpp
 * @author Bastien Brunnenstein
 */

#include "screens/IntroScreen.hpp"

#include "Config.hpp"

#include "screens/MenuScreen.hpp"
#include "screens/TransitionScreen.hpp"

IntroScreen::IntroScreen()
    : _timeout(INTRO_TIME), _font_handle(FontManager::find(RESOURCES_DEFAULT_FONT))
{
    _text1.setString(INTRO_TITLE);
    _text2.setString(INTRO_SUBTITLE);
    _text1.setCharacterSize(90);
    _text2.setCharacterSize(30);
    _text1.setStyle(sf::Text::Bold);
    _text1.setColor(sf::Color::White);
    _text2.setColor(sf::Color::White);
    _text1.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 - 120);
    _text2.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + 80);
    _text1.setFont(_font_handle.get());
    _text2.setFont(_font_handle.get());
    _text1.setOrigin(_text1.getLocalBounds().width/2, _text1.getLocalBounds().height/2);
    _text2.setOrigin(_text2.getLocalBounds().width/2, _text2.getLocalBounds().height/2);
}

Screen * IntroScreen::update(sf::Time elapsed_time)
{
    // Only create a new screen once
    if (_timeout >= sf::Time::Zero && (_timeout -= elapsed_time) < sf::Time::Zero)
        return new TransitionScreen(this, new MenuScreen(), INTRO_TRANSITION, sf::Color::Black, true);

    return 0;
}

void IntroScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.clear(sf::Color::Black);

    target.draw(_text1);
    target.draw(_text2);
}

void IntroScreen::onKeyPressed(sf::Keyboard::Key key)
{
    if (_timeout > sf::Time::Zero)
        _timeout = sf::Time::Zero;
}
