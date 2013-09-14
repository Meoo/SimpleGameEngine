/**
 * @file   Animation.cpp
 * @author Bastien Brunnenstein
 */

#include "game/Animation.hpp"

#include <cassert>
#include <fstream>
#include <sstream>

#include "resources/Manager.hpp"

AnimationSet::AnimationSet()
    : _animation_number(0), _animations(0)
{
}

AnimationSet::~AnimationSet()
{
    for (unsigned ai = 0; ai < _animation_number; ++ai)
        delete[] _animations[ai].frames;

    delete[] _animations;
}

#define CHECK_STRING(tx) \
    file >> text; \
    if (text != std::string(tx)) { \
        std::cerr << "Unexpected text : " << text << "\n" \
                  << "Expected        : " << tx << "\n" \
                  << "In file " << filename.toAnsiString() << std::endl; \
        return false; }

bool AnimationSet::loadFromFile(const sf::String & filename)
{
    std::ifstream file(filename.toAnsiString().c_str());

    if (!file.is_open())
    {
        std::cerr << "Unable to open file " << filename.toAnsiString() << std::endl;
        return false;
    }

    std::vector<Animation> animations;
    std::map<unsigned, sf::String> next_animations;
    std::string text;
    float time;

    _animation_number = 0;

    // Actual loading
    do
    {
        Animation anim;
        std::vector<TileId> frames;

        CHECK_STRING("ANIM");

        // Name
        file >> text;
        anim.name = text;

        CHECK_STRING("TIME");

        // Time
        file >> time;
        anim.animation_time = sf::seconds(time);

        // Next
        file >> text;
        if (text == std::string("LOOP"))
        {
            anim.next_animation = Animation::ANIMATION_LOOP;
        }
        else if (text == std::string("NEXT"))
        {
            file >> text;
            next_animations[_animation_number] = text;
        }
        else
        {
            std::cerr << "Unexpected text : " << text << "\n"
                      << "Expected        : LOOP or NEXT\n"
                      << "In file " << filename.toAnsiString() << std::endl;
            return false;
        }

        CHECK_STRING("BEGIN");

        file >> text;
        while (text != std::string("END"))
        {
            // Frames
            std::stringstream str(text);
            TileId frame;
            str >> frame;
            frames.push_back(frame);

            file >> text;
        }

        anim.frame_number = frames.size();

        if (anim.frame_number == 0)
        {
            std::cerr << "Animation with no images : " << anim.name.toAnsiString() << "\n"
                      << "In file " << filename.toAnsiString() << std::endl;
            return false;
        }

        anim.frames = new TileId[anim.frame_number];

        for (unsigned fi = 0; fi < anim.frame_number; ++fi)
            anim.frames[fi] = frames[fi];

        // Frame time
        anim.frame_time = anim.animation_time / (sf::Int64) anim.frame_number;

        animations.push_back(anim);
        ++_animation_number;
        file >> std::ws;
    }
    while (!file.eof());

    _animation_number = animations.size();
    _animations = new Animation[_animation_number];

    for (unsigned ai = 0; ai < _animation_number; ++ai)
        _animations[ai] = animations[ai];

    // Link next animations
    for (std::map<unsigned, sf::String>::iterator it = next_animations.begin(); it != next_animations.end(); ++it)
        _animations[it->first].next_animation = getAnimationId(it->second);

    return true;
}

#undef CHECK_STRING

Animation::Id AnimationSet::getAnimationId(const sf::String & animation_name) const
{
    assert(_animations);

    for (unsigned ai = 0; ai < _animation_number; ++ai)
    {
        if (_animations[ai].name == animation_name)
            return ai;
    }

    assert(false);
    return -1;
}

const Animation& AnimationSet::getAnimation(Animation::Id id) const
{
    return _animations[id];
}

//----

AnimationInstance::AnimationInstance(const AnimationSetHandle & animation)
    : _animation(animation), _current_animation(0), _current_tile_id(0)
{
}

void AnimationInstance::update(sf::Time elapsed_time)
{
    const Animation & animation = _animation.get().getAnimation(_current_animation);

    _time_in += elapsed_time;

    if (_time_in > animation.animation_time)
    {
        _time_in -= animation.animation_time;
        if (animation.next_animation != Animation::ANIMATION_LOOP)
        {
            _current_animation = animation.next_animation;
            _current_tile_id = _animation.get().getAnimation(_current_animation).getTileAt(_time_in);
            return;
        }
    }

    _current_tile_id = animation.getTileAt(_time_in);
}

void AnimationInstance::resetAnimation(Animation::Id animation_id, sf::Time time_in)
{
    _current_animation = animation_id;
    _time_in = time_in;

    _current_tile_id = _animation.get().getAnimation(animation_id).getTileAt(time_in);
}

TileId AnimationInstance::getTileId() const
{
    return _current_tile_id;
}

RESOURCES_REGISTER_MANAGER(AnimationSetManager);
