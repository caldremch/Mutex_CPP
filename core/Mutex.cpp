//
// Created by Caldremch on 2019/4/25.
//

#include "Mutex.h"
#include <iostream>
Mutex::Mutex() {
    std::cout << "调用构造函数Mutex" << std::endl;
}

Mutex::~Mutex() {
    std::cout << "调用析构函数~Mutex" << std::endl;
}
