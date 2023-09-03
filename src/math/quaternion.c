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

Quaternion quat_multiply(Quaternion left, Quaternion right) {
    return (Quaternion) {
        left.n * right.n - vec3_dot(left.v, right.v),
        vec3_add(
            vec3_scale(right.v, left.n),
            vec3_add(
                vec3_scale(left.v, right.n),
                vec3_cross(left.v, right.v)
            )
        )
    };
}

vec3 quat_rotate_point(Quaternion q, vec3 p) {
    Quaternion result = quat_multiply(
        quat_multiply(
            q, quat_from_point(p)
        ),
        quat_conjugate(q)
    );
    return result.v;
}

float quat_inner_product(Quaternion left, Quaternion right) {
    return
        left.n * right.n +
        left.v.x * right.v.x + 
        left.v.y * right.v.y + 
        left.v.z * right.v.z;
}

float quat_magnitude(Quaternion q) {
    return sqrt(quat_inner_product(q, q));
}

Quaternion quat_normalize(Quaternion q) {
    float mag = quat_magnitude(q);
    return (Quaternion) {
        q.n / mag, {
            q.v.x / mag,
            q.v.y / mag,
            q.v.z / mag
        }
    };
}

Quaternion quat_inverse(Quaternion q) {
    return quat_conjugate(quat_normalize(q));
}

Quaternion quat_diff(Quaternion left, Quaternion right) {
    return quat_multiply(left, quat_inverse(right));
}

Quaternion quat_slerp(Quaternion from, Quaternion to, float t) {
    Quaternion diff = quat_diff(to, from);
    return quat_from_axisangle(
        diff.v,
        acos(diff.n)*2*t
    );
}