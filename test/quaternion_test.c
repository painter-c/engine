#include "math/quaternion.h"
#include "math/vector.h"
#include <stdio.h>
#include <assert.h>

#define CLOSE(a, b) (a) > ((b) - 0.01) && (a) < ((b) + 0.01)

int main() {

    // Should be able to convert a 3d point to a quaternion with 
    // the real component equal to zero.
    vec3 p = {1,2,3};
    Quaternion q1 = quat_from_point(p);
    assert(q1.n == 0 && q1.v.x == 1 && q1.v.y == 2 && q1.v.z == 3);

    // Should be able to conjugate a quaternion
    // (a + bi + cj + dk) => (a - bi - cj - dk)
    Quaternion q1_conj = quat_conjugate(q1);
    assert(q1_conj.v.x == -1 && q1_conj.v.y == -2 && q1_conj.v.z == -3);

    // Should be able to convert an axis angle representation to a 
    // quaternion
    vec3 axis = {1, 0, 1};
    float angle = 1;
    Quaternion q2 = quat_from_axisangle(axis, angle);
    assert(CLOSE(q2.n, 0.877) && CLOSE(q2.v.x, 0.339) && CLOSE(q2.v.y, 0)
        && CLOSE(q2.v.z, 0.339));

    printf("All tests passed");
}