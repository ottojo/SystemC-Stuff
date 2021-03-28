cmake_minimum_required(VERSION 3.19)
project(SystemCKlausur)

set(CMAKE_CXX_STANDARD 17)

find_package(SystemCLanguage REQUIRED)

add_executable(adder adder.main.cpp)
target_link_libraries(adder SystemC::systemc)

add_executable(filter filter.main.cpp)
target_link_libraries(filter SystemC::systemc)

add_executable(demux demux.main.cpp)
target_link_libraries(demux SystemC::systemc)
