#include "functions.h"
#include <stdlib.h>
#include <limits.h>

StatusCode validate_base(int base) {
    if (base >= 2 && base <= 36) {
        return SUCCESS;
    }
    return INVALID_INPUT;
}

static int char_to_val(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
    return -1;
}

StatusCode parse_string_to_ll(const char* str, int base, long long* out_val) {
    if (!str || !out_val || base < 2 || base > 36) return INVALID_INPUT;
    if (str[0] == '\0') return INVALID_INPUT;

    int sign = 1;
    int start = 0;
    if (str[0] == '-') {
        sign = -1;
        start = 1;
        if (str[1] == '\0') return INVALID_INPUT;
    }

    long long val = 0;
    for (int i = start; str[i] != '\0'; i++) {
        int d = char_to_val(str[i]);
        if (d < 0 || d >= base) return INVALID_INPUT;

        if (sign == 1) {
            if (val > (LLONG_MAX - d) / base) return OVERFLOW_ERROR;
            val = val * base + d;
        } else {
            if (val < (LLONG_MIN + d) / base) return OVERFLOW_ERROR;
            val = val * base - d;
        }
    }
    *out_val = val;
    return SUCCESS;
}

StatusCode add_ll(long long a, long long b, long long* out_sum) {
    if (!out_sum) return INVALID_INPUT;
    if ((b > 0) && (a > LLONG_MAX - b)) return OVERFLOW_ERROR;
    if ((b < 0) && (a < LLONG_MIN - b)) return OVERFLOW_ERROR;
    *out_sum = a + b;
    return SUCCESS;
}

static char val_to_char(int val) {
    if (val >= 0 && val <= 9) return (char)('0' + val);
    return (char)('A' + val - 10);
}

StatusCode ll_to_string(long long val, int base, char** out_str) {
    if (!out_str || base < 2 || base > 36) return INVALID_INPUT;

    if (val == 0) {
        *out_str = (char*)malloc(2 * sizeof(char));
        if (!*out_str) return MEMORY_ERROR;
        (*out_str)[0] = '0';
        (*out_str)[1] = '\0';
        return SUCCESS;
    }

    int is_negative = (val < 0) ? 1 : 0;
    unsigned long long uval;
    if (is_negative) {
        if (val == LLONG_MIN) {
            uval = (unsigned long long)LLONG_MAX + 1ULL;
        } else {
            uval = (unsigned long long)(-val);
        }
    } else {
        uval = (unsigned long long)val;
    }

    int digits = 0;
    unsigned long long temp = uval;
    while (temp > 0) {
        digits++;
        temp /= base;
    }

    int capacity = digits + is_negative + 1;
    char* buf = (char*)malloc(capacity * sizeof(char));
    if (!buf) return MEMORY_ERROR;

    int pos = 0;
    while (uval > 0) {
        int rem = (int)(uval % base);
        buf[pos++] = val_to_char(rem);
        uval /= base;
    }
    if (is_negative) {
        buf[pos++] = '-';
    }
    buf[pos] = '\0';

    for (int i = 0; i < pos / 2; i++) {
        char tmp = buf[i];
        buf[i] = buf[pos - 1 - i];
        buf[pos - 1 - i] = tmp;
    }

    *out_str = buf;
    return SUCCESS;
}
