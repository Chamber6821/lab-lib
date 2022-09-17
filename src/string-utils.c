#include "string-utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *concat(const char *left, const char *right) {
    const size_t size = strlen(left) + strlen(right) + 1;

    char *buffer = malloc(size);
    if (buffer == NULL) exit(2);

    sprintf_s(buffer, size, "%s%s", left, right);
    return buffer;
}

char *readString(FILE *in) {
    size_t size = 16;
    size_t read = 0;

    char *buffer = malloc(size * sizeof(*buffer));
    if (buffer == NULL) exit(1);

    for (int ch = fgetc(in); !(ch == EOF || ch == '\n'); ch = fgetc(in)) {
        buffer[read++] = (char) ch;

        if (read >= size) {
            size *= 2;

            char *newBuffer = realloc(buffer, sizeof(*buffer) * size);
            if (newBuffer == NULL) exit(1);
            buffer = newBuffer;
        }
    }
    buffer[read++] = 0;

    char *clippedBuffer = realloc(buffer, sizeof(*buffer) * size);
    if (clippedBuffer == NULL) free(buffer);

    return clippedBuffer;
}

char *lightTrimEnd(char *str) {
    if (str == NULL) return NULL;

    const size_t length = strlen(str);

    size_t i = length; // str[length] == '\0'
    while (i > 0 && isspace(str[i - 1])) i--;
    str[i] = 0;

    return str;
}
