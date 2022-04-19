#include "pdp11.h"
#include "commands.h"

byte mem[MEMSIZE];
word reg[8];
Arg ss, dd;
word nn, r;
byte xx;

Arg get_ssdd(int byte, word w) {
    r = w & 7;
    int mode = (w >> 3) & 7;
    Arg arg;
    switch (mode) {
    case 0 :
        arg.adr = r;
        arg.val = reg[r];
        printf("R%d ", r);
        break;
    case 1:
        arg.adr = reg[r];
        if (byte == 0)
            arg.val = w_read(arg.adr);
        else
            arg.val = b_read(arg.adr);
        printf("(R%d) ", r);
        break;
    case 2:
        arg.adr = reg[r];
        if (byte == 0)
            arg.val = w_read(arg.adr);
        else
            arg.val = b_read(arg.adr);
        if (r < 6)
            reg[r] ++;
        else
            reg[r] += 2;    // +2 word, r6, r7
        if (r == 7)
            printf("#%o ", arg.val);
        else
            printf("(R%d)+ ", r);
        break;
    case 3:
        arg.adr = reg[r];
        reg[r] += 2;
        arg.adr = w_read(arg.adr);
        if (byte == 0)
            arg.val = w_read(arg.adr);
        else
            arg.val  = b_read(arg.adr);
        if (r == 7)
            printf("@#%o ", arg.adr );
        else
            printf("@(R%d) ", r);
        break;
    case 4:
        reg[r] -= 2;
        arg.adr = reg[r];
        if (byte == 0)
            arg.val = w_read(arg.adr);
        else
            arg.val = b_read(arg.adr);
        printf("-(R%d)", r);
        break;
    case 5:
        reg[r] -= 2;
        arg.adr = reg[r];
        arg.adr = w_read(arg.adr);
        if (byte == 0)
            arg.val = w_read(arg.adr);
        else
            arg.val = b_read(arg.adr);
        printf("@-(R%d) ", r);
        break;
    case 6:
        nn = w_read(pc);
        pc += 2;
        arg.adr = reg[r] + nn;
        // arg.adr = w_read(arg.adr);
        if (byte == 0)
            arg.val =  w_read(arg.adr);
        else
            arg.val = b_read(arg.adr);
        if (r == 7)
            printf("%o ", arg.adr);
        else
            printf("%o(R%d)", nn, r);
        break;
    case 7:
        nn = w_read(pc);
        pc += 2;
        arg.adr = reg[r] + nn;
        arg.adr = w_read(arg.adr);
        if (byte == 0) {
            arg.adr = w_read(arg.adr);
            arg.val = w_read(arg.adr);
        } else {
            arg.adr = b_read(arg.adr);
            arg.val = b_read(arg.adr);
        }
        if (r == 7)
            printf("@%o ", nn);
        else
            printf("@%o(R%d) ", nn, r);
        break;
    }
    return arg;
}

char get_nn (word w) {
    return w & 077;
}

char get_xx (word w) {
    return (byte)(w & 0xFF);
}

int get_r (word w) {
    r = w & 07;
    printf("R%d ", r);
    return r;
}

void print() {
    for (int i = 0; i < 8; i++){
        printf("R%d=%06o\n", i, reg[i]);
    }
    printf("\n");
}

void do_add() {
    w_write(dd.adr, (dd.val + ss.val) & 0xFFFF);
}

void do_mov() {
    w_write(dd.adr, (ss.val & 0xFFFF));
}
void do_movb() {

}
void do_sob() {

}
void do_clr() {

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