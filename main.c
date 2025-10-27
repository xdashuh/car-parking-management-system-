#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int main() {
    Car *top = loadFromFile("parking_state.txt");
    int choice;
    while (1) {
        printf("\n1.Park  2.Pop  3.Remove by Reg  4.Display  5.Save  6.Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar();
        if (choice == 1) {
            char reg[REG_LEN], owner[NAME_LEN];
            printf("Reg: "); fgets(reg, sizeof(reg), stdin); reg[strcspn(reg,"\n")] = 0;
            printf("Owner: "); fgets(owner, sizeof(owner), stdin); owner[strcspn(owner,"\n")] = 0;
            top = push(top, reg, owner);
            puts("Parked.");
        } else if (choice == 2) {
            Car *out=NULL; top = pop(top, &out);
            if (!out) puts("Empty."); else { /* calc fee + print */ free(out); }
        } else if (choice == 3) {
            char reg[REG_LEN]; int found=0;
            printf("Reg to remove: "); fgets(reg,sizeof(reg),stdin); reg[strcspn(reg,"\n")] = 0;
            top = removeByReg(top, reg, &found);
            if (!found) puts("Not found.");
        } else if (choice == 4) {
            displayStack(top);
        } else if (choice == 5) {
            saveToFile(top, "parking_state.txt");
        } else if (choice == 6) {
            saveToFile(top, "parking_state.txt");
            freeAll(top); puts("Bye!"); break;
        }
    }
    return 0;
}

