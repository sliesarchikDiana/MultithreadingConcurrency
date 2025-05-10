cmake_minimum_required(VERSION 3.30)
project(MultithreadingConcurrency)

set(CMAKE_CXX_STANDARD 20)

add_executable(MultithreadingConcurrency main.cpp
        task1-2DataRace.cpp
        task4.cpp
        task5.cpp
        task5.h
)
