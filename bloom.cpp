#include "helper.hpp"

int main(int argc, char *argv[])
{

    // init k
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

    // init bloom filter of array size 1e9 + 7
    int bloom_size = 1299709;
    bool bloom_array[bloom_size];
    for (int i = 0; i < bloom_size; i++)
    {
        bloom_array[i] = 0;
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




    // open outfile output.txt
    ofstream outfile[8];


    

#pragma omp parallel for schedule(static, chunk)
    for (int i = 0; i < num_threads; i++)
    {
        stringstream sstm ;
        sstm.str("");
        sstm<<"subnode"<<i;
        outfile[i].open(sstm.str());
        string k_mers ;
        for (int j = 0; j < read - k + 1; j++)
        {
            string k_mer = "";
            for (int p = 0; p < k; p++)
            {
                k_mer += line[i * read + j + p];
            }
            int hash_value1 = hash1(k_mer, k);
            int hash_value2 = hash2(k_mer, k);
            int hash_value3 = hash3(k_mer, k);
            int hash_value4 = hash4(k_mer, k);
            if (bloom_array[hash_value1] && bloom_array[hash_value2] && bloom_array[hash_value3] && bloom_array[hash_value4])
            {
                // print the kmer in output.txt file corresponding to the respective thread
                    outfile[i] << k_mer << endl;
            }
            else
            {
                bloom_array[hash_value1] = 1;
                bloom_array[hash_value2] = 1;
                bloom_array[hash_value3] = 1;
                bloom_array[hash_value4] = 1;
            }
        }
        outfile[i] << k_mers << endl;
        outfile[i].close();
    }

    // set end time
    calctime = tock(&calc);
    // printf("Calctime: %f\n\n", calctime);
    printf("%f\n", calctime);

}
