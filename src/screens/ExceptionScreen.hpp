/**
 * @file   ExceptionScreen.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _EXCEPTIONSCREEN_HPP_
#define _EXCEPTIONSCREEN_HPP_

#include <exception>

#include "screens/Screen.hpp"

#include "resources/Resources.hpp"

class ExceptionScreen : public Screen
{
public:
                        ExceptionScreen(const std::exception & exception, Screen * last_screen);

    virtual             ~ExceptionScreen();

    Screen *            update(sf::Time elapsed_time);

protected:
    void                draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
    sf::Text            _text1;

    sf::Text            _text2;

    FontHandle          _font_handle;

    sf::RectangleShape  _blue_screen;

    Screen *            _last_screen;

};

#endif // _EXCEPTIONSCREEN_HPP_
