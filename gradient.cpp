#include "gradient.h"

gradient::gradient(std::string name, Color color) 
:texture{name,color} {}

Color gradient::uv(double u, double v) const {
    double r{u}, g{v}, b{u+v};
    if (u >= 0 && u < 0.33) {
        r = u/0.33;
        g = 0;
        b = 1.0-u/.333;
    }
    return Color{r,g,b};
    //return Color{u,v,u};
}