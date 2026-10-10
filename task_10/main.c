#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "functions.h"

int main() {
    int base;
    if (scanf("%d", &base) != 1) {
        fprintf(stderr, "Error: Failed to read base.\n");
        return 1;
    }
    if (validate_base(base) != SUCCESS) {
        fprintf(stderr, "Error: Invalid base.\n");
        return 1;
    }

    char buf[1024];
    unsigned long long max_abs = 0;
    long long max_val_real = 0;
    long long sum = 0;
    int count = 0;

    while (scanf("%1023s", buf) == 1) {
        if (strcmp(buf, "Stop") == 0) {
            break;
        }

        long long val;
        StatusCode status = parse_string_to_ll(buf, base, &val);
        if (status == INVALID_INPUT) {
            fprintf(stderr, "Error: Invalid input string '%s' for base %d.\n", buf, base);
            return 1;
        } else if (status == OVERFLOW_ERROR) {
            fprintf(stderr, "Error: Overflow while parsing '%s'.\n", buf);
            return 1;
        }

        unsigned long long abs_val;
        if (val < 0) {
            if (val == LLONG_MIN) {
                abs_val = (unsigned long long)LLONG_MAX + 1ULL;
            } else {
                abs_val = (unsigned long long)(-val);
            }
        } else {
            abs_val = (unsigned long long)val;
        }

        if (count == 0 || abs_val > max_abs) {
            max_abs = abs_val;
            max_val_real = val;
        }

        if (add_ll(sum, val, &sum) == OVERFLOW_ERROR) {
            fprintf(stderr, "Error: Overflow during summation.\n");
            return 1;
        }

        count++;
    }

    if (count == 0) {
        return 0;
    }

    int target_bases[] = {9, 18, 27, 36};
    char* str = NULL;

    printf("Max absolute:\n");
    if (ll_to_string(max_val_real, 10, &str) != SUCCESS) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }
    printf("Base 10: %s\n", str);
    free(str);

    for (int i = 0; i < 4; i++) {
        if (ll_to_string(max_val_real, target_bases[i], &str) != SUCCESS) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return 1;
        }
        printf("Base %d: %s\n", target_bases[i], str);
        free(str);
    }

    printf("\nSum:\n");
    if (ll_to_string(sum, 10, &str) != SUCCESS) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }
    printf("Base 10: %s\n", str);
    free(str);

    for (int i = 0; i < 4; i++) {
        if (ll_to_string(sum, target_bases[i], &str) != SUCCESS) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            return 1;
        }
        printf("Base %d: %s\n", target_bases[i], str);
        free(str);
    }

    return 0;
}
