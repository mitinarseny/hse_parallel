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

[[clang::optnone]] std::uint64_t simple(std::size_t nops, std::double_t a,
                                        std::double_t b) {
  std::uint64_t tsc = readTSC();

  for (std::size_t i = 0; i < nops; ++i)
    a = a / b;

  return readTSC() - tsc;
}

[[clang::optnone]] std::uint64_t sse2(std::size_t nops, std::double_t a,
                                      std::double_t b) {
  __m128d _a = _mm_set1_pd(a), _b = _mm_set1_pd(b);
  std::uint64_t tsc = readTSC();

  for (std::size_t i = 0; i < nops; i+=2)
    _a = _mm_div_pd(_a, _b);

  return readTSC() - tsc;
}

[[clang::optnone]] std::uint64_t avx2(std::size_t nops, std::double_t a,
                                      std::double_t b) {
  __m256d _a = _mm256_set1_pd(a), _b = _mm256_set1_pd(b);
  std::uint64_t tsc = readTSC();

  for (std::size_t i = 0; i < nops; i+=4)
    _a = _mm256_div_pd(_a, _b);

  return readTSC() - tsc;
}

void print_stats(std::size_t nops, std::uint64_t tsc,
                 std::chrono::system_clock::time_point started_at) {
  std::chrono::duration<double> took_s =
      std::chrono::system_clock::now() - started_at;
  std::float_t took_ns = took_s.count() * 1e9;
  std::cout << static_cast<std::float_t>(tsc) / nops
            << " (cycles/op),\ttotal: " << tsc << " cycles" << std::endl
            << took_ns / nops << " (ns/op),\ttotal: " << took_ns << " ns"
            << std::endl;
}

int main() {
  std::cout << "HSE Paralell computations. Task 1.1 (division)" << std::endl;
  const std::double_t A = 1 << 30, B = 2.1;
  std::size_t NUM_OPERATIONS = 0;
  for (std::double_t a = A, b = B; a > 0; a /= b) {
    ++NUM_OPERATIONS;
  }
  std::cout << "NUM_OPERATIONS: " << NUM_OPERATIONS << std::endl;
  {
    std::cout << "====== Simple" << std::endl;
    auto started_at = std::chrono::system_clock::now();
    std::uint64_t tsc = simple(NUM_OPERATIONS, A, B);
    print_stats(NUM_OPERATIONS, tsc, started_at);
  }
  {
    std::cout << "====== SSE2" << std::endl;
    auto started_at = std::chrono::system_clock::now();
    std::uint64_t tsc = sse2(NUM_OPERATIONS, A, B);
    print_stats(NUM_OPERATIONS, tsc, started_at);
  }
  {
    std::cout << "====== AVX2" << std::endl;
    auto started_at = std::chrono::system_clock::now();
    std::uint64_t tsc = avx2(NUM_OPERATIONS, A, B);
    print_stats(NUM_OPERATIONS, tsc, started_at);
  }
}
