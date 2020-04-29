#include "C:\Users\nedeo\Desktop\lab03\12\svg.h"
#include <cassert>
#include <string.h>


void test_1()
{
double maximum = 0;
max_height({1, 2, 3}, maximum);
assert(maximum == 3);
}
void test_2() {
double maximum = 0;
max_height({3, 3, 3}, maximum);
assert(maximum == 3);
}

int main()
{
test_1();
test_2();
}
