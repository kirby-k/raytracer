#pragma once
#include "texture.h"
#include <cmath>
#include <memory>
#include "random.h"

class material {
    public:
        material(std::string name, std::shared_ptr<texture> texture, bool emitting);
        material(std::string name, std::shared_ptr<texture> texture, bool emitting, double fuzz);
        virtual ray scatter(const ray& r, const hit& h) const = 0;
        void print();
        std::string name;
        std::shared_ptr<texture> m_texture;
        bool isEmitting;
        double fuzz{-1};
};

Vector3D reflect(const Vector3D& direction, const Vector3D& normal);
Vector3D refract(const Vector3D& direction, const Vector3D& normal, double index_ratio);
double schlick(double cos_theta, double index_ratio);
