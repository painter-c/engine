#ifndef __QUATERNION_H
#define __QUATERNION_H

#include "math/vector.h"
#include <math.h>

typedef struct {
    float n;
    vec3 v;
} Quaternion;

Quaternion quat_from_point(vec3 p);
Quaternion quat_from_axisangle(vec3 axis, float angle);
Quaternion quat_conjugate(Quaternion q);

#endif