/**
 * @file   MenuScreen.cpp
 * @author Bastien Brunnenstein
 */

#include "screens/MenuScreen.hpp"

#include "Config.hpp"

#include "screens/GameScreen.hpp"
#include "screens/OptionsScreen.hpp"
#include "screens/TransitionScreen.hpp"

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

MenuScreen::MenuScreen()
    : _choice(CHOICE_PENDING), _selection(CHOICE_NEW_GAME)
    , _font(FontManager::find(RESOURCES_DEFAULT_FONT))
    , _background(TextureManager::find(MENU_BACKGROUND))
    , _prepare_once(true), _in_submenu(false)
{
}

Screen * MenuScreen::update(sf::Time elapsed_time)
{
    if (_prepare_once)
    {
        _background_sprite.setTexture(_background.get());

        _text_new.setString(MENU_NEW_GAME);
        _text_load.setString(MENU_LOAD_GAME);
        _text_options.setString(MENU_OPTIONS);
        _text_exit.setString(MENU_QUIT);

        _text_new.setCharacterSize(30);
        _text_load.setCharacterSize(30);
        _text_options.setCharacterSize(30);
        _text_exit.setCharacterSize(30);

        _text_new.setFont(_font.get());
        _text_load.setFont(_font.get());
        _text_options.setFont(_font.get());
        _text_exit.setFont(_font.get());

        _text_new.setOrigin(_text_new.getLocalBounds().width/2, _text_new.getLocalBounds().height/2);
        _text_load.setOrigin(_text_load.getLocalBounds().width/2, _text_load.getLocalBounds().height/2);
        _text_options.setOrigin(_text_options.getLocalBounds().width/2, _text_options.getLocalBounds().height/2);
        _text_exit.setOrigin(_text_exit.getLocalBounds().width/2, _text_exit.getLocalBounds().height/2);

        unsigned p = 100;
        _text_new.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + p);
        if (MENU_LOAD_ENABLED)
            _text_load.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + (p+=40));
        if (MENU_OPTIONS_ENABLED)
            _text_options.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + (p+=40));
        _text_exit.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2 + (p+=40));

        _text_new.setColor(MENU_ITEM);
        _text_load.setColor(MENU_ITEM);
        _text_options.setColor(MENU_ITEM);
        _text_exit.setColor(MENU_ITEM);

        _prepare_once = false;
    }

    switch(_choice)
    {
    case CHOICE_NEW_GAME:

        // Enable pause when starting the game
        if (PAUSE_ENABLED)
            Config::pause_enabled = true;

        _choice = CHOICE_MAX;
        return new TransitionScreen(this, new GameScreen(), sf::seconds(0.5f), sf::Color::White, true);

    case CHOICE_LOAD_GAME:
        _choice = CHOICE_PENDING;
        return 0;

    case CHOICE_OPTIONS:
        _in_submenu = true;
        _choice = CHOICE_PENDING;
        return new OptionsScreen(this);

    case CHOICE_QUIT:
        throw ExitException;

    default:
        _in_submenu = false;
        return 0;
    }
}

void MenuScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(_background_sprite);

    if (_in_submenu) return;

    {
        sf::Text text_new(_text_new);
        sf::Text text_load(_text_load);
        sf::Text text_options(_text_options);
        sf::Text text_exit(_text_exit);

        switch(_selection)
        {
        case CHOICE_NEW_GAME:
            text_new.setColor(MENU_SELECTION);
            break;
        case CHOICE_LOAD_GAME:
            text_load.setColor(MENU_SELECTION);
            break;
        case CHOICE_OPTIONS:
            text_options.setColor(MENU_SELECTION);
            break;
        case CHOICE_QUIT:
            text_exit.setColor(MENU_SELECTION);
            break;

        default:
            break;
        }

        drawShadow(target, _text_new);
        target.draw(text_new);

        drawShadow(target, _text_exit);
        target.draw(text_exit);

        if (MENU_LOAD_ENABLED)
        {
            drawShadow(target, _text_load);
            target.draw(text_load);
        }
        if (MENU_OPTIONS_ENABLED)
        {
            drawShadow(target, _text_options);
            target.draw(text_options);
        }
    }
}

void MenuScreen::onKeyPressed(sf::Keyboard::Key key)
{
    if (_choice != CHOICE_PENDING) return;

    switch(key)
    {
    case sf::Keyboard::Up:
    case sf::Keyboard::Left:
        _selection = static_cast<enum Choice>(_selection - 1);

        if (!MENU_OPTIONS_ENABLED && _selection == CHOICE_OPTIONS)
            _selection = static_cast<enum Choice>(_selection - 1);

        if (!MENU_LOAD_ENABLED && _selection == CHOICE_LOAD_GAME)
            _selection = static_cast<enum Choice>(_selection - 1);

        if (_selection <= 0)
            _selection = CHOICE_QUIT;
        break;

    case sf::Keyboard::Down:
    case sf::Keyboard::Right:
        _selection = static_cast<enum Choice>(_selection + 1);

        if (!MENU_LOAD_ENABLED && _selection == CHOICE_LOAD_GAME)
            _selection = static_cast<enum Choice>(_selection + 1);

        if (!MENU_OPTIONS_ENABLED && _selection == CHOICE_OPTIONS)
            _selection = static_cast<enum Choice>(_selection + 1);

        if (_selection >= CHOICE_MAX)
            _selection = CHOICE_NEW_GAME;
        break;

    case sf::Keyboard::Return:
    case sf::Keyboard::Space:
        _choice = _selection;
        break;

    default:
        break;
    }
}
