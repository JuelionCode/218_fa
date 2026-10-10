#include "functions.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

StatusCode parse_args(const int argc, char * const argv[], long long * const x, char * const flag) {
    if (argc != 3) {
        return ERR_INVALID_INPUT;
    }

    const char *str_x = NULL;
    const char *str_flag = NULL;

    if ((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][1] != '\0' && argv[1][2] == '\0') {
        str_flag = argv[1];
        str_x = argv[2];
    } else if ((argv[2][0] == '-' || argv[2][0] == '/') && argv[2][1] != '\0' && argv[2][2] == '\0') {
        str_flag = argv[2];
        str_x = argv[1];
    } else {
        return ERR_INVALID_INPUT;
    }

    *flag = str_flag[1];

    char *endptr;
    *x = strtoll(str_x, &endptr, 10);
    
    if (endptr == str_x || *endptr != '\0') {
        return ERR_INVALID_INPUT;
    }
    
    if (*x == LLONG_MAX || *x == LLONG_MIN) {
        return ERR_OVERFLOW;
    }

    return OK;
}

StatusCode get_multiples(const long long x, long long ** const multiples, int * const count) {
    if (x <= 0) {
        return ERR_INVALID_INPUT;
    }

    *count = 0;
    if (x > MULTIPLES_MAX) {
        *multiples = NULL;
        return OK;
    }

    int max_count = MULTIPLES_MAX / (int)x;
    *multiples = (long long *)malloc(max_count * sizeof(long long));
    if (!(*multiples)) {
        return ERR_NO_MEMORY;
    }

    for (int i = 1; i <= max_count; i++) {
        (*multiples)[i - 1] = x * i;
    }
    *count = max_count;

    return OK;
}

StatusCode check_prime(const long long x, Primality * const primality) {
    if (x < 2) {
        *primality = NEITHER_PRIME_NOR_COMPOSITE;
        return OK;
    }
    if (x == 2) {
        *primality = PRIME;
        return OK;
    }
    if (x % 2 == 0) {
        *primality = COMPOSITE;
        return OK;
    }
    for (long long i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            *primality = COMPOSITE;
            return OK;
        }
    }
    *primality = PRIME;
    return OK;
}

StatusCode split_hex(const long long x, char ** const hex_str) {
    if (x < 0) {
        return ERR_INVALID_INPUT;
    }

    if (x == 0) {
        *hex_str = (char *)malloc(2);
        if (!*hex_str) return ERR_NO_MEMORY;
        strcpy(*hex_str, "0");
        return OK;
    }

    char buffer[64];
    int pos = 0;
    long long temp = x;
    while (temp > 0) {
        int rem = temp % 16;
        if (rem < 10) {
            buffer[pos++] = '0' + rem;
        } else {
            buffer[pos++] = 'a' + (rem - 10);
        }
        temp /= 16;
    }

    *hex_str = (char *)malloc(pos * 2);
    if (!*hex_str) return ERR_NO_MEMORY;

    int str_idx = 0;
    for (int i = pos - 1; i >= 0; i--) {
        (*hex_str)[str_idx++] = buffer[i];
        if (i > 0) {
            (*hex_str)[str_idx++] = ' ';
        }
    }
    (*hex_str)[str_idx] = '\0';

    return OK;
}

StatusCode generate_power_table(const long long x, long long *** const table) {
    if (x <= 0 || x > 10) {
        return ERR_INVALID_INPUT;
    }

    *table = (long long **)malloc(10 * sizeof(long long *));
    if (!(*table)) return ERR_NO_MEMORY;

    for (int i = 0; i < 10; i++) {
        (*table)[i] = (long long *)malloc(x * sizeof(long long));
        if (!(*table)[i]) {
            for (int j = 0; j < i; j++) {
                free((*table)[j]);
            }
            free(*table);
            return ERR_NO_MEMORY;
        }
    }

    for (int base_idx = 0; base_idx < 10; base_idx++) {
        long long current_val = 1;
        long long base = base_idx + 1;
        for (long long exp_idx = 0; exp_idx < x; exp_idx++) {
            if (base != 0 && current_val > LLONG_MAX / base) {
                for (int j = 0; j < 10; j++) free((*table)[j]);
                free(*table);
                *table = NULL;
                return ERR_OVERFLOW;
            }
            current_val *= base;
            (*table)[base_idx][exp_idx] = current_val;
        }
    }

    return OK;
}

StatusCode sum_1_to_x(const long long x, long long * const sum) {
    if (x <= 0) {
        return ERR_INVALID_INPUT;
    }

    long long a, b;
    if (x % 2 == 0) {
        a = x / 2;
        b = x + 1;
    } else {
        a = (x + 1) / 2;
        b = x;
    }
    
    if (a != 0 && b > LLONG_MAX / a) {
        return ERR_OVERFLOW;
    }
    
    *sum = a * b;
    return OK;
}

StatusCode factorial(const long long x, long long * const fact) {
    if (x < 0) {
        return ERR_INVALID_INPUT;
    }

    if (x > 20) {
        return ERR_OVERFLOW;
    }

    *fact = 1;
    for (long long i = 2; i <= x; i++) {
        *fact *= i;
    }

    return OK;
}
