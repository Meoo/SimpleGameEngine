/**
 * @file   Ressources.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _RESOURCES_HPP_
#define _RESOURCES_HPP_

#include <map>

#include <SFML/Graphics.hpp>

#include "resources/Async.hpp"
#include "ext/tinythread.h"
#include "ext/fast_mutex.h"

namespace Resources
{
    template<class T>
    class Resource
    {
    public:
        Resource(const sf::String & name);

        bool isReady() const;

        const sf::String & getName() const;

              T & get();
        const T & get() const;

        unsigned getReferencesCount() const;

        void lock();    // Increase the reference counter
        void unlock();  // Decrease the reference counter

    private:
        static void doLoad(void * _resource);

        sf::String          _name;
        volatile bool       _ready;
        T                   _object;
        volatile unsigned   _references; // TODO Concurrent access possible! Should be atomic instead?

    }; // class Resource<T>


    template<class T>
    class Handle
    {
        typedef Resource<T> resource_t;

    public:
        Handle();
        Handle(resource_t & resource);
        Handle(const Handle & handle);

        ~Handle();

        void reset();
        void reset(resource_t & resource);
        void reset(Handle & handle);

        bool isReady() const;

              T & get();
        const T & get() const;

    private:
        resource_t * _resource;

    }; // class Handle<T>


    template<class T>
    class Manager
    {
        typedef Resource<T>                         resource_t;
        typedef std::map<sf::String, resource_t *>  resource_map_t;
        typedef typename resource_map_t::iterator   resource_iter_t;

        typedef tthread::fast_mutex         mutex_t;
        typedef tthread::lock_guard<mutex_t> lock_t;

    public:
        // Find a resource
        // The resource can, but should not be used directly
        // Instead, wrap it with a Handle to count references automatically
        static resource_t & find(const sf::String & name);

        // Clean unused ressources
        // This function is rather slow and lock the mutex
        // Use it once, after the handles have been acquired
        static void clean();

        // Clear all ressources
        // Print a warning if a ressource still had references
        static void clear();

    private:
        // Not a class, not a namespace either because of template
        // Private constructor that should never be implemented
        Manager();

        static resource_map_t   s_resource_map;
        static mutex_t          s_map_mutex;

    }; // class Manager<T>

} // namespace Resources

typedef Resources::Handle<sf::Texture>  TextureHandle;
typedef Resources::Manager<sf::Texture> TextureManager;

typedef Resources::Handle<sf::Font>     FontHandle;
typedef Resources::Manager<sf::Font>    FontManager;

#include "Resources.hxx"

#endif // _RESOURCES_HPP_
