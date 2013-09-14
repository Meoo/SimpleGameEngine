/**
 * @file   PauseScreen.cpp
 * @author Bastien Brunnenstein
 */

#include "screens/PauseScreen.hpp"

#include "Config.hpp"

PauseScreen::PauseScreen(Screen * screen)
    : _screen(screen), _font_handle(FontManager::find(RESOURCES_DEFAULT_FONT))
    , _black_screen(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))
    , _unpause_pressed(false)
{
    _black_screen.setFillColor(sf::Color(0, 0, 0, 196));

    _text1.setString(PAUSE_TITLE);
    _text2.setString(PAUSE_SUBTITLE);
    _text1.setCharacterSize(100);
    _text2.setCharacterSize(50);
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

PauseScreen::~PauseScreen()
{
    delete _screen;
}

Screen * PauseScreen::update(sf::Time elapsed_time)
{
    if (_unpause_pressed)
    {
        Screen * screen = _screen;
        _screen = 0;
        delete this;
        return screen;
    }
    return 0;
}

void PauseScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*_screen);

    target.draw(_black_screen);

    target.draw(_text1);
    target.draw(_text2);
}

void PauseScreen::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == PAUSE_KEY)
        _unpause_pressed = true;
}

