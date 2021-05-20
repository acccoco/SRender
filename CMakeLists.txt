cmake_minimum_required(VERSION 3.19)
project(SRender)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)


add_executable(SRender main.cpp glm.hpp pipeline.hpp)
target_link_libraries(SRender ${OpenCV_LIBRARIES})

add_executable(Test test.cpp)
