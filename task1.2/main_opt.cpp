#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>

#ifndef __AVX2__
#error "No AVX support"
#endif
#include <immintrin.h>

std::double_t integral(std::function<__m256d(__m256d)> f, std::double_t a,
                       std::double_t b, std::size_t n) {
  std::double_t step = (b - a) / (4 * n);
  __m256d _step = _mm256_set1_pd(step);
  __m256d _res = _mm256_set1_pd(0);
  for (__m256d _a = _mm256_set_pd(a, a + step, a + 2 * step, a + 3 * step),
               _b = _mm256_set1_pd(b), _add = _mm256_set1_pd(4 * step);
       n > 0; _a = _mm256_add_pd(_a, _add), --n) {
    _res = _mm256_fmadd_pd(f(_a), _step, _res);
  }
  std::double_t res[4];
  _mm256_storeu_pd(res, _res);
  return res[0] + res[1] + res[2] + res[3];
}

int main() {
  std::cout << integral([](__m256d x) { return _mm256_sqrt_pd(x); }, 1, 5, 1e9/4)
            << std::endl;
}
