/**
 * @file   Manager.cpp
 * @author Bastien Brunnenstein
 */

#include "resources/Manager.hpp"

#include <vector>

#include "resources/Resources.hpp"

namespace
{
    typedef std::vector<GlobalManager::CleanFunction>   CleanVector;
    typedef CleanVector::iterator                       CleanIterator;

    typedef std::vector<GlobalManager::ClearFunction>   ClearVector;
    typedef ClearVector::iterator                       ClearIterator;

    inline CleanVector & getCleanVector()
    {
        static CleanVector s_vector;
        return s_vector;
    }

    inline ClearVector & getClearVector()
    {
        static ClearVector s_vector;
        return s_vector;
    }
}

void GlobalManager::registerCleanFunction(CleanFunction function)
{
    getCleanVector().push_back(function);
}

void GlobalManager::registerClearFunction(ClearFunction function)
{
    getClearVector().push_back(function);
}

void GlobalManager::cleanAndClear()
{
    for (CleanIterator it = getCleanVector().begin(); it < getCleanVector().end(); ++it)
        (*it)();

    for (ClearIterator it = getClearVector().begin(); it < getClearVector().end(); ++it)
        (*it)();
}

RESOURCES_REGISTER_MANAGER(TextureManager);

RESOURCES_REGISTER_MANAGER(FontManager);
