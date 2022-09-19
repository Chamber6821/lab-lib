#include <stdlib.h>
#include <stdio.h>
#include "task-menu.h"
#include "input.h"
#include "string-utils.h"

void clear() {
    system("cls");
}

void displayMenu(MenuInfo info) {
    printf("Task Menu:\n");
    printf(" 0. Quit\n");

    for (size_t i = 0; i < info.taskCount; i++)
        printf(" %llu. %s\n", i + 1, info.tasks[i].name);
}

size_t inputTaskNumberToRun(size_t taskCount) {
    return inputIntInRange("Please enter task number to run: ", 0, taskCount);
}

void waitPressEnter() {
    printf("\nPress Enter to exit. ");

    // wait for Enter to be pressed
    // and skip trash line
    free(readString(stdin));
}

void printSeparator(int length) {
    while (length--) putc('-', stdout);
    putc('\n', stdout);
}

void runTask(Task task) {
    int length = printf("Task: %s\n", task.name);
    printSeparator(length - 1);

    task.run();

    waitPressEnter();
}

void startMenu(MenuInfo info) {
    while (1) {
        clear();
        displayMenu(info);
        size_t taskNumber = inputTaskNumberToRun(info.taskCount);

        if (taskNumber == 0) break;

        clear();
        runTask(info.tasks[taskNumber - 1]);
    }

    printf("Bye bye...\n");
    waitPressEnter();
}
