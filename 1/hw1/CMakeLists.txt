cmake_minimum_required(VERSION 2.8)

project(homework1)


find_package( Sophus REQUIRED)

include_directories(${Sophus_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")

add_executable(main main.cpp)
target_link_libraries(main ${Sophus_LIBRARIES})

