#include "pdp11.h"


#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_NN 4
#define HAS_XX 8
#define HAS_RL 16
#define HAS_RR 32

typedef struct 
{
    word mask;
    word opcode;
    char * name;
    void (*do_func)();
    char params;
} Commands;

typedef struct {
    word val;  //значение аргумента
    adr adr;  //адрес аргумента
} Arg;

Arg get_ssdd(int byte, word w);
char get_nn (word w);
char get_xx (word w);
int get_r (word w);
void print();
void do_add();
void do_mov();
void do_movb();
void do_sob();
void do_clr();
void do_nothing();
void do_halt();
