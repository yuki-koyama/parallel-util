#ifndef parallel_util_hpp
#define parallel_util_hpp

#include <vector>
#include <thread>

namespace parallelutil
{
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
}

#endif /* parallel_util_hpp */
