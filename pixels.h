#ifndef PIXELS_H
#define PIXELS_H

#include "color.h"
#include <string>
#include <vector>
#include <ostream>
#include <algorithm>
#include <cmath>

class Pixels {
public:
  Pixels();
  Pixels(unsigned width, unsigned height);
  void set(unsigned width, unsigned height);
  const Color& operator()(unsigned i, unsigned j) const; // get pixel value
  Color& operator()(unsigned i, unsigned j); // set pixel value
  void print();  
  void save_ppm(const std::string& filename);
  void save_png(const std::string& filename);
  
  unsigned width, height;
  std::vector<Color> values;
  double dx, dz;
  
};

double gamma_correction(double value);

template <class T>
T to_color(double value) {
  double clamped = std::clamp(value, 0.0, 0.999); // clamp value in range [0, 1)
  clamped = gamma_correction(clamped);
  return static_cast<T>(256*clamped); // scale to 8-bit color value
}

#endif