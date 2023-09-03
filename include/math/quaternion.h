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
Quaternion quat_inverse(Quaternion q);
Quaternion quat_multiply(Quaternion left, Quaternion right);
vec3 quat_rotate_point(Quaternion q, vec3 p);
float quat_inner_product(Quaternion left, Quaternion right);
float quat_magnitude(Quaternion q);
Quaternion quat_normalize(Quaternion q);
Quaternion quat_diff(Quaternion left, Quaternion right);
Quaternion quat_exp(Quaternion q, float t);
Quaternion quat_slerp(Quaternion from, Quaternion to, float t);

#endif