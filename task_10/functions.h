#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum StatusCode {
    SUCCESS,
    INVALID_INPUT,
    MEMORY_ERROR,
    OVERFLOW_ERROR
} StatusCode;

StatusCode validate_base(int base);
StatusCode parse_string_to_ll(const char* str, int base, long long* out_val);
StatusCode add_ll(long long a, long long b, long long* out_sum);
StatusCode ll_to_string(long long val, int base, char** out_str);

#endif
