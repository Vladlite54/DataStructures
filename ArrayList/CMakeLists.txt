cmake_minimum_required(VERSION 3.5)
project(ArrayList)

set(SOURCE main.cpp)
set(LIB_FILES ArrayList.h Menu.h Menu.cpp)

add_executable(ArrayList ${LIB_FILES} ${SOURCE})