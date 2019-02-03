cmake_minimum_required(VERSION 3.1)

project(parallel-util CXX)
set(CMAKE_CXX_STANDARD 11)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/parallel-util.hpp DESTINATION include)

find_package(Threads REQUIRED)

add_library(parallel-util INTERFACE)
target_sources(parallel-util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/parallel-util.hpp)
target_include_directories(parallel-util INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(parallel-util INTERFACE ${CMAKE_THREAD_LIBS_INIT})

option(PARALLELUTIL_BUILD_TESTS "Build tests" OFF)

if(PARALLELUTIL_BUILD_TESTS)
	add_subdirectory(tests)

	enable_testing()
	add_test(NAME test-parallel-for COMMAND $<TARGET_FILE:test-parallel-for>)
	add_test(NAME test-parallel-map COMMAND $<TARGET_FILE:test-parallel-map>)
endif()
