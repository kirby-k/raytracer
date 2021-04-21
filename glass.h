#pragma once

#include "materials.h"

class glass : public material {
    public:
        glass(std::shared_ptr<texture> texture, bool emitting);
        ray scatter(const ray& r, const hit& h) const override; //override yells if we implement the wrong function
};