#include <stdlib.h>
#include <stdio.h>
#include "task-menu.h"
#include "input.h"

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
    return inputNatural0("Please enter task number to run: ");
}

void waitPressEnter() {
    printf("\nPress Enter to exit. ");
    getchar();
}

void startMenu(MenuInfo info) {
    while (1) {
        clear();
        displayMenu(info);
        size_t taskNumber = inputTaskNumberToRun(info.taskCount);

        if (taskNumber == 0) break;

        clear();
        info.tasks[taskNumber - 1].run();

        waitPressEnter();
    }

    printf("Bye bye...\n");
    waitPressEnter();
}
