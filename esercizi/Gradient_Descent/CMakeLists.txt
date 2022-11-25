cmake_minimum_required(VERSION 3.20)
project(Gradien_Descent)

set(CMAKE_CXX_STANDARD 11)
add_executable(Gradient_Descent main.cpp Function.h Function.cpp FunctionMin.cpp FunctionMin.h)