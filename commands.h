#include "pdp11.h"


#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2

typedef struct 
{
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);
    char params;
} Commands;

typedef struct {
    word val;  //значение аргумента
    adr adr;  //адрес аргумента
} Arg;

void print();
void do_add();
void do_mov();
void do_nothing();
void do_halt();
