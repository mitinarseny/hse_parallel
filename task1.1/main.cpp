#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <emmintrin.h>
#include <iostream>

#ifndef __SSE2__
#error "No SSE2 support"
#endif
#ifndef __AVX2__
#error "No AVX support"
#endif
#include <immintrin.h>

#ifndef __x86_64__
#error "Not x86_64"
#endif
#include <x86intrin.h>

inline std::uint64_t readTSC() {
  std::uint32_t dummy;
  return __rdtscp(&dummy);
}

int main() {
  std::cout << "HSE Paralell computations. Task 1.1 (division)" << std::endl;
  const std::double_t A = 1 << 30, B = 2.1;
  std::size_t NUM_OPERATIONS = 0;
  for (std::double_t a = A, b = B; a > 0; a /= b) {
    ++NUM_OPERATIONS;
  }
  std::cout << "NUM_OPERATIONS: " << NUM_OPERATIONS << std::endl;

#define BEGIN_STATS                                                            \
  auto started_at = std::chrono::system_clock::now();                          \
  std::uint64_t tsc = readTSC()
#define PRINT_STATS                                                            \
  tsc = readTSC() - tsc;                                                       \
  std::chrono::duration<double> took_s =                                       \
      std::chrono::system_clock::now() - started_at;                           \
  std::float_t took_ns = took_s.count() * 1e9;                                 \
  std::cout << static_cast<std::float_t>(tsc) / NUM_OPERATIONS                 \
            << " (cycles/op),\ttotal: " << tsc << " cycles" << std::endl       \
            << took_ns / NUM_OPERATIONS << " (ns/op),\ttotal: " << took_ns     \
            << " ns" << std::endl

  {
    std::cout << "====== Simple division" << std::endl;
    std::double_t a = A, b = B;
    BEGIN_STATS;

    for (std::size_t i = 0; i < NUM_OPERATIONS; ++i)
      a /= b;

    PRINT_STATS;
  }

  {
    std::cout << "====== SSE2 division" << std::endl;
    __m128d a = _mm_set1_pd(A), b = _mm_set1_pd(B);
    BEGIN_STATS;

    for (std::size_t i = 0; i < NUM_OPERATIONS; ++i)
      a = _mm_div_pd(a, b);

    PRINT_STATS;
  }

  {
    std::cout << "====== AVX2 division" << std::endl;
    __m256d a = _mm256_set1_pd(A), b = _mm256_set1_pd(B);
    BEGIN_STATS;

    for (std::size_t i = 0; i < NUM_OPERATIONS; ++i)
      a = _mm256_div_pd(a, b);

    PRINT_STATS;
  }
}
