#include <iostream>
#include <vector>
#include <string>
#include<curl/curl.h>
#include "histogram.h"
#include "svg.h"
using namespace std;

vector<double> input_numbers(istream& in, const size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }

    return result;
}

Input
read_input(istream& in, bool prompt)
{
    Input data;
    size_t number_count;

    if (prompt)
    {
        cerr << "Enter number count: ";
        in >> number_count;

        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, number_count);

        cerr << "Enter column count: ";
        in >> data.bin_count;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >> data.bin_count;
    }


    return data;
}

int main(int argc, char* argv[])
{

    if (argc > 1)
    {
        CURL *curl = curl_easy_init();
        if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            res = CURLE_FAILED_INIT;
            if (res != CURLE_OK)
            {
                cout << curl_easy_strerror(res) << endl;
                exit(1);
            }
            curl_easy_cleanup(curl);
        }
        return 0;
    }

    curl_global_init(CURL_GLOBAL_ALL);

    // Ââîä äàííûõ
    Input data = read_input(cin, true);

    // Îáðàáîòêà äàííûõ
    const auto bins = make_histogram(data);

    // Âûâîä äàííûõ
    show_histogram_svg(bins);
    //show_histogram_text(bins);

    return 0;
}
