#include "C:\Users\nedeo\Desktop\lab03\12\svg.h"
#include <cassert>


void test_1()
{
double wag=fun_wag(2,4,2);
assert(wag == 1);
}

void test_2()
{
double wag=fun_wag(2,10,4);
assert(wag == 2 );
}

void test_3()
{
double wag=fun_wag(2,2,2);
assert(wag==0);
}

void test_4()
{
    double wag=fun_wag(2,2,0);
    assert(wag==0);
}

int main()
{
test_1();
test_2();
test_3();
test_4();
}
