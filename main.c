#include "test.h"

int main()
{
    load_file("pdp11_tests/02_sob/02_sob.pdp.o");
    //load_file("pdp11_tests/02_sob_mode3/02_sob_mode3.pdp.o");
    //load_file("pdp11_tests/02_sob_byte/02_sob_byte.pdp.o");
    run();
    return 0;
}