#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>

StatusCode validate_and_parse_double(const char *str, double *out_val) {
    if (!str || !*str) return STATUS_INVALID_NUMBER;
    char *endptr;
    double val = strtod(str, &endptr);
    if (endptr == str || *endptr != '\0') return STATUS_INVALID_NUMBER;
    if (val == HUGE_VAL || val == -HUGE_VAL || isnan(val) || isinf(val)) return STATUS_INVALID_NUMBER;
    *out_val = val;
    return STATUS_OK;
}

StatusCode validate_and_parse_int(const char *str, int *out_val) {
    if (!str || !*str) return STATUS_INVALID_NUMBER;
    char *endptr;
    long val = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') return STATUS_INVALID_NUMBER;
    if (val > INT_MAX || val < INT_MIN || val == LONG_MAX || val == LONG_MIN) return STATUS_INVALID_NUMBER;
    *out_val = (int)val;
    return STATUS_OK;
}

StatusCode validate_and_parse_long(const char *str, long *out_val) {
    if (!str || !*str) return STATUS_INVALID_NUMBER;
    char *endptr;
    long val = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') return STATUS_INVALID_NUMBER;
    if (val == LONG_MAX || val == LONG_MIN) return STATUS_INVALID_NUMBER;
    *out_val = val;
    return STATUS_OK;
}

StatusCode is_multiple(const long a, const long b, int *result) {
    if (b == 0) return STATUS_DIVISION_BY_ZERO;
    *result = (a % b == 0);
    return STATUS_OK;
}

StatusCode is_right_triangle(const double eps, const double a, const double b, const double c, int *result) {
    if (a <= eps || b <= eps || c <= eps) {
        *result = 0;
        return STATUS_OK;
    }
    double a2 = a * a;
    double b2 = b * b;
    double c2 = c * c;
    if (fabs(a2 + b2 - c2) < eps || fabs(a2 + c2 - b2) < eps || fabs(b2 + c2 - a2) < eps) {
        *result = 1;
    } else {
        *result = 0;
    }
    return STATUS_OK;
}

StatusCode solve_quadratic(const double eps, const double a, const double b, const double c, QuadraticResult *result) {
    if (fabs(a) < eps) {
        if (fabs(b) < eps) {
            if (fabs(c) < eps) {
                result->status = ROOTS_INFINITE;
            } else {
                result->status = ROOTS_ZERO;
            }
        } else {
            result->status = ROOTS_ONE;
            result->root1 = -c / b;
        }
    } else {
        double d = b * b - 4 * a * c;
        if (d > eps) {
            result->status = ROOTS_TWO;
            result->root1 = (-b + sqrt(d)) / (2 * a);
            result->root2 = (-b - sqrt(d)) / (2 * a);
        } else if (fabs(d) <= eps) {
            result->status = ROOTS_ONE;
            result->root1 = -b / (2 * a);
        } else {
            result->status = ROOTS_COMPLEX;
            result->root1 = -b / (2 * a);
            result->imag_part = sqrt(-d) / (2 * fabs(a));
        }
    }
    return STATUS_OK;
}

static int are_doubles_equal(const double x, const double y, const double eps) {
    return fabs(x - y) < eps;
}

static int is_perm_unique(double perms[6][3], const int count, const double a, const double b, const double c, const double eps) {
    for (int i = 0; i < count; i++) {
        if (are_doubles_equal(perms[i][0], a, eps) &&
            are_doubles_equal(perms[i][1], b, eps) &&
            are_doubles_equal(perms[i][2], c, eps)) {
            return 0;
        }
    }
    return 1;
}

StatusCode get_unique_permutations(const double a, const double b, const double c, double perms[6][3], int *count, const double eps) {
    double p[6][3] = {
            {a, b, c},
            {a, c, b},
            {b, a, c},
            {b, c, a},
            {c, a, b},
            {c, b, a}
    };
    *count = 0;
    for (int i = 0; i < 6; i++) {
        if (is_perm_unique(perms, *count, p[i][0], p[i][1], p[i][2], eps)) {
            perms[*count][0] = p[i][0];
            perms[*count][1] = p[i][1];
            perms[*count][2] = p[i][2];
            (*count)++;
        }
    }
    return STATUS_OK;
}
