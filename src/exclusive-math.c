#include "exclusive-math.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

number_t pow_(number_t base, int exp) {
    number_t result = 1;
    while (exp--) result *= base;
    return result;
}

number_t fabs_(number_t x) {
    return (x < 0 ? -x : x);
}

bool doubleEquals(number_t a, number_t b, number_t epsilon) {
    return fabs_(a - b) < epsilon;
}

number_t factorial(int n) {
    if (n < 0) {
        fprintf(stderr,
                "I don't know what is factorial of %d,"
                " but I can quack. Quack\n",
                n);
        exit(1);
    }

    number_t value = 1;
    while (n--) value *= n + 1;
    return value;
}

number_t rad(number_t deg) {
    return deg * (PI / 180);
}
