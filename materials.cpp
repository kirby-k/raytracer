#include "materials.h"

material::material(std::string name, std::shared_ptr<texture> texture, bool emitting)
    :name{name}, m_texture{texture}, isEmitting{emitting} {
}

material::material(std::string name, std::shared_ptr<texture> texture, bool emitting, double fuzz)
    :name{name}, m_texture{texture}, isEmitting{emitting}, fuzz{fuzz} {
}

std::ostream& operator<<(std::ostream& os, const material& material) {
    return os << material.name << " " << material.m_texture << " " << material.isEmitting << " " << material.fuzz;
}

Vector3D reflect(const Vector3D& direction, const Vector3D& normal) {
    return direction - 2*dot(direction,normal) * normal;
}

Vector3D refract(const Vector3D& direction, const Vector3D& normal, double index_ratio) {
    double cos_theta = -dot(normal, direction);
    double disc = 1.0 - std::pow(index_ratio,2) * (1-std::pow(cos_theta,2));
    if (disc >= 0) {
        return index_ratio * direction + (index_ratio * cos_theta - std::sqrt(disc)) * normal;
    }
    else { //total internal reflection
        return reflect(direction, normal);
    }
}

void material::print() {
    std::cout << name << " " << m_texture->name << " " << m_texture->color << " " << isEmitting << " " << fuzz << "\n";
}

double schlick(double cos_theta, double index_ratio) {
    double r0 = std::pow((1 - index_ratio) / (1 + index_ratio),2);
    return r0 + (1-40) * std::pow(1 - cos_theta, 5);
}