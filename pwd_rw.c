#include "pdp11.h"

byte mem[MEMSIZE];
word reg[8];

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
    if (a < 8) {
        reg[a] = val;
    } else {
        mem[a] = val & MASK;
        mem[a+1] = val >> 8 & MASK;
    }
}

void load_file(const char * filename) {
    FILE * f = fopen(filename, "r");
    adr a, n;
    byte x;
    while (fscanf(f, "%x%x", &a, &n) == 2)
    {
        for (adr i = a; i < a + n; i++) {
            fscanf(f, "%hhx", &x);
            b_write(i, x);
        }
    }
    fclose(f);
}

void mem_dump(adr start, word n) {
    for (adr i = start; i < start + n; i+=2) {
        word w = w_read(i);
        //printf("%04hx\n", w);
        printf("%06ho : %06ho\n", i, w);
    }
}
void reg_print()
{
    for (int i = 0; i < 8; i++)
        printf("r%d:%o ", i, reg[i]);
    printf("\n");
}