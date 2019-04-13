cmake_minimum_required(VERSION 3.13)
project(queue)

set(CMAKE_CXX_STANDARD 14)
set(SOURSE_LIB queue.cpp)
add_library(queue STATIC ${SOURSE_LIB})
add_executable(main main.cpp)
target_link_libraries(main queue)