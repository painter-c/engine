#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// The purpose of this program is to measure the performance
// difference of vector operation that use pass by value versus 
// pass by reference.

typedef struct {
    float x;
    float y;
    float z;
} vec3;

float dot_product_val(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 scale_val(vec3 v, float c) {
    vec3 result = {v.x * c, v.y * c, v.z * c};
    return result;
}

float dot_product_ref(vec3* a, vec3* b) {
    return a->x * b->x + a->y * b->y + a->z + b->z;
}

vec3 scale_ref(vec3* v, float c) {
    v->x *= c;
    v->y *= c;
    v->z *= c;
}

float ms_dur(clock_t start, clock_t end) {
    return (float)(end - start) / CLOCKS_PER_SEC * 1000;
}

int random(int low, int high) {
    return rand() % (high - low) + low;
}

int main() {

    clock_t start;
    clock_t end;

    float scalar_result;
    vec3 vector_result;
    
    int iters = 10000000;

    start = clock();
    for (int i = 0; i < iters; i++) {
        vec3 v1 = {random(0,100), random(0,100), random(0,100)};
        vec3 v2 = {random(0,100), random(0,100), random(0,100)};
        scalar_result = dot_product_val(v1, v2);
    }
    end = clock();
    printf("dot product pass by val: %d ops in %.3f ms\n", iters, ms_dur(start, end));

    start = clock();
    for (int i = 0; i < iters; i++) {
        vec3 v1 = {random(0,100), random(0,100), random(0,100)};
        vec3 v2 = {random(0,100), random(0,100), random(0,100)};
        scalar_result = dot_product_ref(&v1, &v2);
    }
    end = clock();
    printf("dot product pass by ref: %d ops in %.3f ms\n", iters, ms_dur(start, end));

    start = clock();
    for (int i = 0; i < iters; i++) {
        vec3 v = {random(0,100), random(0,100), random(0,100)};
        int c = random(2,10);
        v = scale_val(v, c);
    }
    end = clock();
    printf("vector scale pass by val: %d ops in %.3f ms\n", iters, ms_dur(start, end));

    start = clock();
    for (int i = 0; i < iters; i++) {
        vec3 v = {random(0,100), random(0,100), random(0,100)};
        int c = random(2,10);
        scale_ref(&v, c);
    }
    end = clock();
    printf("vector scale pass by ref: %d ops in %.3f ms\n", iters, ms_dur(start, end));

    printf("%f", scalar_result);
    printf("%f", vector_result.x);
}