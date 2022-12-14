#include "task-menu.h"
#include "input.h"
#include "string-utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void clear() {
    system("cls");
}

void displayMenu(MenuInfo info) {
    printf("Task Menu:\n");
    printf(" 0. Quit\n");

    for (size_t i = 0; i < info.taskCount; i++) {
        printf(" %llu. %s\n", i + 1, info.tasks[i].name);
    }
}

int inputTaskNumberToRun(int taskCount) {
    return inputIntInRange("Please enter task number to run: ",
                           0, taskCount);
}

void waitPressEnter() {
    printf("\nPress Enter to exit. ");

    // wait for Enter to be pressed
    // and skip trash line
    while (!isEOL(getchar()));
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
    while (true) {
        clear();
        displayMenu(info);
        int taskNumber = inputTaskNumberToRun(info.taskCount);

        if (taskNumber == 0) break;

        clear();
        runTask(info.tasks[taskNumber - 1]);
    }

    printf("Bye bye...\n");
    waitPressEnter();
}
