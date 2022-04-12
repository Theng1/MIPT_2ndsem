#include "pdp11.h"

typedef struct 
{
    word mask;
    word opcode;
    char * name;
    void (* func) (void);
} Commands;

void print();
void do_add();
void do_mov();
void do_nothing();
void do_halt();