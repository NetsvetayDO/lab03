#include <curl/curl.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "histogram.h"
#include "svg.h"
#include <windows.h>
#include <string.h>
#include <sstream>
using namespace std;



struct Options
{
    string fill;
    bool fill_correct;
    bool guide;
    char* url;
};
Options parse_args(int argc, char** argv)
{
    Options opt;
    opt.url=0;
    opt.fill_correct=false;
    opt.guide = false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {

            if(string(argv[i]) == "-fill")
            {
                if(i+1<argc)
                {
                    opt.fill = string(argv[i+1]);
                    if (opt.fill.size())
                    {
                        opt.fill_correct=true;
                        i++;
                    }
                    else
                        {
                            opt.guide=true;
                        }
                }

                else
                {
                    opt.guide = true;
                }
            }
        }
        else
        {
            opt.url=argv[i];
        }
    }
    return opt;
}



vector<double> input_numbers(istream& in, const size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }

    return result;
}

Input read_input(istream& in, bool prompt) {
    Input input;
    size_t number_count;
    if (prompt)
    {
        cerr << "Enter number count: ";
         in >> number_count;

         cerr << "Enter numbers: ";
        input.numbers = input_numbers(in, number_count);

        cerr << "Enter column count: ";
        in >> input.bin_count;

    }

else
{
    in >> number_count;
    input.numbers = input_numbers(in, number_count);
    in >> input.bin_count;
}

    return input;
}

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}


Input download(const string& address,const Options &opt) {
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            cout << curl_easy_strerror(res) << endl;
            exit(1);
        }
        curl_easy_cleanup(curl);
    }
   return read_input(buffer, false);
}


string make_info_text()
{
    stringstream buffer;
      DWORD info = GetVersion();
     DWORD mask = 0x0000ffff;
     DWORD build;
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & 0xff;
    DWORD version_minor = version >> 8;
    //printf("M_version10 = %lu\n",version_major);
    //printf("M_version16 = %08lx\n",version_major);
    //printf("m_version10 = %lu\n",version_minor);
    //printf("m_version16 = %08lx\n",version_minor);
    if ((info & 0x80000000) == 0)
    {
    build = platform;
    }
    else printf("minor_bit = %u",1);
     //printf("Windows v%lu.%lu (build %lu)\n",version_major,version_minor,build);
    char system_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD Size = sizeof(system_name);
    GetComputerNameA(system_name, &Size);
   //printf("System name: %s\n", system_name);
   buffer << "Windows v" << version_major << "." << version_minor << " (build " << build << ")" << " " << "Computer name: " << system_name;
    return buffer.str();
}

int main(int argc, char* argv[]) {
    string info = make_info_text();
    Input input;

    Options opt=parse_args(argc,argv);
    if (opt.guide)
    {
        cerr<<"Error";
        return 1;
    }
   if (opt.url)
    {
        input = download(opt.url,opt);
    }
    else
    {
        input = read_input(cin, true);
    }

   /*
     if (argc > 1)
    {
        input = download(argv[1]);
    }
    else
        {
        input = read_input(cin, true);
        }
    */

    const auto bins = make_histogram(input);
    double min,max;
    find_minmax(input.numbers,min,max);
    show_histogram_svg(bins,min,max,input.bin_count, opt.fill);
    return 0;

}
