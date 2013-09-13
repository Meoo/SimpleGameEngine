/**
 * @file   MenuScreen.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _MENUSCREEN_HPP_
#define _MENUSCREEN_HPP_

#include "screens/Screen.hpp"

#include "resources/Resources.hpp"

class MenuScreen : public Screen
{
public:
    MenuScreen();

    virtual ~MenuScreen() {}

    virtual Screen * update(sf::Time elapsed_time);

    virtual void onKeyPressed(sf::Keyboard::Key key);

protected:
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
    enum Choice
    {
        CHOICE_PENDING = 0,

        CHOICE_NEW_GAME,
        CHOICE_LOAD_GAME,
        CHOICE_OPTIONS,
        CHOICE_QUIT,

        CHOICE_MAX,

    } _choice, _selection;

    FontHandle      _font;
    TextureHandle   _background;

    bool            _prepare_once;

    sf::Sprite      _background_sprite;
    sf::Text        _text_new;
    sf::Text        _text_load;
    sf::Text        _text_options;
    sf::Text        _text_exit;

};

#endif // _MENUSCREEN_HPP_
