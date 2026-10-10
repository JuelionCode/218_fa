#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum {
    STATUS_OK,
    STATUS_INVALID_ARGS,
    STATUS_INVALID_FLAG,
    STATUS_INVALID_NUMBER,
    STATUS_DIVISION_BY_ZERO
} StatusCode;

typedef enum {
    ROOTS_ZERO,
    ROOTS_ONE,
    ROOTS_TWO,
    ROOTS_COMPLEX,
    ROOTS_INFINITE
} RootsStatus;

typedef struct {
    double root1;
    double root2;
    double imag_part;
    RootsStatus status;
} QuadraticResult;

StatusCode validate_and_parse_double(const char *str, double *out_val);
StatusCode validate_and_parse_int(const char *str, int *out_val);
StatusCode validate_and_parse_long(const char *str, long *out_val);
StatusCode is_multiple(const long a, const long b, int *result);
StatusCode is_right_triangle(const double eps, const double a, const double b, const double c, int *result);
StatusCode solve_quadratic(const double eps, const double a, const double b, const double c, QuadraticResult *result);
StatusCode get_unique_permutations(const double a, const double b, const double c, double perms[6][3], int *count, const double eps);

#endif
