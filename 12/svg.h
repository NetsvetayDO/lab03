#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <vector>
#include <iostream>
using namespace std;

void svg_rect(double x, double y, double width, double height,string stroke,string fill);

void svg_text(double left, double baseline, string text);

void svg_begin(double width, double height);

void svg_end();

void show_histogram_svg(const vector<size_t>& bins,double min,double max,size_t bin_count);

double fun_wag(double& min,double& max,size_t& bin_count);


#endif // SVG_H_INCLUDED
