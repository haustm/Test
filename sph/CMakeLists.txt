cmake_minimum_required(VERSION 2.8.9)
project(sph_test)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
include_directories(src)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(sph ${SOURCES})

target_link_libraries(sph ${VTK_LIBRARIES})
