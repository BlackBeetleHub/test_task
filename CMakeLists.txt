cmake_minimum_required(VERSION 3.6)

project('test_task')

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCE_FILES *.cpp)

add_executable(task ${SOURCE_FILES})

target_link_libraries(task -lgmpxx -lgmp)