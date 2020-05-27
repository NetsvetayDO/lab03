#include <iostream>
#include <vector>
#include "svg.h"
using namespace std;

double fun_wag(double& min,double& max,size_t& bin_count)
{

    if(max == min || bin_count==0)
    {
    return 0;
    }
    else
    {
    return (max-min)/bin_count;
    }


}

void max_width(const vector<size_t>& bins,double& maximum)
{
    if (bins.size()==0)
    {
        return;
    }
    else
    {
        for (size_t bin : bins)
        {
            if (bin > maximum)
            {
                maximum = bin;
            }
        }
    }
}

void svg_rect(double x, double y, double width, double height,string stroke = "black",string fill = "black")
{
    cout << "<rect x='"<<x<< "' y='" <<y<<"' width='" <<width <<"' height='" <<height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"'/>";
}

void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline <<"'>" <<text <<"</text>";
}

void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}

void show_histogram_svg(const vector<size_t>& bins,double min,double max,size_t bin_count)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const size_t MAX_ASTERISK=76;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto GRAPH_WIDTH = IMAGE_WIDTH-TEXT_WIDTH;
    double top = 0;
    double maximum=bins[0];
    max_width(bins,maximum);
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
   double wag= fun_wag(min,max,bin_count);
    double border=min+wag;
    size_t max_count=0;
    for(size_t b:bins)
    {
        if(b>max_count)
        {
            max_count=b;
        }
    }

        if (max_count > MAX_ASTERISK)
        {
            const double scaling_multiplier = (double)MAX_ASTERISK / max_count;
            if(max_count*BLOCK_WIDTH/GRAPH_WIDTH>1)
            {
                for (size_t bin : bins)
                {
                    const double new_scaling_multiplier=(double)GRAPH_WIDTH/(max_count*BLOCK_WIDTH*scaling_multiplier);
                    const size_t new_bin_width = (size_t)BLOCK_WIDTH*bin*scaling_multiplier*new_scaling_multiplier;
                    svg_text(TEXT_LEFT+25, top + TEXT_BASELINE, to_string(bin));
                    svg_rect(TEXT_WIDTH+25, top, new_bin_width, BIN_HEIGHT,"lawngreen","#7CFC00");
                    top += BIN_HEIGHT;
                    if(border<max)
                    {
                        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(border));
                        top += BIN_HEIGHT;
                        border=border+wag;
                    }
                }
            }
            else
            {
                for (size_t bin : bins)
                {
                    const double bin_width = BLOCK_WIDTH*bin*scaling_multiplier;
                    svg_text(TEXT_LEFT+25, top + TEXT_BASELINE, to_string(bin));
                    svg_rect(TEXT_WIDTH+25, top,bin_width, BIN_HEIGHT,"lawngreen","#7CFC00");
                    top += BIN_HEIGHT;
                    if(border<max)
                    {
                        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(border));
                        top += BIN_HEIGHT;
                        border=border+wag;
                    }
                }
            }
        }
        else
        {
            if(max_count*BLOCK_WIDTH/GRAPH_WIDTH>1)
            {
                for (size_t bin : bins)
                {
                    const double new_scaling_multiplier=(double)GRAPH_WIDTH/(max_count*BLOCK_WIDTH);
                    const size_t new_bin_width = (size_t)BLOCK_WIDTH*bin*new_scaling_multiplier;
                    svg_text(TEXT_LEFT+25, top + TEXT_BASELINE, to_string(bin));
                    svg_rect(TEXT_WIDTH+25, top,new_bin_width, BIN_HEIGHT,"lawngreen","#7CFC00");
                    top += BIN_HEIGHT;
                    if(border<max)
                    {
                        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(border));
                        top += BIN_HEIGHT;
                        border=border+wag;
                    }
                }
            }
            else
            {
                for (size_t bin : bins)
                {
                    const double bin_width = BLOCK_WIDTH * bin;
                    svg_text(TEXT_LEFT+25, top + TEXT_BASELINE, to_string(bin));
                    svg_rect(TEXT_WIDTH+25, top,bin_width, BIN_HEIGHT,"lawngreen","#7CFC00");
                    top += BIN_HEIGHT;
                    if(border<max)
                    {
                        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(border));
                        top += BIN_HEIGHT;
                        border=border+wag;
                    }
                }
            }
        }
        svg_end();
}
