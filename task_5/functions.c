#include "functions.h"
#include <math.h>

Status calc_sum_a(const double x, const double eps, double *res) {
    if (!res) return ERROR_INVALID_INPUT;
    if (!isfinite(eps) || !(eps > 0.0) || !isfinite(x)) return ERROR_INVALID_INPUT;

    double sum = 1.0;
    double term = 1.0;
    long long n = 1;
    while (fabs(term) > eps) {
        term = term * x / (double)n;
        sum += term;
        n++;
        if (n > 1000000) return ERROR_DIVERGE;
    }
    *res = sum;
    return SUCCESS;
}

Status calc_sum_b(const double x, const double eps, double *res) {
    if (!res) return ERROR_INVALID_INPUT;
    if (!isfinite(eps) || !(eps > 0.0) || !isfinite(x)) return ERROR_INVALID_INPUT;

    double sum = 1.0;
    double term = 1.0;
    long long n = 1;
    while (fabs(term) > eps) {
        term = term * (-1.0) * x * x / ((2.0 * n) * (2.0 * n - 1.0));
        sum += term;
        n++;
        if (n > 1000000) return ERROR_DIVERGE;
    }
    *res = sum;
    return SUCCESS;
}

Status calc_sum_c(const double x, const double eps, double *res) {
    if (!res) return ERROR_INVALID_INPUT;
    if (!isfinite(eps) || !(eps > 0.0) || !isfinite(x)) return ERROR_INVALID_INPUT;

    double sum = 1.0;
    double term = 1.0;
    long long n = 1;
    while (fabs(term) > eps) {
        term = term * 9.0 * n * n * x * x / ((3.0 * n - 1.0) * (3.0 * n - 2.0));
        sum += term;
        n++;
        if (n > 1000000) return ERROR_DIVERGE;
    }
    *res = sum;
    return SUCCESS;
}

Status calc_sum_d(const double x, const double eps, double *res) {
    if (!res) return ERROR_INVALID_INPUT;
    if (!isfinite(eps) || !(eps > 0.0) || !isfinite(x)) return ERROR_INVALID_INPUT;

    double sum = 0.0;
    double term = -(x * x) / 2.0;
    sum += term;
    long long n = 2;
    while (fabs(term) > eps) {
        term = term * (-1.0) * (2.0 * n - 1.0) * x * x / (2.0 * n);
        sum += term;
        n++;
        if (n > 1000000) return ERROR_DIVERGE;
    }
    *res = sum;
    return SUCCESS;
}

static double f_a(const double x) {
    if (fabs(x) < 1e-9) return 1.0;
    return log(1.0 + x) / x;
}

static double f_b(const double x) {
    return exp(-x * x / 2.0);
}

static double f_c(const double x) {
    if (1.0 - x < 1e-9) return 0.0;
    return -log(1.0 - x);
}

static double f_d(const double x) {
    if (fabs(x) < 1e-9) return 1.0;
    return pow(x, x);
}

static Status integrate(double (*f)(double), const double a, const double b, const double eps, double *res) {
    if (!res) return ERROR_INVALID_INPUT;
    if (!isfinite(eps) || !(eps > 0.0)) return ERROR_INVALID_INPUT;

    long long n = 2;
    double prev = 0.0;
    double curr = 0.0;
    double h = (b - a) / (double)n;
    for (long long i = 0; i < n; i++) {
        curr += f(a + (i + 0.5) * h);
    }
    curr *= h;

    do {
        prev = curr;
        n *= 2;
        if (n > 100000000) return ERROR_DIVERGE;
        h = (b - a) / (double)n;
        curr = 0.0;
        for (long long i = 0; i < n; i++) {
            curr += f(a + (i + 0.5) * h);
        }
        curr *= h;
    } while (fabs(curr - prev) > eps);

    *res = curr;
    return SUCCESS;
}

Status integrate_a(const double eps, double *res) {
    return integrate(f_a, 0.0, 1.0, eps, res);
}

Status integrate_b(const double eps, double *res) {
    return integrate(f_b, 0.0, 1.0, eps, res);
}

Status integrate_c(const double eps, double *res) {
    return integrate(f_c, 0.0, 1.0, eps, res);
}

Status integrate_d(const double eps, double *res) {
    return integrate(f_d, 0.0, 1.0, eps, res);
}
