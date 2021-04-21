#pragma once
#include "point3d.h"
#include "ray.h"
#include <cmath>

class aabb {
    public:
        aabb(const Point3D& mini,const Point3D& maxi)
        :mini{mini},maxi{maxi} {}

        bool hit(const ray& ray, double t_min, double t_max) const {
            for (int i = 0; i < 3; i++) {
                double t0 = fmin(mini(i) - ray.origin(i) / ray.direction(i), maxi(i) - ray.origin(i) / ray.direction(i));
                double t1 = fmax(mini(i) - ray.origin(i) / ray.direction(i), maxi(i) - ray.origin(i) / ray.direction(i));
                t_min = fmax(t0, t_min);
                t_max = fmin(t1, t_max);
                if (t_max <= t_min) {
                    return false;
                }
            }
            return true;
        }

        Point3D mini, maxi;

};