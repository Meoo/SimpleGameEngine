/**
 * @file   OptionsScreen.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _OPTIONSSCREEN_HPP_
#define _OPTIONSSCREEN_HPP_

#include "screens/Screen.hpp"

#include "resources/Resources.hpp"

class OptionsScreen : public Screen
{
    typedef std::vector<sf::VideoMode> videomode_map_t;
    typedef videomode_map_t::iterator  videomode_iter_t;

public:
    explicit OptionsScreen(Screen * return_screen);

    virtual ~OptionsScreen();

    virtual Screen * update(sf::Time elapsed_time);

    virtual void onKeyPressed(sf::Keyboard::Key key);

protected:
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
    enum Choice
    {
        CHOICE_PENDING = 0,

        CHOICE_RESOLUTION,
        CHOICE_MODE,

        CHOICE_ACCEPT,
        CHOICE_CANCEL,

        CHOICE_MAX,

    } _choice, _selection;

    enum ScreenMode
    {
        SMODE_WINDOWED = 0,
        SMODE_BORDERLESS,
        SMODE_FULLSCREEN,

        SMODE_MAX,

    } _screen_mode;

    Screen *        _return_screen;

    FontHandle      _font;
    TextureHandle   _background;

    bool            _prepare_once;

    sf::Sprite      _background_sprite;

    videomode_map_t _modes;
    unsigned        _current_mode;

};

#endif // _OPTIONSSCREEN_HPP_
