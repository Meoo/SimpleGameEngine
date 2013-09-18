/**
 * @file   ExceptionScreen.cpp
 * @author Bastien Brunnenstein
 */

#include "screens/ExceptionScreen.hpp"

#include "Config.hpp"

ExceptionScreen::ExceptionScreen(const std::exception & exception, Screen * last_screen)
    : _font_handle(FontManager::find(RESOURCES_DEFAULT_FONT))
    , _blue_screen(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))
    , _last_screen(last_screen)
{
    _blue_screen.setFillColor(sf::Color::Blue);

    _text1.setString(EXCEPTION_TITLE);
    _text2.setString(exception.what());
    _text1.setCharacterSize(90);
    _text2.setCharacterSize(35);
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

ExceptionScreen::~ExceptionScreen()
{
    delete _last_screen;
}

Screen * ExceptionScreen::update(sf::Time elapsed_time)
{
    return 0;
}

void ExceptionScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_blue_screen);

    target.draw(_text1);
    target.draw(_text2);
}
