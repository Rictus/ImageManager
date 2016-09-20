cmake_minimum_required(VERSION 3.6)
project(Compteur)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ImageManager.cpp ImageManager.h)
add_executable(Compteur ${SOURCE_FILES} ImageManager.cpp ImageManager.h)