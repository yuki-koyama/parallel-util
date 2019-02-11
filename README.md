# parallel-util

Simple implementation of `parallel_for` and `parallel_map` using C++11.

This library is based on multi-threading on CPU (`std::thread`) and the default concurrency is set to the hardware concurrency (`std::thread::hardware_concurrency()`).

## Usage of `parallel_for`

Suppose that you have a callable function that can be stored by an instance of `std::function<void(int)>`; for example, defined by C++11 lambda expression:
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

(TODO)

Example:
```
auto func = [](double x) { return x * x; }
```
```
std::vector<double> input = { 0.2, 0.9, - 0.4, 0.5, 0.3 };
```
```
auto output = parallelutil::parallel_map(input, func);
```
`output` is an array: `{ 0.04, 0.81, 0.16, 0.25, 0.09 }`.

If you are using C++17 Parallel STL, `std::transform` has similar functionality.

## Installation

`parallel-util` is a header-only, single-file library. It can be used by just copying `parallel-util.hpp` and pasting it into your project.

Alternatively, it can be installed using `cmake`. If your project is also managed using `cmake`, `ExternalProject` commands are useful for including `parallel-util` to your project.

## Persuing Further Performance

Please consider to use other complex libraries such as Intel(R) Threading Building Blocks.

## Projects using parallel-util

- Unblending <https://github.com/yuki-koyama/unblending>
- OptiMo <https://github.com/yuki-koyama/optimo>
- Sequential Line Search <https://github.com/yuki-koyama/sequential-line-search>
- SelPh <https://github.com/yuki-koyama/selph>

## LICENSING

MIT License.
