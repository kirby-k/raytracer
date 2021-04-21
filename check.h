#pragma once
#include "texture.h"
class check : public texture {
    public:
        check(std::string name, Color color);
        Color uv(double u, double v) const override;
        
};