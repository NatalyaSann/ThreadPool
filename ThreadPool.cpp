/**
 * @file ThreadPool.cpp
 *
 * @author Natalya Sannikova (natalyasann2@gmail.com)
 * @date 07.09.2017
 * @version 1.0
 */

#include <iostream>
#include "ThreadPool.h"

void ThreadPool::fun() {
    while (true) {
        std::unique_lock<std::mutex> lock(locker_);
        queueIsEmpty_.wait(lock, [=] {
            return !functions_.empty() || flag_;
        });
        if (flag_) {
            break;
        }
        std::function<void()> doItFunc = functions_.front();
        functions_.pop();
//        std :: cout << "I'm " << i << std :: endl;
        doItFunc();

    }
}

ThreadPool :: ThreadPool (size_t numberOfThreads) : numberOfThreads_(numberOfThreads)
{
    // Q: [=], [&], [this]
    for (std::size_t i = 0; i < numberOfThreads; ++i) { //add threads in vector
        threads_.emplace_back(fun, this);
    }
}



ThreadPool :: ~ThreadPool()
{
    flag_ = true;
    for (auto &th: threads_) { // for all threads
            th.join();
    }
}



void ThreadPool :: execute(std::function<void()> const &foo)
{
    std::unique_lock<std::mutex> lock(locker_);
    functions_.push(foo);
    queueIsEmpty_.notify_one();
}