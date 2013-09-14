/**
 * @file   Async.cpp
 * @author Bastien Brunnenstein
 */

#include "resources/Async.hpp"

#include <cassert>

#include "Config.hpp"

#include "ext/tinythread.h"
#include "ext/fast_mutex.h"

namespace
{
    typedef tthread::thread                 thread_t;

    typedef tthread::fast_mutex             mutex_t;

    typedef tthread::condition_variable     condition_variable_t;

    typedef tthread::lock_guard<mutex_t>    lock_t;

    typedef struct job_t
    {
        volatile job_t * next;

        Async::function_t function;

        void * param;

    } job_t;

#ifndef NDEBUG
    bool ready = false;
#endif

    thread_t *          worker_pool[RESOURCES_WORKERS_MAX];

    // Set to true to kill all the workers
    volatile bool       kill_workers;

    mutex_t             jobs_mutex;

    condition_variable_t jobs_condition;

    volatile job_t      job_pool[RESOURCES_JOBS_MAX];

    volatile job_t *    first_job;

    volatile job_t *    last_job;

    volatile job_t *    first_free_job;

    void schedule_job(Async::function_t  function, void * param, bool priority = false)
    {
        lock_t lock(jobs_mutex);

        assert(first_free_job);

        volatile job_t * job = first_free_job;
        first_free_job = job->next;

        job->function = function;
        job->param = param;

        if (!first_job)
        {
            job->next = 0;
            first_job = job;
            last_job = job;
        }
        else if (priority)
        {
            job->next = first_job;
            first_job = job;
        }
        else
        {
            job->next = 0;
            last_job->next = job;
            last_job = job;
        }
        jobs_condition.notify_one();
    }

    volatile job_t * acquire_job()
    {
        lock_t lock(jobs_mutex);

        if (first_job == 0)
        {
            jobs_condition.wait(jobs_mutex);
            if (first_job == 0)
                return 0;
        }

        volatile job_t * job = first_job;
        first_job = job->next;

        return job;
    }

    void free_job(volatile job_t * job)
    {
        lock_t lock(jobs_mutex);

        job->next = first_free_job;
        first_free_job = job;
    }

    // Main function for workers
    void worker_main(void * _worker_num)
    {
        // int worker_num = reinterpret_cast<int>(_worker_num);

        while(!kill_workers)
        {
            volatile job_t * job = acquire_job();
            if (job)
            {
                job->function(job->param);
                free_job(job);
            }
        }
    }

} // namespace

void Async::initialize()
{
    assert(!ready);
    assert((ready = true));

    if (!RESOURCES_THREADING)
        return;

    // Jobs
    first_job = 0;
    last_job = 0;
    first_free_job = job_pool;

    for (unsigned ji = 0; ji < (RESOURCES_JOBS_MAX - 1); ++ji)
    {
        job_pool[ji].next = &job_pool[ji+1];
    }
    job_pool[RESOURCES_JOBS_MAX - 1].next = 0;

    // Workers
    kill_workers = false;

    for (unsigned wi = 0; wi < RESOURCES_WORKERS_MAX; ++wi)
    {
        worker_pool[wi] = new tthread::thread(worker_main, reinterpret_cast<void *>(wi));
    }
}

void Async::terminate()
{
    assert(ready);
    assert(!(ready = false));

    kill_workers = true;
    jobs_condition.notify_all();

    for (unsigned wi = 0; wi < RESOURCES_WORKERS_MAX; ++wi)
    {
        worker_pool[wi]->join();
        worker_pool[wi] = 0;
    }
}

void Async::run(Async::function_t function, void * param, bool priority)
{
    assert(ready);

    if (!RESOURCES_THREADING)
        function(param);
    else
        schedule_job(function, param, priority);
}

