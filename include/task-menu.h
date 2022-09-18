#pragma once

#include <stdlib.h>

typedef struct {
    const char *name;
    const void (*run)(void);
} Task;

typedef struct {
    const Task *tasks;
    const size_t taskCount;
} MenuInfo;

void startMenu(MenuInfo info);
