cmake_minimum_required(VERSION 2.8)
project(cpsl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(FLEX)
find_package(BISON)
find_package(Boost COMPONENTS program_options)
flex_target(scanner cpsl.lex ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
bison_target(parser cpsl.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
        COMPILE_FLAGS "-d -W -v --report-file=${CMAKE_CURRENT_BINARY_DIR}/bison.output")


set(COMMON_SOURCES
        src/instructions.hpp
        src/instructions.cpp src/Expression.cpp src/Expression.hpp src/ProgramNode.hpp)

set(COMPILER_SOURCES
        parser
        scanner src/main.cpp)

set(TEST_SOURCES
        unit-tests/main.cpp unit-tests/mips_test.cpp unit-tests/expression_test.cpp)


include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/unit-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(cpsl ${COMPILER_SOURCES} ${COMMON_SOURCES})
add_executable(unit_tests ${TEST_SOURCES} ${COMMON_SOURCES})
enable_testing(true)

add_custom_command(TARGET cpsl
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/language-tests/language_test.sh"
        "${CMAKE_CURRENT_BINARY_DIR}/language_test.sh"
        DEPENDS "${CMAKE_SOURCE_DIR}/language-tests/language_test.sh")

add_custom_command(TARGET cpsl
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/language-tests/Mars4_4.jar"
        "${CMAKE_CURRENT_BINARY_DIR}/Mars4_4.jar")

file(GLOB language_tests ${CMAKE_SOURCE_DIR}/language-tests/test-files/*.cpsl)
foreach (language_test_dir ${language_tests})
    get_filename_component(language_test ${language_test_dir} NAME)
    add_custom_command(TARGET cpsl
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${language_test_dir}
        "${CMAKE_CURRENT_BINARY_DIR}/test-files/${language_test}"
        DEPENDS "${CMAKE_SOURCE_DIR}/language-tests/test-files")
endforeach()

add_custom_target(language_test
        COMMAND ./language_test.sh
        DEPENDS cpsl "${CMAKE_CURRENT_BINARY_DIR}/language_test.sh" )

