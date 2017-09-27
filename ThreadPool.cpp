/**
 * @file ThreadPool.cpp
 *
 * @author Natalya Sannikova (natalyasann2@gmail.com)
 * @date 07.09.2017
 * @version 1.0
 */

#include <iostream>
#include <atomic>
#include "ThreadPool.h"
/*
class my_unique_lock {
public:
    std::mutex &locker_;

    my_unique_lock(std::mutex &locker) : locker_(locker) {
        locker_.lock();
    }

    ~my_unique_lock() {
        locker_.unlock();
    }
};

class my_conditional_variable {
public:
    std::atomic_bool _is_notified;

    my_conditional_variable()
            : _is_notified(false) {}

    void wait(my_unique_lock lock) {
        lock.locker_.unlock();

        while (!_is_notified) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        lock.locker_.lock();
    }

    void notify_one() {
        _is_notified = true;
    }
};
*/

ThreadPool::ThreadPool(size_t numberOfThreads) : numberOfThreads_(numberOfThreads) {
    /*
     Q: [=], [&], [this]
     Data race, dead lock
     A:
    [=] - захват локальных переменных, т.е. доступ к ним
    [&] - захват локальных переменных по ссылке
    [this] - захват членов класса (в функции-члене класса)
    */
    for (std::size_t i = 0; i < numberOfThreads; ++i) { //add threads in vector
        threads_.emplace_back([this, i] //если написать [this] i не будет доступна;
                              {
                                  while (true) {
                                      std::unique_lock<std::mutex> lock(locker_); //для доступа к вектору
                                      while (functions_.empty() && !flag_) {
                                          queueIsEmpty_.wait(lock);
                                      }
                                      /*
                                        queueIsEmpty_.wait(lock, [=] {
                                        return !functions_.empty() || flag_;
                                        });
                                       */

                                      if (flag_) { break; }
                                      std::function<void()> doItFunc = functions_.front();
                                      functions_.pop();
                                      std::cout << "I'm " << i << std::endl;
                                      doItFunc();
                                  }
                              }
        );
    }
}


ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(locker_);//для доступа к вектору
        flag_ = true;
        //or locker_.unlock();
    }

    queueIsEmpty_.notify_all();
    for (auto &th: threads_) { // for all threads
        th.join();
    }
}


void ThreadPool::execute(std::function<void()> const &foo) {
    std::unique_lock<std::mutex> lock(locker_);//для доступа к вектору
    functions_.push(foo);
    queueIsEmpty_.notify_one();
}