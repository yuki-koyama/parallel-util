#include <vector>
#include <parallel-util.hpp>

using parallelutil::parallel_map;

int main()
{
    // Array of random numbers
    const std::vector<int> numbers = { 4, 2, 90, 58, 19, 59, 18, 24, 9 };

    // Process of squaring a number
    auto square = [](int number)
    {
        return number * number;
    };

    // Perform "map" operation in parallel
    const std::vector<int> parallel_map_results = parallel_map(numbers, square);

    return 0;
}
