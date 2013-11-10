/**
 * @file   Resources.hxx
 * @author Bastien Brunnenstein
 */

#ifndef _RESOURCES_HXX_
#define _RESOURCES_HXX_

#include "Resources.hpp"

#ifndef NDEBUG
#include <iostream>
#endif

#include <stdexcept>
#include <typeinfo>
#include <sstream>

namespace
{
    void throwResourceLoadException(const sf::String & filename)
    {
        std::ostringstream string;
        string << "Error while loading resource file : " << filename.toAnsiString();

        throw std::runtime_error(string.str());
    }
}

// Resource

template<class T> inline
Resources::Resource<T>::Resource(const sf::String & name)
    : _name(name), _ready(false), _error(false), _references(0)
{
    Async::run(Resource<T>::doLoad, this);
}

template<class T> inline
volatile bool Resources::Resource<T>::isReady() const
{
    return _ready;
}

template<class T> inline
const sf::String & Resources::Resource<T>::getName() const
{
    return _name;
}

template<class T> inline
T & Resources::Resource<T>::get()
{
    while (!isReady())
    {
        if (_error)
            throwResourceLoadException(getName());

        tthread::this_thread::yield();
    }
    return _object;
}

template<class T> inline
const T & Resources::Resource<T>::get() const
{
    while (!isReady())
    {
        if (_error)
            throwResourceLoadException(getName());

        tthread::this_thread::yield();
    }
    return _object;
}

template<class T> inline
unsigned Resources::Resource<T>::getReferencesCount() const
{
    return _references;
}

template<class T> inline
void Resources::Resource<T>::lock()
{
    ++_references;
}

template<class T> inline
void Resources::Resource<T>::unlock()
{
    --_references;
}

template<class T>
void Resources::Resource<T>::doLoad(void * _resource)
{
    Resource * resource = (Resource *) _resource;
    if (resource->_object.loadFromFile(resource->_name))
    {
        resource->_ready = true;
    }
    else
    {
        resource->_error = true;
    }
}

// Handle

template<class T> inline
Resources::Handle<T>::Handle()
    : _resource(0)
{}

template<class T> inline
Resources::Handle<T>::Handle(resource_t & resource)
    : _resource(&resource)
{
    _resource->lock();
}

template<class T> inline
Resources::Handle<T>::Handle(const Handle & handle)
    : _resource(handle._resource)
{
    if (_resource)
        _resource->lock();
}

template<class T> inline
Resources::Handle<T>::~Handle()
{
    reset();
}

template<class T> inline
void Resources::Handle<T>::reset()
{
    if (_resource)
    {
        _resource->unlock();
        _resource = 0;
    }
}

template<class T> inline
void Resources::Handle<T>::reset(resource_t & resource)
{
    reset();
    _resource = &resource;
    _resource->lock();
}

template<class T> inline
void Resources::Handle<T>::reset(const Handle & handle)
{
    if (handle._resource)
        reset(*handle._resource);
    else
        reset();
}

template<class T> inline
bool Resources::Handle<T>::isReady() const
{
    return _resource->isReady();
}

template<class T> inline
T & Resources::Handle<T>::get()
{
    return _resource->get();
}

template<class T> inline
const T & Resources::Handle<T>::get() const
{
    return _resource->get();
}

// Manager

template<class T> inline
typename Resources::Manager<T>::resource_t & Resources::Manager<T>::find(const sf::String & name)
{
    lock_t lock(s_map_mutex);

    resource_iter_t iter(s_resource_map.find(name));
    if (iter != s_resource_map.end())
        return *(iter->second);

    resource_t * res = new resource_t(name);
    s_resource_map[name] = res;
    return *res;
}

template<class T>
void Resources::Manager<T>::clean()
{
    lock_t lock(s_map_mutex);

    for (resource_iter_t it = s_resource_map.begin(); it != s_resource_map.end(); /**/)
    {
        if (it->second->getReferencesCount() <= 0)
        {
            delete it->second;
            s_resource_map.erase(it++);
        }
        else
            ++it;
    }
}

template<class T>
void Resources::Manager<T>::clear()
{
    lock_t lock(s_map_mutex);

    for (resource_iter_t it = s_resource_map.begin(); it != s_resource_map.end(); /**/)
    {
#ifndef NDEBUG
        if (it->second->getReferencesCount() != 0)
        {
            std::cerr << "Resource \"" << (it->second->getName().toAnsiString())
                      << "\" cleared with " << (it->second->getReferencesCount())
                      << " active reference(s)" << std::endl;
        }
#endif

        delete it->second;
        s_resource_map.erase(it++);
    }
}

template<class T>
typename Resources::Manager<T>::resource_map_t Resources::Manager<T>::s_resource_map;

template<class T>
typename Resources::Manager<T>::mutex_t Resources::Manager<T>::s_map_mutex;

#endif // _RESOURCES_HXX_
