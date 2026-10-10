#include <stdio.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Invalid arguments\n");
        return STATUS_INVALID_ARGS;
    }

    const char *flag = argv[1];
    if (flag[0] != '-' && flag[0] != '/') {
        fprintf(stderr, "Invalid flag format\n");
        return STATUS_INVALID_FLAG;
    }

    if (strcmp(flag + 1, "q") == 0) {
        if (argc != 6) {
            fprintf(stderr, "Invalid arguments\n");
            return STATUS_INVALID_ARGS;
        }
        double eps, a, b, c;
        if (validate_and_parse_double(argv[2], &eps) != STATUS_OK ||
            validate_and_parse_double(argv[3], &a) != STATUS_OK ||
            validate_and_parse_double(argv[4], &b) != STATUS_OK ||
            validate_and_parse_double(argv[5], &c) != STATUS_OK) {
            fprintf(stderr, "Invalid number\n");
            return STATUS_INVALID_NUMBER;
        }

        if (eps <= 0.0) {
            fprintf(stderr, "Invalid epsilon\n");
            return STATUS_INVALID_NUMBER;
        }

        double perms[6][3];
        int count;
        get_unique_permutations(a, b, c, perms, &count, eps);

        for (int i = 0; i < count; i++) {
            QuadraticResult result;
            solve_quadratic(eps, perms[i][0], perms[i][1], perms[i][2], &result);
            printf("%f x^2 + %f x + %f = 0: ", perms[i][0], perms[i][1], perms[i][2]);
            if (result.status == ROOTS_ZERO) {
                printf("No real roots\n");
            } else if (result.status == ROOTS_ONE) {
                printf("One root: %f\n", result.root1);
            } else if (result.status == ROOTS_TWO) {
                printf("Two roots: %f, %f\n", result.root1, result.root2);
            } else if (result.status == ROOTS_COMPLEX) {
                printf("Complex roots: %f + %fi, %f - %fi\n", result.root1, result.imag_part, result.root1, result.imag_part);
            } else if (result.status == ROOTS_INFINITE) {
                printf("Infinite roots\n");
            }
        }
    } else if (strcmp(flag + 1, "m") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Invalid arguments\n");
            return STATUS_INVALID_ARGS;
        }
        long a, b;
        if (validate_and_parse_long(argv[2], &a) != STATUS_OK ||
            validate_and_parse_long(argv[3], &b) != STATUS_OK) {
            fprintf(stderr, "Invalid number\n");
            return STATUS_INVALID_NUMBER;
        }
        if (a == 0 || b == 0) {
            fprintf(stderr, "Invalid number (must be non-zero)\n");
            return STATUS_INVALID_NUMBER;
        }
        int is_mult;
        StatusCode sc = is_multiple(a, b, &is_mult);
        if (sc != STATUS_OK) {
            fprintf(stderr, "Error\n");
            return sc;
        }
        if (is_mult) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    } else if (strcmp(flag + 1, "t") == 0) {
        if (argc != 6) {
            fprintf(stderr, "Invalid arguments\n");
            return STATUS_INVALID_ARGS;
        }
        double eps, a, b, c;
        if (validate_and_parse_double(argv[2], &eps) != STATUS_OK ||
            validate_and_parse_double(argv[3], &a) != STATUS_OK ||
            validate_and_parse_double(argv[4], &b) != STATUS_OK ||
            validate_and_parse_double(argv[5], &c) != STATUS_OK) {
            fprintf(stderr, "Invalid number\n");
            return STATUS_INVALID_NUMBER;
        }

        if (eps <= 0.0) {
            fprintf(stderr, "Invalid epsilon\n");
            return STATUS_INVALID_NUMBER;
        }

        int is_right;
        is_right_triangle(eps, a, b, c, &is_right);
        if (is_right) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    } else {
        fprintf(stderr, "Invalid flag\n");
        return STATUS_INVALID_FLAG;
    }

    return STATUS_OK;
}
