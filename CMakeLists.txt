cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(raytracer C CXX)

set(SOURCE_FILES
	src/main.cpp
	src/Image.hpp
	src/Image.cpp
	src/Kernel.hpp
	src/Kernel.cpp
	src/Point3.hpp
	src/Point3.cpp
	src/RGB.hpp
)

add_executable(raytracer ${SOURCE_FILES})