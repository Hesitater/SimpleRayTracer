cmake_minimum_required(VERSION 3.12)
project(SimpleRayTracer)

set(CMAKE_CXX_STANDARD 11)

add_executable(SimpleRayTracer main.cpp Vector3.h Ray.h Hitable.h Sphere.h HitableList.h Camera.h Material.h)