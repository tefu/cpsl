cmake_minimum_required(VERSION 2.8)
project(cpsl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(FLEX)
find_package(BISON)
flex_target(scanner cpsl.lex ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
bison_target(parser cpsl.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp COMPILE_FLAGS "-d -W")
set(SOURCES parser scanner)
add_executable(cpsl ${SOURCES})
