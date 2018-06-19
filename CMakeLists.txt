cmake_minimum_required(VERSION 3.1)

project(parallel-util CXX)
set(CMAKE_CXX_STANDARD 11)

install(FILES ./parallel-util.hpp DESTINATION include)

option(PARALLELUTIL_BUILD_TESTS "Build tests" OFF)

if(PARALLELUTIL_BUILD_TESTS)
	include_directories(${CMAKE_SOURCE_DIR})
	add_subdirectory(tests)

	enable_testing()
	add_test(NAME test-parallel-for COMMAND $<TARGET_FILE:test-parallel-for> ${CMAKE_BINARY_DIR})
endif()
