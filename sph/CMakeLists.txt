cmake_minimum_required(VERSION 3.0)
project(sph_test)

set(VTK_DIR "/home/haustei4/Software/VTK-8.0.1/")
set(CMAKE_BUILD_TYPE Debug)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

 
include_directories(src)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(sph ${SOURCES})

target_link_libraries(sph ${VTK_LIBRARIES})
