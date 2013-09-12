/**
 * @file   Animation.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include <SFML/System/Time.hpp>

#include "game/Tileset.hpp"
#include "resources/Resources.hpp"

class AnimationSet;

typedef Resources::Handle<AnimationSet>     AnimationSetHandle;
typedef Resources::Manager<AnimationSet>    AnimationSetManager;

typedef struct Animation
{
    typedef unsigned Id;

    TileId      getTileAt(const sf::Time & time) const
    {
        return frames[static_cast<unsigned>(time / frame_time)];
    }

    sf::String  name;

    sf::Time    animation_time;

    sf::Time    frame_time;

    unsigned    frame_number;

    TileId *    frames;

    Id          next_animation;

    static const Id ANIMATION_LOOP = -1u;

} Animation;

//----

class AnimationSet
{
public:
                        AnimationSet();

                        ~AnimationSet();

    bool                loadFromFile(const sf::String & filename);

    Animation::Id       getAnimationId(const sf::String & animation_name) const;

    const Animation &   getAnimation(Animation::Id id) const;

private:
    unsigned    _animation_number;

    Animation * _animations;

};

//----

class AnimationInstance
{
public:
                AnimationInstance(const AnimationSetHandle & animation);

    void        update(sf::Time elapsed_time);

    // Set or reset an animation
    void        resetAnimation(Animation::Id animation_id, sf::Time time_in = sf::Time::Zero);

    TileId      getTileId() const;

private:
    AnimationSetHandle  _animation;

    Animation::Id       _current_animation;

    sf::Time            _time_in;

    TileId              _current_tile_id;

};

#endif // _ANIMATION_HPP_
