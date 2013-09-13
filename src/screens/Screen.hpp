/**
 * @file   Screen.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_

#include <SFML/Graphics.hpp>

class Screen : public sf::Drawable
{
public:
    virtual ~Screen() {}

    // Return next screen to use or NULL
    // If something else than NULL is returned the Screen should be considered as an invalid object
    // It means you can safely "delete this" right before returning the next Screen
    virtual Screen * update(sf::Time elapsed_time) = 0;

    virtual void onKeyPressed(sf::Keyboard::Key key) {}

};

#endif // _SCREEN_HPP_
