#pragma once

#include <stdbool.h>

#define INFINITY (1./0.)
#define NAN (0./0.)
#define PI 3.1415926535897932384

#define isnan(x) ((x) != (x))

typedef long double number_t;

number_t pow_(number_t base, int exp);

number_t fabs_(number_t x);

bool doubleEquals(number_t a, number_t b, number_t epsilon);

number_t factorial(int n);

number_t rad(number_t deg);
