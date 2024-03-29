#include "pdp11.h"

byte mem[MEMSIZE];
word reg[8];

byte b_read(adr a) {
    if (a < 8) {
        return reg[a];
    } else {
        return mem[a];
    }
}

void b_write(adr a, byte val) {
    if (a < 8) {
        if ((val >> 7) & 1) {
            reg[a] = (val & 0xFF) | 0xFF00;
        } else {
            reg[a] = val & 0xFF;
        }
    } else {
        mem[a] = val;
    }
}

word w_read(adr a) {
    word w;
    if (a < 8) {
        w = (reg[a + 1] << 8) | reg[a];
    } else {
        w = (mem[a + 1] << 8) | mem[a];
    }
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
    if (f == NULL)
    {
        perror(filename);
        exit(0);
    }
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
        printf("r%d:%06o ", i, reg[i]);
    printf("\n");
}