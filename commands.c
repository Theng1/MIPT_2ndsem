#include "pdp11.h"
#include "commands.h"

byte mem[MEMSIZE];
word reg[8];
Arg ss, dd;
word nn, r;
byte xx;

void print() {
    for (int i = 0; i < 8; i++){
        printf("R%d=%06o\n", i, reg[i]);
    }
    printf("\n");
}

void do_add() {
}

void do_mov() {
}

void do_nothing() {
    print();
}

void do_halt() {
    printf("\n");
    print();
    printf("THE END!!!\n");
    exit(0);
}