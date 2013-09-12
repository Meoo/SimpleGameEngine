/**
 * @file   TransitionScreen.cpp
 * @author Bastien Brunnenstein
 */

#include "screens/TransitionScreen.hpp"

#include <cassert>

#include "Config.hpp"

TransitionScreen::TransitionScreen(Screen * first, Screen * second, sf::Time time, sf::Color fade_color, bool delete_first_screen)
    : _time(time), _timeout(sf::Time::Zero), _delete_first_screen(delete_first_screen)
    , _first(first), _second(second), _fade_screen(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))
{
    assert(_first);
    assert(_second);
    assert(_time.asMilliseconds() > 0);

    fade_color.a = 0;
    _fade_screen.setFillColor(fade_color);
}

TransitionScreen::~TransitionScreen()
{
    delete _first;
    delete _second;
}

Screen * TransitionScreen::update(sf::Time elapsed_time)
{
    if (_first)
    {
        // Fade in
        Screen * ret = _first->update(elapsed_time);
        if (ret)
            _first = ret;

        if ((_timeout += elapsed_time) > _time)
        {
            if (_delete_first_screen)
                delete _first;

            _first = 0;
            _timeout = _time;
        }
    }
    else
    {
        // Fade out
        Screen * ret = _second->update(elapsed_time);
        if (ret)
            _second = ret;

        if ((_timeout -= elapsed_time) < sf::Time::Zero)
        {
            Screen * second = _second;
            _second = 0;
            delete this;
            return second;
        }
    }

    sf::Color color = _fade_screen.getFillColor();
    color.a = sf::Uint8((_timeout.asSeconds() / _time.asSeconds()) * 255);
    _fade_screen.setFillColor(color);
    return 0;
}

void TransitionScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_first)
        target.draw(*_first);
    else
        target.draw(*_second);

    target.draw(_fade_screen);
}
