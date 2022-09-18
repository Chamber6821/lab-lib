cmake_minimum_required(VERSION 3.23)
project(lab-lib C)

set(CMAKE_C_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.c")
add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
