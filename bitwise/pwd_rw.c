#include <stdio.h>

#define MEMSIZE (64*1024)

typedef unsigned char byte;     // 8 bit
typedef unsigned int word;      // 16 bit 

typedef word adr;               // 16 bit

byte mem[MEMSIZE];

byte b_read  (adr a);            // читает из "старой памяти" mem байт с "адресом" a.
void b_write (adr a, byte val);  // пишет значение val в "старую память" mem в байт с "адресом" a.
word w_read  (adr a);            // читает из "старой памяти" mem слово с "адресом" a.
void w_write (adr a, word val);  // пишет значение val в "старую память" mem в слово с "адресом" a.

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

int main()
{
    byte b0 = 0x0a;
    b_write(2, b0);
    byte bres = b_read(2);
    printf("%02hhx = %02hhx\n", b0, bres);

    adr a = 4;
    byte b1 = 0xcb;
    b0 = 0x0a;
    word w = 0x0b0a;
    b_write(a, b0);
    b_write(a+1, b1);
    word wres = w_read(a);
    printf("%04hx=%02hhx%02hhx\n", wres, b1, b0);
    w_write(a, w);
    return 0;
}
