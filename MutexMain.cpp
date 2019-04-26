//
// Created by Caldremch on 2019/4/26.
//

#include<iostream>
#include "core/Mutex.h"

void invokeTest();

int main(){

    invokeTest();
    return 0;
}

void invokeTest()
{
    std::cout << "in function invokeTest start" << std::endl;
    Mutex mutex;
    std::cout << "in function invokeTest finish" << std::endl;
}