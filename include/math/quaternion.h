#ifndef __QUATERNION_H
#define __QUATERNION_H

typedef struct {
    float r;
    float i;
    float j;
    float k;
} Quaternion;

// Allocation functions

Quaternion* quat_new(float r, float i, float j, float k);

Quaternion* quat_default();

Quaternion* quat_copy(Quaternion* target);

Quaternion* quat_from_euler(EulerAngles* eulerAngles);

Quaternion* quat_from_rotationMatrix(Matrix4f* rotationMatrix);

Quaternion* quat_from_axisAngle(AxisAngle* axisAngle);

void quat_delete(Quaternion* quaternion);

// Conversion Functions

EulerAngles* quat_to_euler(Quaternion* quaternion);

Matrix4f* quat_to_rotationMatrix(Quaternion* quaternion);

AxisAngle* quat_to_axisAngle(Quaternion* quaternion);

// Mathematical Operations

float quat_magnitude(Quaternion* quaternion);

void quat_normalize(Quaternion* quaternion);

void quat_multiply(Quaternion* multiplicand, Quaternion* multiplier);

#endif