#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} vec3;

vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_subtract(vec3 a, vec3 b);
vec3 vec3_scale(vec3 v, float c);
float vec3_dot(vec3 a, vec3 b);
vec3 vec3_cross(vec3 a, vec3 b);
float vec3_magnitude(vec3 v);
vec3 vec3_norm(vec3 v);

#endif