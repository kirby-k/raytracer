#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
/*
int main() {
  // loss of precision through subtraction
  std::cout << std::setprecision(std::numeric_limits<double>::max_digits10+1);
  std::cout << "Loss of precision through subtraction:\n  ";
  double little = 1;
  double big = 1e16;
  std::cout << little << " + " << big << " - " << big;
  std::cout << " = " << little+big-big << "\n  ";
  
  std::cout << big << " - " << big << " + " << little;
  std::cout << " = " << big-big+little << "\n\n";

  
  // error propagation in arithmetic
  std::cout << "Error propagation in addition:\n";
  double value = -10'000'000;
  double x = value;
  double dx = 0.1;
  while (x < 5*dx) {
    x += dx;
    if (x >= -5*dx) {
      std::cout << x << '\n';
    }
  }

  std::cout << "\nModify algorithm to use multiplication:\n";
  int N = std::abs(value/dx);
  for (int i = 0; i < N+5; ++i) {
    x = value + i*dx;
    if (x >= -5*dx) {
      std::cout << x << '\n';
    }
  }

}
*/