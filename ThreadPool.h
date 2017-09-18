/**
 * @file ThreadPool.h
 *
 * @author Natalya Sannikova (natalyasann2@gmail.com)
 * @date 07.09.2017
 * @version 1.0
 */

#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include <thread>
#include <vector>
#include <cstddef>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool   (size_t numberOfThreads);
    ~ThreadPool  ();

    void fun();
    void execute (std::function<void()> const &foo);

private:
    size_t numberOfThreads_;
    std :: vector < std::thread > threads_; //vector of threads
    std :: mutex locker_;
    std :: condition_variable queueIsEmpty_;
    std :: queue< std::function<void()> > functions_;
    bool flag_ = false;
};


#endif //THREADPOOL_THREADPOOL_H
