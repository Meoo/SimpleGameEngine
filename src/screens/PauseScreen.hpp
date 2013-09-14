/**
 * @file   PauseScreen.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _PAUSESCREEN_HPP_
#define _PAUSESCREEN_HPP_

#include "screens/Screen.hpp"

#include "resources/Resources.hpp"

class PauseScreen : public Screen
{
public:
    PauseScreen(Screen * screen);

    virtual ~PauseScreen();

    virtual Screen * update(sf::Time elapsed_time);

    virtual void onKeyPressed(sf::Keyboard::Key key);

protected:
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
    Screen * _screen;

    sf::Text _text1;

    sf::Text _text2;

    FontHandle _font_handle;

    sf::RectangleShape _black_screen;

    bool _unpause_pressed;

};

#endif // _PAUSESCREEN_HPP_
