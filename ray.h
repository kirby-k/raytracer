#ifndef RAY_H
#define RAY_H

#include "point3d.h"

// p = origin + direction * t
class ray {
    public:
        ray();
        ray(Vector3D origin, Vector3D direction);
        Point3D at(double t) const;

        Vector3D origin;
        Vector3D direction;
};

std::ostream& operator<<(std::ostream& os, const ray& ray);

#endif