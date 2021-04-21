#include "pixels.h"
#include "lodepng.h"
#include <fstream>
#include <cmath>

Pixels::Pixels() :width{0}, height{0}, values(0){

}
Pixels::Pixels(unsigned width, unsigned height)
  :width{width}, height{height}, values(width*height) {}

void Pixels::set(unsigned w, unsigned h) {
  width = w;
  height = h;
  std::vector<Color> v(w*h);
  values = v;
}

const Color& Pixels::operator()(unsigned i, unsigned j) const {
  return values[i*width + j];
}
Color& Pixels::operator()(unsigned i, unsigned j) {
  return values[i*width + j]; 
}

void Pixels::print() {
  std::cout << "Pixels(Height = " << height << " Width = " << width;
}

void Pixels::save_ppm(const std::string& filename) {
    std::ofstream output(filename);
    if (!output) {
      throw std::runtime_error("Cannot open output file: " + filename);
    }
    output << "P3\n1920 1080\n255\n";
  for (int i = 0; i < values.size(); i++) {
      unsigned int r = to_color<unsigned>(values[i].x);
      unsigned int g = to_color<unsigned>(values[i].y);
      unsigned int b = to_color<unsigned>(values[i].z);  
      output << r << " " << g << " " << b << std::endl;
  }

}

void Pixels::save_png(const std::string& filename) {
  std::ofstream output(filename);
  if (!output) {
    throw std::runtime_error("Cannot open output file: " + filename);
  }
  std::vector<unsigned char> data;
  for (auto c: values) {
    data.push_back(to_color<unsigned char>(c.x));
    data.push_back(to_color<unsigned char>(c.y));
    data.push_back(to_color<unsigned char>(c.z));
    data.push_back(255);
  }
  unsigned error = lodepng::encode(filename, data, width, height);
  if (error) {
    throw std::runtime_error(lodepng_error_text(error));
  }
  
  // lodepng expects pixels to be in a vector of unsigned char, where
  // the elements are R, G, B, alpha, R, G, B, alpha, etc.  Use
  // to_color<unsigned char>(color.x) for putting colors in this
  // vector, and lodepng::encode(filename, vector, width, height)
  // (make sure you check the error code returned by this function
  // using lodepng_error_text(unsigned error)).
}

double gamma_correction(double value) {
  // double gamma = 2.2;
  double gamma = 1.0;
  return std::pow(value, 1/gamma);
}
