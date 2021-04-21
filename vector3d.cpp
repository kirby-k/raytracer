#include "vector3d.h"
#include "constants.h"
#include <cmath>
#include <iostream>
#include <exception>
#include <complex>

Vector3D::Vector3D()
    :x{0.0}, y{0.0}, z{0.0} {}

Vector3D::Vector3D(double x, double y, double z)
    :x{x}, y{y}, z{z} {}

Vector3D& Vector3D::operator+=(const Vector3D& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vector3D& Vector3D::operator*=(const Vector3D& rhs) {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

Vector3D& Vector3D::operator*=(const double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3D& Vector3D::operator/=(const double scalar) {
    if (scalar == 0) {
        throw std::overflow_error("divide by zero");
    }
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

double Vector3D::operator()(int i) const {
    switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::runtime_error("Index out of bounds: " + std::to_string(i));
    }
    return -1;
}   

double& Vector3D::operator()(int i) {
    switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::runtime_error("Index out of bounds: " + std::to_string(i));
    }
    x*=-1;
    return x;
}

bool almost_equal(double x, double y) {
  return std::abs(x - y) < Constants::Epsilon;
}

bool operator==(const Vector3D& lhs, const Vector3D& rhs) {
  return almost_equal(lhs.x, rhs.x) && almost_equal(lhs.y, rhs.y) && almost_equal(lhs.z, rhs.z);
}

bool operator!=(const Vector3D& lhs, const Vector3D& rhs) {
  return !(lhs == rhs);
}

Vector3D operator+(Vector3D lhs, const Vector3D& rhs) {
    lhs += rhs;
    return lhs;
}

Vector3D operator-(Vector3D lhs, const Vector3D& rhs) {
    lhs -= rhs;
    return lhs;
}

Vector3D operator-(const Vector3D& rhs)  { // negation
    return -1*rhs;
}

Vector3D operator*(Vector3D lhs, const Vector3D& rhs) {
    lhs *= rhs;
    return lhs;
}

Vector3D operator*(Vector3D lhs, const double scalar) {
    lhs *= scalar;
    return lhs;
}

Vector3D operator*(const double scalar, Vector3D rhs) {
    rhs *= scalar;
    return rhs;
}

Vector3D operator/(Vector3D lhs, const double scalar) {
    lhs /= scalar;
    return lhs;
}

Vector3D pow(Vector3D v, const double n) {
    v.x = pow(v.x, n);
    v.y = pow(v.y, n);
    v.z = pow(v.z, n);
    return v;
}

double dot(const Vector3D& a, const Vector3D& b) {
    Vector3D tmp = a*b;
    double ret = tmp.x + tmp.y + tmp.z;
    return ret;
}

Vector3D cross(const Vector3D& a, const Vector3D& b) {
    Vector3D cproduct;
    cproduct.x = (a.y * b.z) - (a.z * b.y);
    cproduct.y = (a.z*b.x) - (a.x*b.z);
    cproduct.z = (a.x * b.y) - (a.y * b.x);
    return cproduct;
}

double norm(const Vector3D& v) {
    return std::sqrt(dot(v,v));
}

Vector3D unit(const Vector3D& v) {
    return v/norm(v);
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
    os << "(" << v.x << " " << v.y << " " << v.z << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Vector3D& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}