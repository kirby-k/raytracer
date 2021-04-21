#pragma once
#include "texture.h"

class solid : public texture {
    public:
        solid(std::string name, Color color);
        Color uv(double u, double v) const override;
};