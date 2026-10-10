#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define FIXED_ARRAY_SIZE 20

int main(int argc, char *argv[]) {
    int a, b;
    status_code status = parse_args(argc, argv, &a, &b);
    if (status != STATUS_OK) {
        fprintf(stderr, "Error: Invalid arguments\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    int fixed_array[FIXED_ARRAY_SIZE];
    status = fill_random_array_fixed(fixed_array, FIXED_ARRAY_SIZE, a, b);
    if (status != STATUS_OK) {
        fprintf(stderr, "Error filling array\n");
        return 1;
    }

    printf("Fixed array:\n");
    for (size_t i = 0; i < FIXED_ARRAY_SIZE; ++i) {
        printf("%d ", fixed_array[i]);
    }
    printf("\n");

    status = swap_min_max(fixed_array, FIXED_ARRAY_SIZE);
    if (status != STATUS_OK) {
        fprintf(stderr, "Error swapping\n");
        return 1;
    }

    printf("Fixed array after swap:\n");
    for (size_t i = 0; i < FIXED_ARRAY_SIZE; ++i) {
        printf("%d ", fixed_array[i]);
    }
    printf("\n");

    int *A = NULL;
    int *B = NULL;
    int *C = NULL;
    size_t size_A = 0;
    size_t size_B = 0;
    size_t size_C = 0;

    status = fill_random_array_dynamic(&A, &size_A, 10, 10000, -1000, 1000);
    if (status != STATUS_OK) {
        fprintf(stderr, "Error memory allocation\n");
        return 1;
    }

    status = fill_random_array_dynamic(&B, &size_B, 10, 10000, -1000, 1000);
    if (status != STATUS_OK) {
        fprintf(stderr, "Error memory allocation\n");
        free(A);
        return 1;
    }

    status = build_array_c(A, size_A, B, size_B, &C, &size_C);
    if (status != STATUS_OK) {
        fprintf(stderr, "Error building array C\n");
        free(A);
        free(B);
        return 1;
    }

    printf("Array A size: %zu\n", size_A);
    printf("Array B size: %zu\n", size_B);
    printf("Array C size: %zu\n", size_C);

    free(A);
    free(B);
    free(C);

    return 0;
}
