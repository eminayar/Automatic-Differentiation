cmake_minimum_required(VERSION 3.8)
project(backprob)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        code/function.cpp
        code/function.h
        code/graph.cpp
        code/graph.h
        code/main.cpp
        code/variable.cpp
        code/variable.h)

add_executable(backprob ${SOURCE_FILES})