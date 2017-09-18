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