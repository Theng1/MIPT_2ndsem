#include "test.h"

int main()
{
    //load_file("pdp11_tests/03_arr0/03_arr0.pdp.o");
    load_file("pdp11_tests/simple_tests/com/com.pdp.o");
    //load_file("pdp11_tests/03_arr0_byte/03_arr0_byte.pdp.o");
    //load_file("pdp11_tests/07_putchar/07_putchar.pdp.o");
    //load_file("pdp11_tests/02_sob_mode3/02_sob_mode3.pdp.o");
    //load_file("pdp11_tests/02_sob_byte/02_sob_byte.pdp.o");
    run();
    return 0;
}