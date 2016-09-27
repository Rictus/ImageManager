cmake_minimum_required(VERSION 3.6)
project(ImageManager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(NRC_SOURCE_FILES NRC/def.h NRC/nralloc.c NRC/nralloc.h NRC/nrarith.c NRC/nrarith.h NRC/nrio.c NRC/nrio.h)
set(SOURCE_FILES FileException.h Image.cpp Image.h main.cpp)

add_executable(ImageManager ${SOURCE_FILES} ${NRC_SOURCE_FILES} )

add_library(ImageManagerLib SHARED ${SOURCE_FILES} ${NRC_SOURCE_FILES} )

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})