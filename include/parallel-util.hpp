/// \file parallel-util.hpp

#ifndef parallel_util_hpp
#define parallel_util_hpp

#include <vector>
#include <thread>

namespace parallelutil
{
    /// \brief Execute a for-loop process for an array in parallel
    /// \param n The number of iterations. I.e., { 0, 1, ..., n - 1 } will be visited.
    /// \param function The function that will be called in the for-loop. This can be specified as a lambda expression. The type should be equivalent to std::function<void(int)>.
    /// \param target_concurrency The number of threads that will be generated. When this is set to zero (which is the default), the hardware concurrency will be automatically used.
    template<typename Callable>
    void parallel_for(int n, Callable function, int target_concurrency = 0)
    {
        const int hint      = (target_concurrency == 0) ? std::thread::hardware_concurrency() : target_concurrency;
        const int n_threads = std::min(n, (hint == 0) ? 4 : hint);
        
        auto inner_loop = [n, n_threads, function](const int j)
        {
            const int start_index = j * (n / n_threads);
            const int end_index   = (j + 1 == n_threads) ? n : (j + 1) * (n / n_threads);
            
            for (int k = start_index; k < end_index; ++ k) { function(k); }
        };
        std::vector<std::thread> threads;
        for (int j = 0; j < n_threads; ++ j) { threads.push_back(std::thread(inner_loop, j)); }
        for (auto& t : threads) { t.join(); }
    }
    
    /// \brief Execute a for-loop process for a 2D array (e.g., a bitmap image data) in parallel
    /// \param width The width of the target 2D array. I.e., { 0, 1, ..., width - 1 } will be visited as the first dimensional indices.
    /// \param height The height of the target 2D array. I.e., { 0, 1, ..., height - 1 } will be visited as the second dimensional indices.
    /// \param function The function that will be called in the for-loop. This can be specified as a lambda expression. The type should be equivalent to std::function<void(int, int)>.
    /// \param target_concurrency The number of threads that will be generated. When this is set to zero (which is the default), the hardware concurrency will be automatically used.
    template<typename Callable>
    void parallel_for_2d(int width, int height, Callable function, int target_concurrency = 0)
    {
        const int hint      = (target_concurrency == 0) ? std::thread::hardware_concurrency() : target_concurrency;
        const int n_threads = std::min(width * height, (hint == 0) ? 4 : hint);
        
        auto inner_loop = [width, height, n_threads, function](const int j)
        {
            const int n = width * height;
            
            const int start_index = j * (n / n_threads);
            const int end_index   = (j + 1 == n_threads) ? n : (j + 1) * (n / n_threads);
            
            for (int k = start_index; k < end_index; ++ k) { function(k % width, k / width); }
        };
        std::vector<std::thread> threads;
        for (int j = 0; j < n_threads; ++ j) { threads.push_back(std::thread(inner_loop, j)); }
        for (auto& t : threads) { t.join(); }
    }

#if __cplusplus >= 201402L
    template<typename T, typename Callable>
    decltype(auto) parallel_map(const std::vector<T>& input_array, Callable op, int target_concurrency = 0)
    {
        std::vector<decltype(op(input_array.front()))> result_array(input_array.size());
        auto indexed_op = [&](int index) { result_array[index] = op(input_array[index]); };
        parallel_for(input_array.size(), indexed_op);
        return result_array;
    }
#endif
}

#endif /* parallel_util_hpp */
