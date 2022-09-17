#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "input.h"
#include "string-utils.h"

void input(const char *prompt, const char *inputPattern, void *buffer);

double inputDouble(const char *prompt) {
    double value;
    input(prompt, "%lf", &value);
    return value;
}

double inputDoublePositive(const char *prompt) {
    double value = inputDouble(prompt);

    while (value <= 0) {
        printf("Must be positive. Try again\n");
        value = inputDouble(prompt);
    }

    return value;
}

int inputNatural(const char *prompt) {
    int value;
    input(prompt, "%d", &value);

    while (value <= 0) {
        printf("Must be natural. Try again\n");
        input(prompt, "%d", &value);
    }

    return value;
}

int inputNatural0(const char *prompt) {
    int value;
    input(prompt, "%d", &value);

    while (value < 0) {
        printf("Must be natural or zero. Try again\n");
        input(prompt, "%d", &value);
    }

    return value;
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
