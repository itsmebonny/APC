cmake_minimum_required(VERSION 3.20)
project(LibraryInitialCode)

set(CMAKE_CXX_STANDARD 11)

add_executable(LibraryInitialCode main.cpp Book.cpp Book.h Library.cpp Library.h)