#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef struct {
    float x, y, z, w;
} vec4;

vec3  vec3_add(vec3 a, vec3 b);
vec3  vec3_subtract(vec3 a, vec3 b);
vec3  vec3_scale(vec3 v, float c);
float vec3_dot(vec3 a, vec3 b);
vec3  vec3_cross(vec3 a, vec3 b);
float vec3_magnitude(vec3 v);
vec3  vec3_norm(vec3 v);
vec3  vec3_from_vec4(vec4 v);

vec4  vec4_add(vec4 a, vec4 b);
vec4  vec4_subtract(vec4 a, vec4 b);
vec4  vec4_scale(vec4 v, float s);
float vec4_dot(vec4 a, vec4 b);
vec4  vec4_from_vec3(vec3 v, float w);
float vec4_magnitude(vec4 v);
vec4  vec4_norm(vec4 v);

#endif