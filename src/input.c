#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h> // for INFINITY, fabs
#include <malloc.h>
#include <locale.h>
#include "input.h"
#include "string-utils.h"

void input(const char *prompt, const char *inputPattern, void *buffer);

bool tryInput(const char *prompt, const char *inputPattern, void *buffer);

bool tryParseWithLocale(const char *source, const char *bufferPattern, void *buffer, const char *locale);

bool tryParse(const char *source, const char *bufferPattern, void *buffer);

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
    while (true) {
        int value;
        input(prompt, "%d", &value);

        if (min <= value && value <= max) return value;

        printf("Must be in range from %d to %d. Try again\n", min, max);
    }
}

bool doubleEquals(double a, double b, double epsilon) {
    return fabs(a - b) < epsilon;
}

double inputDoubleInRange(const char *prompt, double min, double max, RangeInclude include) {
    const char leftPar = (include & MIN_LIMIT) ? '[' : '(';
    const char rightPar = (include & MAX_LIMIT) ? ']' : ')';

    while (true) {
        double value = inputDouble(prompt);

        bool isInRange = min < value && value < max;
        bool isMin = (include & MIN_LIMIT) && doubleEquals(min, value, 0.0001);
        bool isMax = (include & MAX_LIMIT) && doubleEquals(max, value, 0.0001);
        if (isInRange || isMin || isMax) return value;

        printf("Must be in range %c%lf, %lf%c. Try again\n", leftPar, min, max, rightPar);
    }
}

double inputDouble(const char *prompt) {
    while (true) {
        double value = 0;

        printf("%s", prompt);
        char *string = lightTrimEnd(readString(stdin));
        bool success = tryParseWithLocale(string, "%lf", &value, "C")
                || tryParseWithLocale(string, "%lf", &value, "Russian");
        free(string);

        if (success) return value;
        printf("Wrong double format! Try again\n");
    }
}

void input(const char *prompt, const char *inputPattern, void *buffer) {
    while (!tryInput(prompt, inputPattern, buffer)) {
        printf("Wrong! Try again\n");
    }
}

bool tryInput(const char *prompt, const char *inputPattern, void *buffer) {
    printf("%s", prompt);

    char *string = lightTrimEnd(readString(stdin));
    bool status = tryParse(string, inputPattern, buffer);
    free(string);

    return status;
}

bool tryParseWithLocale(const char *source, const char *bufferPattern, void *buffer, const char *locale) {
    const char *oldLocale = setlocale(LC_NUMERIC, NULL);

    setlocale(LC_NUMERIC, locale);
    bool success = tryParse(source, bufferPattern, buffer);
    setlocale(LC_NUMERIC, oldLocale);

    return success;
}

bool tryParse(const char *source, const char *bufferPattern, void *buffer) {
    size_t length = strlen(source);
    size_t read = 0;

    char *pattern = concat(bufferPattern, "%n");
    sscanf(source, pattern, buffer, &read);
    free(pattern);

    return read == length;
}
