#include "test.h"

byte mem[MEMSIZE];
word reg[8];
Arg ss, dd;
word nn, r;

Commands cmd[] = {
    {0177777, 0000000, "halt", do_halt, NO_PARAMS},
    {0170000, 0010000, "mov", do_mov, HAS_SS | HAS_DD},
    {0170000, 0110000, "movb", do_movb, HAS_SS | HAS_DD},
    {0170000, 0060000, "add", do_add, HAS_SS | HAS_DD},
	{0177000, 0077000, "sob", do_sob, HAS_NN | HAS_RL},
	{0177700, 0005000, "clr", do_clr, HAS_DD},
    {0170000, 0000000, "unknown", do_nothing, NO_PARAMS},
};


void run() {
    pc = 01000;
    while (1)
    {
        word w = w_read(pc);
        printf("%06o %06o: ", pc, w);
        pc += 2;
        
        for (int i = 0; ; i++) {
            Commands x = cmd[i];
            if ((w & x.mask) == x.opcode) {
                printf("%s ", x.name);
                int byte = (w >> 15) & 1;
                if (x.params & HAS_RL)
                    r = get_r(w >> 6) & 7;
                if (x.params & HAS_RR)
                    r = get_r(w);
                if (x.params & HAS_SS)
                    ss = get_ssdd(byte, w >> 6);
                if (x.params & HAS_DD)
                    dd = get_ssdd(byte, w);
                if (x.params & HAS_NN)
                {   
                    nn = get_nn(w);
                    printf("%o ", pc - 2 * nn);
                }
                x.do_func();
                printf("\n");
                reg_print();
                //print();
                break;
            }
        }
    }
}