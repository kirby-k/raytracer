#include "random.h"
#include "vector3d.h"
#include "constants.h"
#include <random>

static std::random_device rd;
static std::mt19937 engine{rd()};

double randomDouble() {
    static std::uniform_real_distribution<double> dist(0,1);
    return dist(engine);
}

double randomDouble(double min, double max) {
    std::uniform_real_distribution<double> dist{min,max};
    return randomDouble() * (max - min) + min;
}

Vector3D randomUnitVector() {
    double theta = randomDouble(0,Constants::Pi);
    double sinTheta = std::sin(theta);
    double phi = randomDouble(0,2*Constants::Pi);
    double x = sinTheta * std::cos(phi);
    double y = sinTheta * std::sin(phi);
    double z = std::cos(theta);
    return Vector3D{x,y,z};
}

Vector3D randomHemisphere(const Vector3D& normal) {
    Vector3D vector = randomUnitVector();
    if (dot(vector,normal) > 0.0) {
        return vector;
    }
    else {
        return -vector;
    }
}