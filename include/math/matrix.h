#ifndef __MATRIX_H
#define __MATRIX_H

#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "utils/string.h"

// Data definitions

typedef struct {
    int m;
    int n;
    float* data;
} Matrix;

// Creation, allocation, and assignment operations

Matrix* mat_new(int m, int n);

Matrix* mat_copy(Matrix* target);

void mat_assign(Matrix* source, Matrix* target);

void mat_delete(Matrix* m);

// Mathematical operations

Matrix* mat_multiply(Matrix* multiplicand, Matrix* multiplier);

// Multiply a series of matrices together sequentially in 
// the order of the arguments.
Matrix* mat_compose(int num_args, ...);

// Logging

char* mat_toString(Matrix* matrix);

#endif