cmake_minimum_required(VERSION 3.16)
project(raytracer)

find_package(MPI REQUIRED)

add_executable(test
  camera.cpp 
  hit.cpp 
  lodepng.cpp 
  main.cpp
  pixels.cpp
  ray.cpp
  roundoff.cpp
  sphere.cpp
  vector3d.cpp
  world.cpp
  parser.cpp
  materials.cpp
  specular.cpp
  diffuse.cpp
  metal.cpp
  unreal.cpp
  random.cpp
  texture.cpp
  solid.cpp
  check.cpp
  gradient.cpp
  glass.cpp
  object.cpp
  triangle.cpp
)
target_compile_options(test PUBLIC -g -std=c++17 -Ofast -flto)
target_link_libraries(test ${SOURCES} ${MPI_LIBRARIES})

#cmake  -DCMAKE_CXX_COMPILER=/usr/bin/mpic++ ..