cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Detector VERSION 0.1.0 LANGUAGES CXX)

## This is not recommended:
set(CMAKE_CXX_COMPILER "g++")
#set(CMAKE_CXX_COMPILER "clang++")

set(MY_FLAGS "")
set(MY_FLAGS "${MY_FLAGS} -O3")
set(MY_FLAGS "${MY_FLAGS} -Wall")
set(MY_FLAGS "${MY_FLAGS} -Wextra")
set(MY_FLAGS "${MY_FLAGS} -Wshadow")
set(MY_FLAGS "${MY_FLAGS} -Wnon-virtual-dtor")
set(MY_FLAGS "${MY_FLAGS} -Wold-style-cast")
set(MY_FLAGS "${MY_FLAGS} -Wcast-align")
set(MY_FLAGS "${MY_FLAGS} -Wunused")
set(MY_FLAGS "${MY_FLAGS} -Woverloaded-virtual")
set(MY_FLAGS "${MY_FLAGS} -Wpedantic")
set(MY_FLAGS "${MY_FLAGS} -Wconversion")
#set(MY_FLAGS "${MY_FLAGS} -mlong-double-64")
#set(MY_FLAGS "${MY_FLAGS} -Weverything")
#set(MY_FLAGS "${MY_FLAGS} -Wno-c++98-compat")
set(CMAKE_CXX_FLAGS ${MY_FLAGS})

find_package(Catch2 3 REQUIRED)

#find_package(
#  Eigen3 3.4 REQUIRED
#  PATHS ./eigen
#  NO_DEFAULT_PATH
#  NO_MODULE
#)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSION OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(test)

