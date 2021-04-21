#ifndef COLOR_H
#define COLOR_H

#include "vector3d.h"
#include <vector>

using Color = Vector3D;

const Color black = {0, 0, 0};
const Color almostBlack = {.1,.1,.1};
const Color white = {1, 1, 1};

const Color gray = {0.5, 0.5,0.5};
const Color lightgray = {0.8, 0.8, 0.8};

const Color red = {1, 0, 0};
const Color orange = {1.0, 0.5, 0.0};
const Color green = {0, 1, 0};
const Color pink = {1, 0, .8};
const Color blue = {0,0,1};
const Color yellow = {1, 1, 0};
const Color purple = {.5, 0, .5};

const Color sun = {1, .6, 0};
const Color lightBlue = {.5, .8, 1};
const Color teal = {0,1,1};

// Add 10+ new colors that you think will be useful for generating
// beautiful scenes, e.g. primary colors, secondary colors, extras
// (fuschia?, sky blue?, sun?, molten metal/fire/magma?, etc)

#endif