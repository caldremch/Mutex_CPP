cmake_minimum_required(VERSION 3.14)
project(Mutex_CPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp core/Mutex.cpp core/Mutex.h MutexMain.cpp)
add_executable(Mutex_CPP ${SOURCE_FILES})