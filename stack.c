#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stack.h"

Car* push(Car *top, const char *reg, const char *owner) {
    Car *newCar = (Car*)malloc(sizeof(Car));
    if (!newCar) return top;
    strcpy(newCar->reg, reg);
    strcpy(newCar->owner, owner);
    newCar->arrival = time(NULL);
    newCar->next = top;
    return newCar;
}

Car* pop(Car *top, Car **out) {
    if (!top) {
        *out = NULL;
        return NULL;
    }
    *out = top;
    Car *newTop = top->next;
    return newTop;
}

Car* removeByReg(Car *top, const char *reg, int *found) {
    *found = 0;
    Car *current = top;
    Car *prev = NULL;
    while (current) {
        if (strcmp(current->reg, reg) == 0) {
            *found = 1;
            if (prev) {
                prev->next = current->next;
            } else {
                top = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
    return top;
}

void displayStack(Car *top) {
    Car *current = top;
    if (!current) {
        puts("Stack is empty.");
        return;
    }
    while (current) {
        printf("Reg: %s, Owner: %s, Arrival: %s", current->reg, current->owner, ctime(&current->arrival));
        current = current->next;
    }
}

void saveToFile(Car *top, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return;
    Car *current = top;
    while (current) {
        fprintf(file, "%s %s %ld\n", current->reg, current->owner, current->arrival);
        current = current->next;
    }
    fclose(file);
}

Car* loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    Car *top = NULL;
    char reg[REG_LEN], owner[NAME_LEN];
    time_t arrival;
    while (fscanf(file, "%s %s %ld", reg, owner, &arrival) == 3) {
        Car *newCar = (Car*)malloc(sizeof(Car));
        if (!newCar) break;
        strcpy(newCar->reg, reg);
        strcpy(newCar->owner, owner);
        newCar->arrival = arrival;
        newCar->next = top;
        top = newCar;
    }
    fclose(file);
    return top;
}

void freeAll(Car *top) {
    Car *current = top;
    while (current) {
        Car *temp = current;
        current = current->next;
        free(temp);
    }
}
