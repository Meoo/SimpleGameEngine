/**
 * @file   OptionsScreen.cpp
 * @author Bastien Brunnenstein
 */

#include "screens/OptionsScreen.hpp"

#include <cstdio>

#include "Config.hpp"

namespace
{
    inline void drawShadow(sf::RenderTarget & target, const sf::Text & text)
    {
        sf::Text texts(text);
        texts.setColor(MENU_SHADOW);
        texts.move(2, 2);
        target.draw(texts);
    }
}

OptionsScreen::OptionsScreen(Screen * return_screen)
    : _choice(CHOICE_PENDING), _selection(CHOICE_RESOLUTION), _return_screen(return_screen)
    , _font(FontManager::find(RESOURCES_DEFAULT_FONT))
    , _background(TextureManager::find(MENU_BACKGROUND))
    , _prepare_once(true)
{
    // List video modes and get current config
    _modes = sf::VideoMode::getFullscreenModes();
    _current_mode = 0;

    if (Config::fullscreen)
        _screen_mode = SMODE_FULLSCREEN;
    else if (Config::borderless)
        _screen_mode = SMODE_BORDERLESS;
    else
        _screen_mode = SMODE_WINDOWED;

    unsigned mode_id = 0;
    for (videomode_iter_t it = _modes.begin(); it != _modes.end(); /**/)
    {
        if (it->bitsPerPixel != 32 || it->width < WINDOW_WIDTH || it->height < WINDOW_HEIGHT)
            it = _modes.erase(it);
        else
        {
            if (it->width == Config::width && it->height == Config::height)
                _current_mode = mode_id;
            ++mode_id;
            ++it;
        }
    }
}

OptionsScreen::~OptionsScreen()
{
    delete _return_screen;
}

Screen * OptionsScreen::update(sf::Time elapsed_time)
{
    if (_prepare_once)
    {
        _background_sprite.setTexture(_background.get());
    }

    switch(_choice)
    {
    case CHOICE_ACCEPT:

        // Save new config
        Config::width = _modes.at(_current_mode).width;
        Config::height = _modes.at(_current_mode).height;
        switch(_screen_mode)
        {
        case SMODE_WINDOWED:
            Config::fullscreen = false;
            Config::borderless = false;
            break;
        case SMODE_BORDERLESS:
            Config::fullscreen = false;
            Config::borderless = true;
            break;
        case SMODE_FULLSCREEN:
            Config::fullscreen = true;
            Config::borderless = false;
            break;
        default:
            break;
        }
        Config::save();

        // Recreate the window then go back to previous screen
        _choice = CHOICE_CANCEL;
        throw EXCEPTION_RESTART;

    case CHOICE_CANCEL:
        {
            Screen * return_screen = _return_screen;
            _return_screen = 0;
            delete this;
            return return_screen;
        }

    default:
        _choice = CHOICE_PENDING;
        return 0;
    }
}

void OptionsScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(*_return_screen);

    sf::RectangleShape rect(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    sf::Color col(MENU_SHADOW);
    col.a = 128;
    rect.setFillColor(col);
    target.draw(rect);

    char buffer[256];

    sf::Text text;
    text.setCharacterSize(36);
    text.setFont(_font.get());

#define DRAW_TEXT(item, x, y) \
    text.setColor(_selection == CHOICE_##item ? MENU_SELECTION : MENU_ITEM); \
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2); \
    text.setPosition(WINDOW_WIDTH/2 + x, WINDOW_HEIGHT/2 + y); \
    drawShadow(target, text); \
    target.draw(text);


    // Accept & Cancel
    text.setString(MENU_ACCEPT);
    DRAW_TEXT(ACCEPT, -280, 170);

    text.setString(MENU_CANCEL);
    DRAW_TEXT(CANCEL, -280, 220);


    // Resolution
    text.setString(MENU_RESOLUTION);
    DRAW_TEXT(RESOLUTION, -220, -180);

    sf::VideoMode mode = _modes.at(_current_mode);
    std::snprintf(buffer, 256, "< %dx%d >", mode.width, mode.height);
    text.setString(sf::String(buffer));
    DRAW_TEXT(RESOLUTION, 220, -180);


    // Video mode
    text.setString(MENU_MODE);
    DRAW_TEXT(MODE, -220, -120);

    switch (_screen_mode)
    {
    case SMODE_WINDOWED:
        text.setString(MENU_WINDOWED);
        break;
    case SMODE_BORDERLESS:
        text.setString(MENU_BORDERLESS);
        break;
    case SMODE_FULLSCREEN:
        text.setString(MENU_FULLSCREEN);
        break;
    default:
        text.setString(ERROR_STRING);
        break;
    }
    DRAW_TEXT(MODE, 220, -120);

#undef DRAW_TEXT
}

void OptionsScreen::onKeyPressed(sf::Keyboard::Key key)
{
    if (_choice != CHOICE_PENDING) return;

    switch(key)
    {
    case sf::Keyboard::Up:
        _selection = static_cast<enum Choice>(_selection - 1);
        if (_selection <= 0)
            _selection = CHOICE_CANCEL;
        break;

    case sf::Keyboard::Down:
        _selection = static_cast<enum Choice>(_selection + 1);
        if (_selection >= CHOICE_MAX)
            _selection = CHOICE_RESOLUTION;
        break;

    case sf::Keyboard::Left:
        switch (_selection)
        {
        case CHOICE_RESOLUTION:
            ++_current_mode;
            _current_mode %= _modes.size();
            break;

        case CHOICE_MODE:
            _screen_mode = static_cast<enum ScreenMode>(_screen_mode - 1);
            if (_screen_mode == -1)
                _screen_mode = SMODE_FULLSCREEN;
            break;

        default:
            break;
        }
        break;

    case sf::Keyboard::Right:
        switch (_selection)
        {
        case CHOICE_RESOLUTION:
            if (--_current_mode == -1u)
                _current_mode = _modes.size() - 1;
            break;

        case CHOICE_MODE:
            _screen_mode = static_cast<enum ScreenMode>(_screen_mode + 1);
            if (_screen_mode == SMODE_MAX)
                _screen_mode = SMODE_WINDOWED;
            break;

        default:
            break;
        }
        break;

    case sf::Keyboard::Return:
    case sf::Keyboard::Space:
        _choice = _selection;
        break;

    case sf::Keyboard::Escape:
        _choice = CHOICE_CANCEL;
        break;

    default:
        break;
    }
}
