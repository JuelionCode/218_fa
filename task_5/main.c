#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

static void print_status_result(const char *name, Status status, double value) {
    switch (status) {
        case SUCCESS:
            printf("%s: %.10f\n", name, value);
            break;
        case ERROR_INVALID_INPUT:
            fprintf(stderr, "%s: Error - invalid input parameters\n", name);
            break;
        case ERROR_DIVERGE:
            fprintf(stderr, "%s: Error - series/integral diverged or iteration limit reached\n", name);
            break;
        case ERROR_MEMORY:
            fprintf(stderr, "%s: Error - memory allocation error\n", name);
            break;
        case ERROR_FILE:
            fprintf(stderr, "%s: Error - file error\n", name);
            break;
        default:
            fprintf(stderr, "%s: Error - unknown error\n", name);
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <epsilon> [x]\n", argv[0]);
        fprintf(stderr, "   or: %s <x> <epsilon>\n", argv[0]);
        return 1;
    }

    double x = 0.5;
    double eps = 0.0;
    char *endptr = NULL;

    if (argc == 2) {
        eps = strtod(argv[1], &endptr);
        if (*endptr != '\0' || argv[1][0] == '\0' || !isfinite(eps) || eps <= 0.0) {
            fprintf(stderr, "Error: Invalid epsilon '%s'\n", argv[1]);
            return 1;
        }
    } else {
        double val1 = strtod(argv[1], &endptr);
        if (*endptr != '\0' || argv[1][0] == '\0' || !isfinite(val1)) {
            fprintf(stderr, "Error: Invalid first argument '%s'\n", argv[1]);
            return 1;
        }
        double val2 = strtod(argv[2], &endptr);
        if (*endptr != '\0' || argv[2][0] == '\0' || !isfinite(val2)) {
            fprintf(stderr, "Error: Invalid second argument '%s'\n", argv[2]);
            return 1;
        }

        if (val2 > 0.0 && val2 < 1.0) {
            x = val1;
            eps = val2;
        } else if (val1 > 0.0 && val1 < 1.0) {
            eps = val1;
            x = val2;
        } else {
            x = val1;
            eps = val2;
        }

        if (eps <= 0.0) {
            fprintf(stderr, "Error: Epsilon must be positive, got %f\n", eps);
            return 1;
        }
    }

    printf("Parameters: x = %.6f, epsilon = %.10f\n\n", x, eps);

    double res = 0.0;
    Status st;

    printf("--- Series ---\n");
    st = calc_sum_a(x, eps, &res);
    print_status_result("Series A", st, res);

    st = calc_sum_b(x, eps, &res);
    print_status_result("Series B", st, res);

    st = calc_sum_c(x, eps, &res);
    print_status_result("Series C", st, res);

    st = calc_sum_d(x, eps, &res);
    print_status_result("Series D", st, res);

    printf("\n--- Integrals ---\n");
    st = integrate_a(eps, &res);
    print_status_result("Integral A", st, res);

    st = integrate_b(eps, &res);
    print_status_result("Integral B", st, res);

    st = integrate_c(eps, &res);
    print_status_result("Integral C", st, res);

    st = integrate_d(eps, &res);
    print_status_result("Integral D", st, res);

    return 0;
}
