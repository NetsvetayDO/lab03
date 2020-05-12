#include "C:\Users\nedeo\Desktop\прога\lab03\12\histogram.h"
#include "C:\Users\nedeo\Desktop\прога\lab03\12\svg.h"
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
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
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


void test_1()
{
    double min=2;
    double max=4;
    size_t bin_count=2;
    assert( fun_wag(min,max,bin_count) == 1.0);
}

void test_2()
{
    double min=2;
    double max=10;
    size_t bin_count=4;

    assert( fun_wag(min,max,bin_count) == 2.0);
}

void test_3()
{

    double min=2;
    double max=2;
    size_t bin_count=2;
    assert(fun_wag(min,max,bin_count) == 0);
}

void test_4()
{
    double min=2;
    double max=2;
    size_t bin_count=0;
    assert( fun_wag(min,max,bin_count) == 0);
}


int main()
{
    test_positive();
    test_otricala();
    test_same();
    test_ones();
    test_emptyarr();
    test_1();
    test_2();
    test_3();
    test_4();
}
