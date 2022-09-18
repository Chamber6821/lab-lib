#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h> // for INFINITY
#include <malloc.h>
#include "input.h"
#include "string-utils.h"

void input(const char *prompt, const char *inputPattern, void *buffer);

double inputDouble(const char *prompt) {
    return inputDoubleInRange(prompt, -INFINITY, INFINITY, MAX_LIMIT | MIN_LIMIT);
}

double inputDoublePositive(const char *prompt) {
    return inputDoubleInRange(prompt, 0, INFINITY, MAX_LIMIT);
}

int inputNatural(const char *prompt) {
    return inputIntInRange(prompt, 1, INT_MAX);
}

int inputNatural0(const char *prompt) {
    return inputIntInRange(prompt, 0, INT_MAX);
}

int inputIntInRange(const char *prompt, int min, int max) {
    while (1) {
        int value;
        input(prompt, "%d", &value);

        if (min <= value && value <= max) return value;

        printf("Must be in range from %d to %d. Try again\n", min, max);
    }
}

double inputDoubleInRange(const char *prompt, double min, double max, RangeInclude include) {
    const char leftPar = (include & MIN_LIMIT) ? '[' : '(';
    const char rightPar = (include & MAX_LIMIT) ? ']' : ')';

    while (true) {
        double value;
        input(prompt, "%lf", &value);

        bool isInRange = min < value && value < max;
        bool isMin = (include & MIN_LIMIT) && min == value;
        bool isMax = (include & MAX_LIMIT) && max == value;
        if (isInRange || isMin || isMax) return value;

        printf("Must be in range %c%lf, %lf%c. Try again\n", leftPar, min, max, rightPar);
    }
}

void input(const char *prompt, const char *inputPattern, void *buffer) {
    char *pattern = concat(inputPattern, "%n");

    while (1) {
        printf("%s", prompt);
        char *string = lightTrimEnd(readString(stdin));
        size_t length = strlen(string);

        size_t read = 0;
        sscanf(string, pattern, buffer, &read);

        free(string);

        if (read == length) break;
        else printf("Wrong! Try again\n");
    }

    free(pattern);
}
