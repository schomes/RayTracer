cmake_minimum_required(VERSION 2.6)

project(raytracer C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
	src/main.cpp
	src/Image.hpp
	src/Image.cpp
	src/RayTracer.hpp
	src/RayTracer.cpp
	src/Point3.hpp
	src/Point3.cpp
	src/Vector3.hpp
	src/Vector3.cpp
	src/HVector.hpp
	src/Ray.hpp
	src/Ray.cpp
	src/Material.hpp
	src/Material.cpp
	src/Surface.hpp
	src/Surface.cpp
	src/Sphere.hpp
	src/Sphere.cpp
	src/Ellipsoid.hpp
	src/Ellipsoid.cpp
	src/Triangle.hpp
	src/Triangle.cpp
	src/RGB.hpp
	src/RGB.cpp
	src/Light.hpp
	src/Camera.cpp
	src/Camera.hpp
	src/Perspective.hpp
	src/Perspective.cpp
	src/Orthographic.hpp
	src/Orthographic.cpp
)

add_executable(raytracer ${SOURCE_FILES})
