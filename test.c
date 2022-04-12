#include "test.h"
#include "pdp11.h"
#include "commands.h"

byte mem[MEMSIZE];
word reg[8];


void run() {
    pc = 01000;
   while (1)
   {
       word w = w_read(pc);
       printf("%06o %06o: ", pc, w);
       pc += 2;
       if (w == 0) {
           printf("halt ");
           do_halt();
       }
       else if ((w & 0xF000) == 0010000)
       {
           printf("mov ");
           do_mov();
       }
   }
}