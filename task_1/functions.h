#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum StatusCode {
    OK = 0,
    ERR_INVALID_INPUT,
    ERR_OVERFLOW,
    ERR_NO_MEMORY
} StatusCode;

typedef enum Primality {
    PRIME,
    COMPOSITE,
    NEITHER_PRIME_NOR_COMPOSITE
} Primality;

#define MULTIPLES_MAX 100
#define HEX_DIGITS_MAX 20
#define POWERS_TABLE_MAX 10

StatusCode parse_args(const int argc, char * const argv[], long long * const x, char * const flag);
StatusCode get_multiples(const long long x, long long ** const multiples, int * const count);
StatusCode check_prime(const long long x, Primality * const primality);
StatusCode split_hex(const long long x, char ** const hex_str);
StatusCode generate_power_table(const long long x, long long *** const table);
StatusCode sum_1_to_x(const long long x, long long * const sum);
StatusCode factorial(const long long x, long long * const fact);

#endif
