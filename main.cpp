/**
 * @file main.cpp
 *
 * @author Natalya Sannikova (natalyasann2@gmail.com)
 * @date 07.09.2017
 * @version 1.0
 */



#include <iostream>
#include "ThreadPool.h"

using namespace std;

void foo()
{
    for (int i = 0; i < 10; i++) {
        std::cout << "foo() : " << i <<  std::endl;
    }
}



int main() {
    {
        std::cerr << "start" << std::endl;

        ThreadPool ttt(2);

        ttt.execute([] {std::this_thread::sleep_for(std::chrono::seconds(10)); std::cerr << "first" << std::endl; });
        std::this_thread::sleep_for(std::chrono::seconds(1));

        ttt.execute([] {std::cerr << "here" << std::endl; });

        std::this_thread::sleep_for(std::chrono::seconds(11));
        std::cerr << "end" << std::endl;

    }

    return 0;
    /*{
        ThreadPool tttttt(2);


    }
    std::cout << "asdf" << std::endl;

    return 0;*/

    std :: size_t numberOfThreads;
    std :: cin >> numberOfThreads;

    ThreadPool threadPool(numberOfThreads);
    threadPool.execute(foo);
    threadPool.execute(foo);
    threadPool.execute(foo);
    threadPool.execute(foo);
    threadPool.execute(foo);
    threadPool.execute(foo);

    std:: cout<<"END MAIN";

    return 0;
}