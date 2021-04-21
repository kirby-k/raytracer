#pragma once

#include <vector>
#include <memory>
#include "point3d.h"
#include "color.h"

class ray;
class object;
class material;
using Nearest = std::pair<double,std::shared_ptr<object>>;

class world {
    public:
        world();
        void addSphere(Point3D center, double radius, std::shared_ptr<material> m);
        void addTriangle(Point3D v1, Point3D v2, Point3D v3, std::shared_ptr<material> m);
        Nearest nearest(const ray& ray) const;
        std::vector<std::shared_ptr<object>> objects;
};