/**
 * @file   Screen.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include <SFML/Graphics.hpp>

/**
 * A screen is a "state" for the application.
 *
 * Screens controls the flow of an application.
 */
class Screen : public sf::Drawable
{
public:
    /**
     * Virtual destructor for inheritance.
     */
    virtual ~Screen() {}

    /**
     * Update the scene.
     *
     * If you return something else than the null pointer, it will be used
     * as the next screen for the application.
     *
     * @warning The memory is not managed automatically, so if you don't pass
     *          this screen as a parameter for the new one, then you probably
     *          should "delete this" right before returning.
     *
     * @param elapsed_time
     * @return next screen to be used, or null pointer.
     */
    virtual Screen * update(sf::Time elapsed_time) = 0;

    /**
     * Callback to handle key presses.
     *
     * @param key
     */
    virtual void onKeyPressed(sf::Keyboard::Key key) {}

};

#endif // _SCREEN_HPP_
