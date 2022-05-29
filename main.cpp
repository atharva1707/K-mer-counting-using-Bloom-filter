#include "helper.hpp"

int main(int argc, char *argv[])
{

    // input k
    int k = 0;
    if (argc < 2)
    {
        cout << "No k specified\n";
        k = 4;
    }
    else
    {
        k = atoi(argv[1]);
    }

    int chunk = 1 ;
    if (argc >= 3)
    {
        chunk = atoi(argv[2]);
    }

    // init hash map
    int n = pow(4, k);
    int hash_map[n];
    for (int i = 0; i < n; i++)
    {
        hash_map[i] = 0;
    }

    // set start time
    struct timeval calc;
    double calctime;
    tick(&calc);

    // read file
    string filename;
    filename = "test";
    FILE *fp = fopen(filename.c_str(), "r");
    if (fp == NULL)
    {
        cout << "File not found\n";
        return 1;
    }
    char *line = NULL;
    size_t len = 20;
    getline(&line, &len, fp);
    len = strlen(line);
    int len_line = strlen(line);

    // setup read length for each thread
    int num_threads = 8;
    int read = len / num_threads;

#pragma omp parallel for schedule(guided, chunk)
    for (int i = 0; i < num_threads; i++)
    {
        long long window_value = 0;
        long long msd = 1;
        for (int j = 0; j < k; j++)
        {
            window_value *= 4;
            window_value += value(line[i * read + j]);
            msd *= 4;
        }
        msd /= 4;
        while (!compare_and_swap(&hash_map[window_value], hash_map[window_value], hash_map[window_value] + 1))
        {
            ;
        }

        for (int j = i * read + 1; j < min((i + 1) * read, len_line - k + 1); j++)
        {
            window_value -= value(line[j - 1]) * msd;
            window_value *= 4;
            window_value += value(line[j + k - 1]);
            while (!compare_and_swap(&hash_map[window_value], hash_map[window_value], hash_map[window_value] + 1))
            {
                ;
            }
        }

        if (i == num_threads - 1)
        {
            for (int j = min((i + 1) * read, len_line - k + 1); j < len_line - k + 1; j++)
            {
                window_value -= value(line[j - 1]) * msd;
                window_value *= 4;
                window_value += value(line[j + k - 1]);
                while (!compare_and_swap(&hash_map[window_value], hash_map[window_value], hash_map[window_value] + 1))
                {
                    ;
                }
            }
        }
    }


    // copy hash map array to csv file named output.csv
    ofstream outfile("output.csv");
    for (int i = 0; i < n; i++)
    {
        if (hash_map[i] != 0)
        {
            outfile << get_string(i, k) << ',' << hash_map[i] << endl;
        }
    }
    outfile.close();

    // set end time
    calctime = tock(&calc);
    // printf("Calctime: %f\n\n", calctime);
    printf("%f\n", calctime);
}