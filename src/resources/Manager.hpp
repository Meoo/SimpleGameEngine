/**
 * @file   Manager.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

/**
 * Global resources manager.
 *
 * Register clean and clear functions to be called at the end of the application.
 */
namespace GlobalManager
{
    typedef void (*CleanFunction) (void);
    typedef void (*ClearFunction) (void);

    /**
     * Register a clean function.
     * @param function
     */
    void registerCleanFunction(CleanFunction function);

    /**
     * Register a clear function.
     * @param function
     */
    void registerClearFunction(ClearFunction function);

    /**
     * Call every clean functions, then every clear functions registered.
     */
    void cleanAndClear();

    /**
     * Class used to easily register clean and clear functions from a
     * resource manager.
     *
     * @see RESOURCES_REGISTER_MANAGER
     * @see Resources::Manager
     */
    template<class T>
    class Registerer
    {
    public:
        Registerer()
        {
            registerCleanFunction(T::clean);
            registerClearFunction(T::clear);
        }
    };
}

/**
 * Macro wrapping a static Registerer for a resource manager.
 *
 * Do not use it in a header file.
 * It should be used only once per resource manager.
 *
 * @param T Resource manager class name.
 * @warning T must not be namespace qualified. Use this macro inside the namespace instead.
 */
#define RESOURCES_REGISTER_MANAGER(T) static GlobalManager::Registerer<T> _s_ ## T ## _registerer;

#endif // _MANAGER_HPP_
