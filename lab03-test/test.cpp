#include "C:\Users\nedeo\Desktop\lab03\12\histogram.h"

#include <cassert>

void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_otricala()
{
    double min=0;
    double max=0;
    find_minmax({1,2,3},min,max);
    assert(max == 1);
    assert(min == 3);
}
void test_same()
{
    double min = 0;
    double max = 0;
    find_minmax({3, 3, 3}, min, max);
    assert(min == 3);
    assert(max == 3);
}

void test_ones()
{
    double min = 0;
    double max = 0;
    find_minmax({2}, min, max);
    assert(min == 2);
    assert(max == 2);
}

void test_emptyarr()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
}

int main()
{
    test_positive();
    test_otricala();
    test_same();
    test_ones();
    test_emptyarr();
}
