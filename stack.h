#ifndef STACK_H
#define STACK_H
#include <time.h>

#define REG_LEN 20
#define NAME_LEN 50

typedef struct Car {
    char reg[REG_LEN];
    char owner[NAME_LEN];
    time_t arrival;
    struct Car *next;
} Car;

Car* push(Car *top, const char *reg, const char *owner);
Car* pop(Car *top, Car **out);
Car* removeByReg(Car *top, const char *reg, int *found);
void displayStack(Car *top);
void saveToFile(Car *top, const char *filename);
Car* loadFromFile(const char *filename);
void freeAll(Car *top);

#endif
