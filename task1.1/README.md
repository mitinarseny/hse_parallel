# Задание 1.1. Вариант 5. Деление

Исходный код программы можно найти в файле [`main.cpp`](./main.cpp).

Для векторного деления были использованы `_mm_div_pd` (SSE2) и `_mm256_div_pd` (AVX2) и соответствующие функции для подготовки векторных типов.

## Сборка

> **NOTE**: `clang v12.0.1`

```sh
$ cmake \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_BUILD_TYPE=Release \
  -B build
$ cmake --build build
```

## Результаты

Вычислительная система:
* CPU: Intel(R) Core(TM) i7-10510U 2.3 GHz
* Cores: 8
* RAM: 16GB

```sh
$ ./build/hse_parallel_task1_1
HSE Paralell computations. Task 1.1 (division)
NUM_OPERATIONS: 1032
====== Simple
75.8217 (cycles/op),    total: 78248 cycles
33.3595 (ns/op),        total: 34427 ns
====== SSE2
27.6279 (cycles/op),    total: 28512 cycles
12.1831 (ns/op),        total: 12573 ns
====== AVX2
17.4787 (cycles/op),    total: 18038 cycles
7.85465 (ns/op),        total: 8106 ns
```

Из полученных результатов видно, что при использовании `SSE2` векторизации
время выполнения сократилось чуть больше, чем в два раза, а при `AVX2` - в 4.
Результаты похожи на правду, потому что отношение количество циклов к
процессорному времени не изменяется от типа выполняемой операции, и примерно равно
заявленной производителем частотой процессора.
