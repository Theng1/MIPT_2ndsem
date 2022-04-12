#include "pdp11.h"

byte mem[MEMSIZE];
word reg[8];

Commands cmd[] = {
    {0170000, 0010000, "mov", do_mov},
    {0170000, 0060000, "add", do_add},
};
void print() {
    for (int x = 0; x < 8; x++){
        printf("R%d=%06o", x, reg[x]);
    }
    printf("\n");
}

void do_add() {

}

void do_mov() {

}

void do_nothing() {

}

void do_halt() {
    printf("\n");
    print();
    printf("THE END!!!\n");
    exit(0);
}