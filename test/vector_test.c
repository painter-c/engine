#include "math/vector.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>

#define CLOSE(a, b) ((a) > (b) - 0.001) && ((a) < (b) + 0.001)

int main() {

    // Can add two vectors
    vec3 a = {1, 1, 1};
    vec3 b = {2, 2, 2};
    vec3 c = vec3_add(a, b);
    assert(c.x == 3 && c.y == 3 && c.z == 3);

    // Can subtract two vectors
    vec3 d = vec3_subtract(b, a);
    assert(d.x == 1 && d.y == 1 && d.z == 1);

    // Can multiply a vector by a scalar
    vec3 e = vec3_scale(a, 5);
    assert(e.x == 5 && e.y == 5 && e.z == 5);

    // Can take the dot product of two vectors
    float a_dot_b = vec3_dot(a, b);
    assert(a_dot_b == 6);

    // Can take the cross product of two vectors
    vec3 u = {2, 1, 1};
    vec3 v = {1, 1, 2};
    vec3 u_cross_v = vec3_cross(u, v);
    assert(u_cross_v.x == 1 && u_cross_v.y == -3 && u_cross_v.z == 1);

    // Can calculate the magnitude of a vector
    vec3 f = {1, 2, 3};
    float f_mag = vec3_magnitude(f);
    assert(CLOSE(f_mag, sqrt(14))); // sqrt(4 + 4 + 4)

    // Can normalize a vector
    vec3 f_norm = vec3_norm(f);
    assert(CLOSE(vec3_magnitude(f_norm), 1));

    printf("\n");
    printf("All tests passed");
}