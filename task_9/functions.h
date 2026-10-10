#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>

typedef enum {
    STATUS_OK = 0,
    STATUS_ERROR_NULL_POINTER,
    STATUS_ERROR_INVALID_ARGS,
    STATUS_ERROR_MEMORY_ALLOCATION
} status_code;

status_code parse_args(int argc, char *argv[], int *a, int *b);
status_code fill_random_array_fixed(int *arr, const size_t size, int a, int b);
status_code swap_min_max(int *arr, const size_t size);
status_code fill_random_array_dynamic(int **arr, size_t *size, const size_t min_size, const size_t max_size, const int min_val, const int max_val);
status_code build_array_c(const int *A, const size_t size_A, int *B, const size_t size_B, int **C, size_t *size_C);

#endif
