#pragma once

#include "materials.h"

class unreal : public material {
    public:
        unreal(std::shared_ptr<texture> texture, bool emitting);
        ray scatter(const ray& r, const hit& h) const override;
};