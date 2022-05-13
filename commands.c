#include "commands.h"

extern Arg ss, dd;
extern byte mem[MEMSIZE];
extern word reg[8];
extern Arg ss, dd;
extern word nn, r;
extern signed char xx;
extern int b;
extern char Z, N, V, C;

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
        if (byte && r < 6)
            reg[r] ++;
        else
            reg[r] += 2;    // +2 word, r6, r7
        if (r == 7)
            printf("#%o ", arg.val);
        else
            printf("(R%d)+ ", r);
        //printf("%06o  ", arg.val);
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
        if (byte && r < 6)
            reg[r] --;
        else
            reg[r] -= 2;    // -2 word, r6, r7
        arg.adr = reg[r];
        if (byte == 0)
            arg.val = w_read(arg.adr);
        else
            arg.val = b_read(arg.adr);
        printf("-(R%d)", r);
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

void set_NZ(word w) {
    if (w == 0) {
        Z = 1;
        N = 0;
    } else if (w < 0) {
        N = 1;
        Z = 0;
    } else {
        N = 0;
        Z = 0;
    }
}
void set_C(int x) {
    if ((x >> 16) && (x > 0))
        C = 1;
    else
        C = 0;
}

void NZVC_print() {
    printf("%c", N ? 'n' : '-');
    printf("%c", Z ? 'z' : '-');
    printf("%c", V ? 'v' : '-');
    printf("%c", C ? 'c' : '-');
    printf(" ");
}

void do_add() {
    word res = (dd.val + ss.val) & 0xFFFF;
    w_write(dd.adr, res);
    set_NZ(res);
}

void do_mov() {
    w_write(dd.adr, (ss.val & 0xFFFF));
    set_NZ(ss.val);
}
void do_movb() {
    b_write(dd.adr, ss.val);
    set_NZ(ss.val);
}
void do_sob() {
    //reg[r] --;
    // printf("nn = %o ", nn);
    if (--reg[r] != 0)
        pc = pc - (2 * nn);
    //printf("%06o ", pc);

}
void do_clr() {
    w_write(dd.adr, 0);
}

void do_tst() {
    unsigned int val = w_read(dd.adr);
    set_NZ(w_read(dd.adr));
    //printf("dd.a = %06o val = %06o b = %d ss.val = %06o", dd.adr, val, b, ss.val);

}

void do_tstb() {
    unsigned int val = b_read(dd.adr);
    set_NZ(b_read(dd.adr));
    //printf("dd.a = %06o val = %06o b = %d ss.val = %06o", dd.adr, val, b, ss.val);
}

void do_cmp() {
    w_write(dd.adr, ss.val - dd.val);
    set_NZ(ss.val - dd.val);
}

void do_cmpb() {
    b_write(dd.adr, ss.val - dd.val);
    set_NZ(ss.val - dd.val);
}

void do_br() {
    pc = pc + 2 * xx;
}

void do_beq() {
    if(Z)
        do_br();
}

void do_bne() {
    if(Z == 0)
        do_br();
}

void do_bmi() {
    if(N)
        do_br();
}

void do_bpl() {
    if(N == 0)
        do_br();
}

void do_jmp() {
	pc = dd.val;
}

void do_nothing() {
    exit(0);
}

void do_halt() {
    printf("\n");
    reg_print();
    printf("THE END!!!\n");
    exit(0);
}
