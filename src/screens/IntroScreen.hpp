/**
 * @file   IntroScreen.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _INTROSCREEN_HPP_
#define _INTROSCREEN_HPP_

#include "Screen.hpp"

#include "resources/Resources.hpp"

class IntroScreen : public Screen
{
public:
    IntroScreen();

    virtual ~IntroScreen() {}

    virtual Screen * update(sf::Time elapsed_time);

    virtual void onKeyPressed(sf::Keyboard::Key key);

protected:
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
    sf::Time _timeout;

    sf::Text _text1;

    sf::Text _text2;

    FontHandle _font_handle;

};

#endif // _INTROSCREEN_HPP_
