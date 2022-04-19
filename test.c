#include "test.h"

byte mem[MEMSIZE];
word reg[8];

Commands cmd[] = {
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
    {0000000, 0000000, "unknown", do_nothing, NO_PARAMS},
    {0111111, 0000000, "halt", do_halt, NO_PARAMS},
};


void run() {
    pc = 01000;
    while (1)
    {
        word w = w_read(pc);
        printf("%06o %06o: ", pc, w);
        pc += 2;
        if (w == 0) {
            printf("halt\n");
            do_halt();
        }
        for (int i = 0; ; i++) {
            Commands x = cmd[i];
            if ((w & x.mask) == x.opcode) {
                printf("%s ", x.name);
                //x.do_func();
                printf("\n");
                break;
            }
        }
        
    }
}