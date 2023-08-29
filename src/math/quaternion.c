#include "math/quaternion.h"
#include <stdio.h>

Quaternion quat_from_point(vec3 p) {
    return (Quaternion) {0, p};
}

Quaternion quat_conjugate(Quaternion q) {
    return (Quaternion) {q.n, -1 * q.v.x, -1 * q.v.y, -1 * q.v.z};
}

Quaternion quat_from_axisangle(vec3 axis, float angle) {
    float half_angle = angle / 2;
    return (Quaternion) {
        cos(half_angle),
        vec3_scale(vec3_norm(axis), sin(half_angle))
    };
}