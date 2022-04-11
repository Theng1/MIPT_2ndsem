#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MASK 0xff

typedef unsigned char byte; //8 bit
typedef unsigned int word;  //16 bit
typedef word adr;           //16 bit

void b_read(adr a);
void b_write(adr a, byte val);
void w_write(adr a, word val);
void w_read(adr a);
void load_file(const char * filename);
void mem_dump(adr start, word n);