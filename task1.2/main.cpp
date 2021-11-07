#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>

std::double_t integral(std::function<std::double_t(std::double_t)> f,
                       std::double_t a, std::double_t b, std::size_t n) {
  std::double_t step = (b - a) / n;
  std::double_t res = 0;
  for (; a < b; a += step) {
    res += f(a) * step;
  }
  return res;
}

int main() {
  std::cout << integral([](std::double_t x) { return std::sqrt(x); }, 1, 5, 1e9)
            << std::endl;
}
