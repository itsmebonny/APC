cmake_minimum_required(VERSION 3.14)
project(DocumentStore)

set(CMAKE_CXX_STANDARD 11)

add_executable(DocumentStore main.cpp DocumentStore.cpp Document.h Document.cpp DocumentStore.h)