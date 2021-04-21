#pragma once

class hit;
class ray;

#include <memory>
#include "materials.h"
#include "color.h"

class object {
    public:
        object();
        virtual hit construct_hit(const ray& ray, double time) = 0;
        virtual bool intersect(const ray& ray, double& time) const = 0;
        virtual std::pair<double,double> uv(const hit& hit) const = 0;
        virtual void print() const = 0;
        std::shared_ptr<material> m;
};