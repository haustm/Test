cmake_minimum_required(VERSION 2.8.9)
project(sph_test)
 
include_directories(src)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(sph ${SOURCES})
