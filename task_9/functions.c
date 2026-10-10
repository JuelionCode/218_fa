#include "functions.h"
#include <stdlib.h>
#include <limits.h>

status_code parse_args(int argc, char *argv[], int *a, int *b) {
    if (argc != 3) {
        return STATUS_ERROR_INVALID_ARGS;
    }
    if (a == NULL || b == NULL || argv == NULL) {
        return STATUS_ERROR_NULL_POINTER;
    }
    
    char *endptr;
    long val_a = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || endptr == argv[1] || val_a == LONG_MAX || val_a == LONG_MIN || val_a > INT_MAX || val_a < INT_MIN) {
        return STATUS_ERROR_INVALID_ARGS;
    }
    
    long val_b = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || endptr == argv[2] || val_b == LONG_MAX || val_b == LONG_MIN || val_b > INT_MAX || val_b < INT_MIN) {
        return STATUS_ERROR_INVALID_ARGS;
    }
    
    *a = (int)val_a;
    *b = (int)val_b;
    return STATUS_OK;
}

status_code fill_random_array_fixed(int *arr, const size_t size, int a, int b) {
    if (arr == NULL) {
        return STATUS_ERROR_NULL_POINTER;
    }
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    for (size_t i = 0; i < size; ++i) {
        arr[i] = a + rand() % (b - a + 1);
    }
    return STATUS_OK;
}

status_code swap_min_max(int *arr, const size_t size) {
    if (arr == NULL) {
        return STATUS_ERROR_NULL_POINTER;
    }
    if (size == 0) {
        return STATUS_OK;
    }
    size_t min_idx = 0;
    size_t max_idx = 0;
    int min_val = arr[0];
    int max_val = arr[0];
    for (size_t i = 1; i < size; ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_idx = i;
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_idx = i;
        }
    }
    int temp = arr[min_idx];
    arr[min_idx] = arr[max_idx];
    arr[max_idx] = temp;
    return STATUS_OK;
}

status_code fill_random_array_dynamic(int **arr, size_t *size, const size_t min_size, const size_t max_size, const int min_val, const int max_val) {
    if (arr == NULL || size == NULL) {
        return STATUS_ERROR_NULL_POINTER;
    }
    if (min_size > max_size) {
        return STATUS_ERROR_INVALID_ARGS;
    }
    if (min_val > max_val) {
        return STATUS_ERROR_INVALID_ARGS;
    }
    *size = min_size + (size_t)(rand() % (int)(max_size - min_size + 1));
    *arr = (int *)malloc(*size * sizeof(int));
    if (*arr == NULL) {
        return STATUS_ERROR_MEMORY_ALLOCATION;
    }
    for (size_t i = 0; i < *size; ++i) {
        (*arr)[i] = min_val + rand() % (max_val - min_val + 1);
    }
    return STATUS_OK;
}

static int compare_ints(const void *a, const void *b) {
    int int_a = *((const int *)a);
    int int_b = *((const int *)b);
    if (int_a < int_b) return -1;
    if (int_a > int_b) return 1;
    return 0;
}

static int find_nearest(const int val, const int *B, const size_t size_B) {
    if (size_B == 0) {
        return 0;
    }
    size_t left = 0;
    size_t right = size_B - 1;
    if (val <= B[0]) {
        return B[0];
    }
    if (val >= B[size_B - 1]) {
        return B[size_B - 1];
    }
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (B[mid] == val) {
            return B[mid];
        }
        if (B[mid] < val) {
            left = mid + 1;
        } else {
            if (mid == 0) {
                break;
            }
            right = mid - 1;
        }
    }
    int diff_right = abs(val - B[right]);
    int diff_left = abs(B[left] - val);
    if (diff_right <= diff_left) {
        return B[right];
    }
    return B[left];
}

status_code build_array_c(const int *A, const size_t size_A, int *B, const size_t size_B, int **C, size_t *size_C) {
    if (A == NULL || B == NULL || C == NULL || size_C == NULL) {
        return STATUS_ERROR_NULL_POINTER;
    }
    if (size_A == 0 || size_B == 0) {
        return STATUS_ERROR_INVALID_ARGS;
    }

    qsort(B, size_B, sizeof(int), compare_ints);

    *C = (int *)malloc(size_A * sizeof(int));
    if (*C == NULL) {
        return STATUS_ERROR_MEMORY_ALLOCATION;
    }
    *size_C = size_A;

    for (size_t i = 0; i < size_A; ++i) {
        int nearest = find_nearest(A[i], B, size_B);
        (*C)[i] = A[i] + nearest;
    }

    return STATUS_OK;
}
