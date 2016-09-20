cmake_minimum_required(VERSION 3.6)
project(ImageManager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ImageManager.cpp ImageManager.h)
add_executable(ImageManager ${SOURCE_FILES} ImageManager.cpp ImageManager.h main.cpp main.h)
add_library(ImageManagerLib  ${SOURCE_FILES} ImageManager.cpp ImageManager.h)
include_directories()