#include "math/vector.h"

vec3 vec3_add(vec3 a, vec3 b) {
    vec3 sum = {a.x + b.x, a.y + b.y, a.z + b.z};
    return sum;
}

vec3 vec3_subtract(vec3 a, vec3 b) {
    vec3 diff = {a.x - b.x, a.y - b.y, a.z - b.z};
    return diff;
}

vec3 vec3_scale(vec3 v, float c) {
    vec3 scaled = {v.x * c, v.y * c, v.z * c};
    return scaled;
}

float vec3_dot(vec3 a, vec3 b) {
    float dot = a.x * b.x + a.y * b.y + a.z * b.z;
    return dot;
}

vec3 vec3_cross(vec3 a, vec3 b) {
    vec3 cross = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    return cross;
}

float vec3_magnitude(vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 vec3_norm(vec3 v) {
    float mag = vec3_magnitude(v);
    vec3 norm = {v.x / mag, v.y / mag, v.z / mag};
    return norm;
}