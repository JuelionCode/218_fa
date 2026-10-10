#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum Status {
    SUCCESS,
    ERROR_INVALID_INPUT,
    ERROR_MEMORY,
    ERROR_FILE,
    ERROR_DIVERGE
} Status;

Status calc_sum_a(const double x, const double eps, double *res);
Status calc_sum_b(const double x, const double eps, double *res);
Status calc_sum_c(const double x, const double eps, double *res);
Status calc_sum_d(const double x, const double eps, double *res);

Status integrate_a(const double eps, double *res);
Status integrate_b(const double eps, double *res);
Status integrate_c(const double eps, double *res);
Status integrate_d(const double eps, double *res);

#endif
