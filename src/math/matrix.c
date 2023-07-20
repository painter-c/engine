#include "math/matrix.h"

// Implementation of generic m x n matrices. Internally, matrices 
// are stored column-wise in a block of contiguous memory.
//
// For example, consider a 2 x 2 matrix M with column vectors a and
// b. The memory layout of Matrix M would be as follows:
//
// M: a0 a1 b0 b1

Matrix* mat_new(int m, int n) {
    Matrix* new = malloc(sizeof(Matrix));
    
    new->m = m;
    new->n = n;
    new->data = malloc(sizeof(float) * m * n);
    
    for (int i = 0; i < m * n; i++) {
        new->data[i] = 0;
    }

    return new;
}

void mat_delete(Matrix* matrix) {
    free(matrix->data);
    free(matrix);
}

void mat_assign(Matrix* source, Matrix* target) {
    assert(source->m == target->m && source->n == target->n);

    for (int i = 0; i < source->m * source->n; i++) {
        target->data[i] = source->data[i];
    }
}

Matrix* mat_copy(Matrix* target) {
    Matrix* copy = malloc(sizeof(target));
    
    copy->m = target->m;
    copy->n = target->n;
    copy->data = malloc(sizeof(float) * copy->m * copy->n);

    for (int i = 0; i < copy->m * copy->n; i++) {
        copy->data[i] = target->data[i];
    }

    return copy;
}

// Given the column-wise representation of matrices in this 
// implementation, the indices of rows and columns will can be 
// obtained using the following strategies:
//
// Each row of a matrix M will have a stride equal to the column 
// size of M.
//
// Row formula: [row index] + [column size] * [row item index]
//
// Each column in matrix M will be packed in a block of contiguous 
// memory offset a multiple of the column size.
//
// Column formula: [column index] * [column size] + [column item index]
//
// The row in ij format of the product matrix will be the row of A.
// The column in ij format of the product matrix will be the column 
// of B. The dot product of row i of A and column j of B will be 
// put into element (i,j) of the product matrix.
//
// (i,j) must be converted to an array index using the formula 
// j * [column size] + i.

Matrix* mat_multiply(Matrix* A, Matrix* B) {
    assert(A->n == B->m);

    Matrix* C = malloc(sizeof(Matrix));

    C->m = A->m;
    C->n = B->n;
    C->data = malloc(sizeof(float) * C->m * C->n);

    for (int row_A = 0; row_A < A->m; row_A++) {
        for (int col_B = 0; col_B < B->n; col_B++) {
            float sum = 0;
            for (int i = 0; i < A->n; i++) {
                int entry_A = row_A + A->n * i;
                int entry_B = col_B * B->m + i;
                sum += A->data[entry_A] * B->data[entry_B];
            }
            // Convert from (row, col) to array index
            int entry_C = col_B * C->m + row_A;
            C->data[entry_C] = sum;
        }
    }
    return C;
}

Matrix* mat_compose(int num_args, ...) {
    assert(num_args > 0);

    va_list args;
    va_start(args, num_args);

    Matrix* left_mat = va_arg(args, Matrix*);
    // Must copy or matrix ptr in argument will be freed. Only 
    // first value for left_mat contains pointer from function 
    // arguments, subsequent deletes free temporary product 
    // matrix allocations.
    left_mat = mat_copy(left_mat);

    for (int i = 1; i < num_args; i++) {
        Matrix* current = va_arg(args, Matrix*);
        assert(left_mat->n == current->m);

        Matrix* product = mat_multiply(left_mat, current);

        mat_delete(left_mat);
        left_mat = product;
    }
    return left_mat;
}

char* mat_toString(Matrix* matrix) {
    char* result = su_heapify("");
    char buff[16];

    for (int row = 0; row < matrix->m; row++) {
        for (int col = 0; col < matrix->n; col++) {
            int index = col * matrix->m + row;
            sprintf(buff, "%.2f", matrix->data[index]);
            result = su_append(result, buff);
            if (col < matrix->n - 1)
                result = su_append(result, " ");
        }
        result = su_append(result, "\n");
    }
    return result;
}