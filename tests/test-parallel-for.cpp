#include <vector>
#include <parallel-util.hpp>

using parallelutil::parallel_for;
using parallelutil::parallel_map;

int main()
{
    // Array of random numbers
    const std::vector<int> numbers = { 4, 2, 90, 58, 19, 59, 18, 24, 9 };

    // -------------------------------------------------------------------------
    // parallel_for
    // -------------------------------------------------------------------------

    std::vector<int> parallel_for_results(numbers.size());

    // Process of squaring the i-th number in an input array and store it
    auto square_i_th_element = [&numbers, &parallel_for_results](int i)
    {
        parallel_for_results[i] = numbers[i] * numbers[i];
    };

    // Perform the process in parallel
    // The result is equivalent to:
    // for (int i = 0; i < numbers.size(); ++ i) { square(i); }
    parallel_for(numbers.size(), square_i_th_element);

    // -------------------------------------------------------------------------
    // parallel_map
    // -------------------------------------------------------------------------

    // Process of squaring a number
    auto square = [](int number)
    {
        return number * number;
    };

    // Perform "map" operation in parallel
    const std::vector<int> parallel_map_results = parallel_map(numbers, square);

    return 0;
}
