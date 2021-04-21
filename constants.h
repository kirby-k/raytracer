#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <limits>
#include <cmath>

namespace Constants {
  constexpr double Pi = M_PI;
  constexpr double Infinity = std::numeric_limits<double>::infinity();
  constexpr double Epsilon = 1e-6;
}

#endif