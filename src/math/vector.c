#include "math/vector.h"

/* VEC3 DEFINITIONS */

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
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 vec3_norm(vec3 v) {
    float mag = vec3_magnitude(v);
    vec3 norm = {v.x / mag, v.y / mag, v.z / mag};
    return norm;
}

vec3 vec3_from_vec4(vec4 v) {
    return (vec3){v.x, v.y, v.z};
}

/* VEC4 DEFINITIONS */

vec4 vec4_add(vec4 a, vec4 b) {
    return (vec4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

vec4 vec4_subtract(vec4 a, vec4 b) {
    return (vec4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

vec4 vec4_scale(vec4 v, float s) {
    return (vec4){v.x * s, v.y * s, v.z * s, v.w * s};
}

float vec4_dot(vec4 a, vec4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

vec4 vec4_from_vec3(vec3 v, float w) {
    return (vec4){v.x, v.y, v.z, w};
}

float vec4_magnitude(vec4 v) {
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}

vec4 vec4_norm(vec4 v) {
    float mag = vec4_magnitude(v);
    return (vec4) {v.x / mag, v.y / mag, v.z / mag, v.w / mag};
}