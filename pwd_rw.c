#include "pdp11.h"

#define MEMSIZE (64*1024)

byte mem[MEMSIZE];

byte b_read(adr a) {
    return mem[a];
}

void b_write(adr a, byte val) {
    mem[a] = val;
}

word w_read(adr a) {
    word w = ((word)mem[a+1]) << 8;
    //printf("w = %x\n", w);
    w = w | mem[a];
    return w;
}

void w_write(adr a, word val) {
    byte val1 = (byte)(val >> 8);
    byte val2 = (byte)(val);
    b_write(a, val2);
    b_write(a+1, val1);
    //printf("%02hhx%02hhx\n", val1, val2);
}

void load_file(FILE * f) {
    adr a, n;
    byte x;
    while (fscanf(f, "%x%x", &a, &n) == 2)
    {
        for (adr i = a; i < a + n; i++) {
            scanf("%hhx", &x);
            b_write(i, x);
        }
    }
}

void mem_dump(adr start, word n) {
    for (adr i = start; i < start + n; i+=2) {
        word w = w_read(i);
        //printf("%04hx\n", w);
        printf("%06ho : %06ho\n", i, w);
    }
}