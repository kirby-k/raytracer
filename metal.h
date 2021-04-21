#pragma once

#include "materials.h"

class metal : public material {
    public:
        metal(std::shared_ptr<texture> texture, bool emitting, double fuzz);
        ray scatter(const ray& r, const hit& h) const override;

};

Vector3D metalScatter(Point3D, double);