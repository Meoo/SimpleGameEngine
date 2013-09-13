/**
 * @file   TransitionScreen.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _TRANSITIONSCREEN_HPP_
#define _TRANSITIONSCREEN_HPP_

#include "screens/Screen.hpp"

class TransitionScreen : public Screen
{
public:
    TransitionScreen(Screen * first, Screen * second, sf::Time time, sf::Color fade_color, bool delete_first_screen);

    virtual ~TransitionScreen();

    virtual Screen * update(sf::Time elapsed_time);

    // Do not override onKeyPressed, so key presses are intercepted while the transition is active

protected:
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
    sf::Time _time;

    sf::Time _timeout;

    bool _delete_first_screen;

    Screen * _first;

    Screen * _second;

    sf::RectangleShape _fade_screen;

};

#endif // _TRANSITIONSCREEN_HPP_
