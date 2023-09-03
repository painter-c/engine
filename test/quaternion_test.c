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

    // Should be able to obtain the magnitude of a quaternion
    Quaternion q3 = {4, {4, 4, 4}};
    // The magnitude should be sqrt(16+16+16+16) = sqrt(64) = 8
    assert(CLOSE(quat_magnitude(q3), 8));

    // Should be able to take the inner product of two quaternions (dot product)
    // q3 dot itself should be 4^2 + 4^2 + 4^2 + 4^2 = 64
    assert(CLOSE(quat_inner_product(q3, q3), 64));

    // Should be able to normalize a quaternion
    // norm(q3) = norm((4,4,4,4)) = (.5,.5,.5,.5)
    Quaternion q3_norm = quat_normalize(q3);
    assert(CLOSE(q3_norm.n, .5) && CLOSE(q3_norm.v.x, .5) && CLOSE(q3_norm.v.y, .5)
        && CLOSE(q3_norm.v.z, .5));

    // Should be able to calculate a quaternion inverse
    // inv(q3) = conj(norm(q3)) = conj(.5,.5,.5,.5) = (.5,-.5,-.5,-.5)
    Quaternion q3_inv = quat_inverse(q3);
    assert(CLOSE(q3_inv.n, .5) && CLOSE(q3_inv.v.x, -.5) && CLOSE(q3_inv.v.y, -.5)
        && CLOSE(q3_inv.v.z, -.5));

    // Should be able to take the difference of two quaternions
    // The difference between two quaternions produces a new quaternion that 
    // describes how to rotate one quaternion to another. A quaternion is like a 
    // displacement vector, except instead of walking some amount of units in 
    // euclidean space, it traces some distance along the 4d complex hypersphere.
    // 
    // The equation of the quaternions difference is A-B = AB* where A is the 
    // the starting quaternion and B* is the inverse of the destination 
    // quaternion.
    //
    // Given two quaternions qa and qb:
    // Where qa_axis = {1,0,0} and qa_angle = pi/2
    // And qb_axis = {1,0,0} and qa_angle = 3*pi/2
    // Then the quaternion difference qc = qa - qb should be
    // qc_axis = {1,0,0}, and qa_angle = pi since both rotations 
    // are in the same x axis and the angle between them is pi radians.
    //
    // In quaternion form this would be {cos(pi/4), sin(pi/4){1,0,0}}

    Quaternion qa = quat_from_axisangle((vec3){1,0,0}, M_PI_2);
    Quaternion qb = quat_from_axisangle((vec3){1,0,0}, M_PI);
    Quaternion qc = quat_diff(qb, qa);
    assert(CLOSE(qc.n, cos(M_PI_2/2))
        && CLOSE(qc.v.x, sin(M_PI_2/2))
        && CLOSE(qc.v.y, 0)
        && CLOSE(qc.v.z, 0)
    );

    // Should be able to exponentiate a quaternion
    // Should have half the angle of qc
    Quaternion qc_exp = quat_exp(qc, 0.5);
    assert(CLOSE(qc_exp.n, cos(M_PI_2/4))
        && CLOSE(qc_exp.v.x, sin(M_PI_2/4))
        && CLOSE(qc_exp.v.y, 0)
        && CLOSE(qc_exp.v.z, 0)
    );

    // Should be able to interpolate between two different quaternions
    // Should use SLERP (spherical linear interpolation)
    // 
    // Interpolating between qa and qb with a factor of .5 should result in 
    // a quaternion similar to the difference but with half the angle:
    // qc_slerp = {cos(pi/8), sin(pi/8){1,0,0}}
    
    Quaternion qc_slerp = quat_slerp(qa, qb, 0.5);
    assert(CLOSE(qc_slerp.n, cos(M_PI_2/4))
        && CLOSE(qc_slerp.v.x, sin(M_PI_2/4))
        && CLOSE(qc_slerp.v.y, 0)
        && CLOSE(qc_slerp.v.z, 0)
    );

    printf("All tests passed");
}