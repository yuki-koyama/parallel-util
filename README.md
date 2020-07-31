# parallel-util

![Test](https://github.com/yuki-koyama/parallel-util/workflows/Test/badge.svg)

A single-header implementation of `parallel_for`, `parallel_map`, and `parallel_exec` using C++11.

This library is based on multi-threading on CPU (`std::thread`) and the default concurrency is set to the hardware concurrency (`std::thread::hardware_concurrency()`).

## Usage of `parallel_for`

Suppose that you have a callable function that can be stored by an instance of `std::function<void(int)>`, for example, defined by C++11 lambda expression:
```
auto process = [](int i) { ... };
```
and want to parallelize the following for-loop procedure:
```
for (int i = 0; i < n; ++ i) { process(i); }
```
By using parallel-util, this can be easily parallelized by
```
parallelutil::parallel_for(n, process);
```

## Usage of `parallel_map`

Suppose that you have a callable function that takes an instance of `T1` as input and returns an instance of `T2` as output, and thus can be stored by an instance of `std::function<T2(T1)>`. For example,
```
auto square = [](double x) { return x * x; };
```
In this case, `T1` = `T2` = `double`. Also suppose that you have an array of `T1` and want to obtain an array of `T2` by applying the function to each array element. For example, you have an array:
```
std::vector<double> input_array = { 0.2, 0.9, - 0.4, 0.5, 0.3 };
```
and want to their squares. By using parallel-util, this can be easily parallelized by
```
auto output_array = parallelutil::parallel_map(input_array, square);
```
where `output_array` is an array: `{ 0.04, 0.81, 0.16, 0.25, 0.09 }`.

If you are using C++17 Parallel STL, `std::transform` has similar functionality.

## Usage of `parallel_exec`

An arbitrary number of functions whose type is `std::function<void()>`, for example,
```
auto process_1 = [](){ ... };
auto process_2 = [](){ ... };
auto process_3 = [](){ ... };
```
can be executed in parallel by
```
parallelutil::parallel_exec({ process_1, process_2, process_3 });
```

## Installation

`parallel-util` is a header-only, single-file library. It can be used by just copying `parallel-util.hpp` and pasting it into your project.

Alternatively, it can be installed using `cmake`. If your project is also managed using `cmake`, `ExternalProject` or `add_subdirectory` commands are useful for including `parallel-util` to your project.

If you want to install `parallel-util` to your system, use the typical `cmake` cycle:
```
git clone https://github.com/yuki-koyama/parallel-util.git
mkdir build
cd build
cmake ../parallel-util
make install
```

## Dependencies

- C++ Standard Library; Thread support library (require `-pthread`)

## Persuing Further Performance

Please consider to use more sophisticated libraries such as Intel(R) Threading Building Blocks.

## Projects using parallel-util

- Unblending <https://github.com/yuki-koyama/unblending>
- OptiMo <https://github.com/yuki-koyama/optimo>
- Sequential Line Search <https://github.com/yuki-koyama/sequential-line-search>
- SelPh <https://github.com/yuki-koyama/selph>

## LICENSING

MIT License.
