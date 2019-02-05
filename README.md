# parallel-util

Simple implementation of "parallel_for" and "parallel_map" using C++11.

This library is based on multi-threading on CPU (`std::thread`) and the default concurrency is set to the hardware concurrency (`std::thread::hardware_concurrency()`).

## Usage of `parallel_for`

Suppose that you have a process expressed using C++11 lambda expressions:
```
auto process = [](int i) { ... };
```
and want to parallelize the following for loop:
```
for (int i = 0; i < n; ++ i) { process(i); }
```
This can be easily parallelized by
```
parallelutil::parallel_for(n, process);
```

## Usage of `parallel_map`

(TODO)

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
