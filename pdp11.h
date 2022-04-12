#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MASK 0xff
#define MEMSIZE (64*1024)
#define pc reg[7]

typedef unsigned char byte; //8 bit
typedef unsigned int word;  //16 bit
typedef word adr;           //16 bit
typedef struct 
{
    word mask;
    word opcode;
    char * name;
    void (* func) (void);
} Commands;


byte b_read(adr a);
void b_write(adr a, byte val);
void w_write(adr a, word val);
word w_read(adr a);
void load_file(FILE * f);
void mem_dump(adr start, word n);