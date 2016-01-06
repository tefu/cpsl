cmake_minimum_required(VERSION 2.8)
project(cpsl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(FLEX)
flex_target(scanner cpsl.lex ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
set(SOURCES scanner)
add_executable(cpsl ${SOURCES})
