#include <vector>
#include <iostream>
#include <parallel-util.hpp>

using parallelutil::parallel_exec;

int main()
{
    // Define processes that will be executed in parallel
    auto process_1 = []()
    {
        std::cout << "process 1\n";
    };
    auto process_2 = []()
    {
        std::cout << "process 2\n";
    };
    auto process_3 = []()
    {
        std::cout << "process 3\n";
    };

    // Execute processes in parallel
    parallel_exec({ process_1, process_2, process_3 });

    return 0;
}
