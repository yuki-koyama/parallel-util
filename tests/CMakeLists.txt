add_executable(test-parallel-for test-parallel-for.cpp)
target_link_libraries(test-parallel-for parallel-util)

add_executable(test-parallel-map test-parallel-map.cpp)
target_link_libraries(test-parallel-map parallel-util)

add_executable(test-parallel-exec test-parallel-exec.cpp)
target_link_libraries(test-parallel-exec parallel-util)
