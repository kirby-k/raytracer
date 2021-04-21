#pragma once

#include "vector3d.h"
#include "point3d.h"
#include <memory>

class material;

class hit {
    public:
    hit(double time, Point3D point, Vector3D normal, std::shared_ptr<material> m);

    double time;
    Point3D point;
    Vector3D normal;
    std::shared_ptr<material> m;
};

std::ostream& operator<<(std::ostream& os, const hit& hit);