#include "math/matrix.h"

#include <assert.h>
#include <stdio.h>

int main() {

    // Can allocate new matrix with 2 rows and 3 columns
    Matrix* m1 = mat_new(2, 3);

    assert(m1->m == 2);
    assert(m1->n == 3);
    assert(m1->data[5] == 0);

    // Can copy a matrix
    Matrix* m2 = mat_copy(m1);

    assert(m2 != m1);
    assert(m2->m == m1->m);
    assert(m2->n == m1->n);
    for (int i = 0; i < m1->m * m1->n; i++) {
        assert(m2->data[i] == m1->data[i]);
    }

    // Can multiply two matrices
    Matrix* m3 = mat_new(2, 2);
    m3->data[0] = 1; m3->data[1] = 2;
    m3->data[2] = 1; m3->data[3] = 2;

    Matrix* m4 = mat_new(2, 2);
    m4->data[0] = 2; m4->data[1] = 1;
    m4->data[2] = 2; m4->data[3] = 1;

    Matrix* m3m4 = mat_multiply(m3, m4);
    assert(m3m4->m == 2);
    assert(m3m4->n == 2);
    assert(m3m4->data[0] == 3);
    assert(m3m4->data[1] == 6);
    assert(m3m4->data[2] == 3);
    assert(m3m4->data[3] == 6);

    // Can multiply two matrices of different size
    Matrix* m5 = mat_new(2, 3);
    m5->data[0] = 1; m5->data[1] = 1;
    m5->data[2] = 1; m5->data[3] = 1;
    m5->data[4] = 1; m5->data[5] = 1;

    Matrix* m3m5 = mat_multiply(m3, m5);

    assert(m3m5->m == 2);
    assert(m3m5->n == 3);
    assert(m3m5->data[0] == 2);
    assert(m3m5->data[1] == 4);
    assert(m3m5->data[2] == 2);
    assert(m3m5->data[3] == 4);
    assert(m3m5->data[4] == 2);
    assert(m3m5->data[5] == 4);

    // Works with larger matrix in first argument

    Matrix* m6 = mat_new(3, 2);
    m6->data[0] = 1; m6->data[1] = 1; m6->data[2] = 1; // col 1
    m6->data[3] = 1; m6->data[4] = 1; m6->data[5] = 1; // col 2
    // row 1            row 2              row 3

    Matrix* m6m3 = mat_multiply(m6, m3);

    assert(m6m3->m == 3);
    assert(m6m3->n == 2);
    assert(m6m3->data[0] == 3);
    assert(m6m3->data[1] == 3);
    assert(m6m3->data[2] == 3);
    assert(m6m3->data[3] == 3);
    assert(m6m3->data[4] == 3);
    assert(m6m3->data[5] == 3);

    // Can assign one matrix to another of equal size
    Matrix* m7 = mat_new(2, 2);
    m7->data[0] = 1; m7->data[1] = 1;
    m7->data[2] = 1; m7->data[3] = 1;

    Matrix* m8 = mat_new(2, 2);
    m8->data[0] = 0; m8->data[1] = 0;
    m8->data[2] = 0; m8->data[3] = 0;

    mat_assign(m7, m8);

    assert(m8->data[0] == 1);
    assert(m8->data[1] == 1);
    assert(m8->data[2] == 1);
    assert(m8->data[3] == 1);

    // Can compose multiple matrices using a single function call
    Matrix* m3m4m5 = mat_compose(3, m3, m4, m5);

    assert(m3m4m5->m == 2);
    assert(m3m4m5->n == 3);
    assert(m3m4m5->data[0] == 6);
    assert(m3m4m5->data[1] == 12);
    assert(m3m4m5->data[2] == 6);
    assert(m3m4m5->data[3] == 12);
    assert(m3m4m5->data[4] == 6);
    assert(m3m4m5->data[5] == 12);

    // Can display a matrix visually as a string

    char* str_m3m4m5 = mat_toString(m3m4m5);

    printf("%s", str_m3m4m5);

    printf("\n");
    printf("All tests passed");
}