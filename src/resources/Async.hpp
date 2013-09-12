/**
 * @file   Async.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _ASYNC_HPP_
#define _ASYNC_HPP_

namespace Async
{
    typedef void (*function_t) (void *);

    // Start workers
    void initialize();

    // Kill workers
    void terminate();

    // Run a function on a secondary thread
    // Set priority to true to run it as soon as possible
    // This function should be thread safe, so you can use it within a secondary thread
    // If threading is disabled in Config, using it "recursively" will probably cause errors
    void run(function_t function, void * param, bool priority = false);

}

#endif // _ASYNC_HPP_
