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

    // Should be able to multiply two quaternions
    Quaternion left = {1, {1, 0, 0}};
    Quaternion right = {1, {0, 1, 0}};
    Quaternion prod = quat_multiply(left, right);
    // Multiplication of these two quaternions should be the quaternion (1,1,1,1)
    assert(prod.n == 1 && prod.v.x == 1 && prod.v.y == 1 && prod.v.z == 1);

    // should be able to rotate a point using a quaternion
    Quaternion rot_x_270 = quat_from_axisangle((vec3){1, 0, 0}, 3*M_PI_2);
    vec3 point = {1,1,1};
    vec3 rot_point = quat_rotate_point(rot_x_270, point);
    // Rotation of (1,1,1) around the x axis BY 270 should result in the point (1, 1, -1)
    assert(CLOSE(rot_point.x, 1) && CLOSE(rot_point.y, 1) && 
        CLOSE(rot_point.z, -1));

    // test rotation of point (1,0,0) 90 degrees around the z axis
    Quaternion rot_z_90 = quat_from_axisangle((vec3){0, 0, 1}, M_PI_2);
    vec3 point2 = {1,0,0};
    vec3 rot_point2 = quat_rotate_point(rot_z_90, point2);
    // should result in the point (0, 1, 0);
    assert(CLOSE(rot_point2.x, 0) && CLOSE(rot_point2.y, 1)
        && CLOSE(rot_point2.z, 0));

    printf("All tests passed");
}