#pragma once

#include "object.h"
#include "point3d.h"
#include "ray.h"
#include "constants.h"
#include "hit.h"
#include <cmath>

class material;

class sphere : public object {
    public:
        sphere(Point3D center, double radius, std::shared_ptr<material> m);
        hit construct_hit(const ray& ray, double time) override;
        std::pair<double,double> uv(const hit& hit) const;
        bool intersect(const ray& ray, double& time) const override;
        double where(const ray& ray) const;
        void print() const override;
        
        Point3D center;
        double radius;
};
