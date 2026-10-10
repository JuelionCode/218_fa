#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    long long x;
    char flag;

    StatusCode status = parse_args(argc, argv, &x, &flag);
    if (status != OK) {
        if (status == ERR_OVERFLOW) {
            fprintf(stderr, "Error: Integer overflow in argument parsing.\n");
        } else {
            fprintf(stderr, "Error: Invalid input arguments.\n");
        }
        return 1;
    }

    if (flag == 'h') {
        long long *multiples = NULL;
        int count = 0;
        status = get_multiples(x, &multiples, &count);
        if (status == ERR_INVALID_INPUT) {
            fprintf(stderr, "Error: Input must be a positive integer for multiples.\n");
        } else if (status == ERR_NO_MEMORY) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
        } else {
            if (count == 0) {
                printf("No multiples within [1..100].\n");
            } else {
                for (int i = 0; i < count; i++) {
                    printf("%lld ", multiples[i]);
                }
                printf("\n");
                free(multiples);
            }
        }
    } else if (flag == 'p') {
        Primality p;
        status = check_prime(x, &p);
        if (status == OK) {
            if (p == PRIME) printf("PRIME\n");
            else if (p == COMPOSITE) printf("COMPOSITE\n");
            else printf("NEITHER PRIME NOR COMPOSITE\n");
        } else {
            fprintf(stderr, "Error: Invalid input for primality check.\n");
        }
    } else if (flag == 's') {
        char *hex_str = NULL;
        status = split_hex(x, &hex_str);
        if (status == ERR_INVALID_INPUT) {
            fprintf(stderr, "Error: Input must be non-negative.\n");
        } else if (status == ERR_NO_MEMORY) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
        } else {
            printf("%s\n", hex_str);
            free(hex_str);
        }
    } else if (flag == 'e') {
        long long **table = NULL;
        status = generate_power_table(x, &table);
        if (status == ERR_INVALID_INPUT) {
            fprintf(stderr, "Error: Power table requires x in [1..10].\n");
        } else if (status == ERR_NO_MEMORY) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
        } else if (status == ERR_OVERFLOW) {
            fprintf(stderr, "Error: Integer overflow.\n");
        } else {
            for (int base = 1; base <= 10; base++) {
                for (long long exp = 1; exp <= x; exp++) {
                    printf("%lld ", table[base - 1][exp - 1]);
                }
                printf("\n");
                free(table[base - 1]);
            }
            free(table);
        }
    } else if (flag == 'a') {
        long long sum = 0;
        status = sum_1_to_x(x, &sum);
        if (status == ERR_INVALID_INPUT) {
            fprintf(stderr, "Error: Input must be a positive integer.\n");
        } else if (status == ERR_OVERFLOW) {
            fprintf(stderr, "Error: Integer overflow.\n");
        } else {
            printf("%lld\n", sum);
        }
    } else if (flag == 'f') {
        long long fact = 0;
        status = factorial(x, &fact);
        if (status == ERR_INVALID_INPUT) {
            fprintf(stderr, "Error: Input must be non-negative.\n");
        } else if (status == ERR_OVERFLOW) {
            fprintf(stderr, "Error: Integer overflow.\n");
        } else {
            printf("%lld\n", fact);
        }
    } else {
        fprintf(stderr, "Error: Unrecognized flag.\n");
        return 1;
    }

    return 0;
}
