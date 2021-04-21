#pragma once

#include "materials.h"

class diffuse : public material {
    public:
        diffuse(std::shared_ptr<texture> texture, bool emitting);
        ray scatter(const ray& r, const hit& h) const override;
};

