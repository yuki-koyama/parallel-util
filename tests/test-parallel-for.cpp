#include <vector>
#include <parallel-util.hpp>

using parallelutil::parallel_for;

int main()
{
    // Array of random numbers
    std::vector<int> numbers = { 4, 2, 90, 58, 19, 59, 18, 24, 9 };
    
    // Process of squaring the i-th number
    auto square = [&numbers](int i)
    {
        numbers[i] = numbers[i] * numbers[i];
    };
    
    // Perform the process in parallel
    // The result is equivalent to:
    // for (int i = 0; i < numbers.size(); ++ i) { square(i); }
    parallel_for(numbers.size(), square);
    
    return 0;
}
