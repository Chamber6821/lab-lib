#pragma once

#include <stdio.h>
#include <stdbool.h>

char *concat(const char *left, const char *right);

char *readString(FILE *in);

char *lightTrimEnd(char *str);

bool isEOL(int ch);
