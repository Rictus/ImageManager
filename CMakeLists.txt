cmake_minimum_required(VERSION 3.6)
project(ImageManager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES ImageManager.cpp ImageManager.h main.cpp)
add_executable(ImageManager ${SOURCE_FILES})
add_library(ImageManagerLib SHARED ${SOURCE_FILES})


# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})