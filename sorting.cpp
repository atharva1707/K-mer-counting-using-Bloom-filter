#include"helper.hpp"



int main(){

    // to store results
    vector <pair<string,int>> results;

    // read starting n lines from output file of bloom.cpp
    string filename;
    filename = "output.txt";
    FILE *fp = fopen(filename.c_str(), "r");
    if (fp == NULL)
    {
        cout << "File not found\n";
        return 1;
    }
    
    int num_threads = 8;

    // start time
    struct timeval calc;
    double calctime;
    tick(&calc);


# pragma omp parallel for
    for(int i=0 ; i<num_threads; i++){
        // vector for storing lines
        bool file_left = true;
        while(file_left){
            vector<string> lines;
            for(int j=0; j<10000; j++){
                char *line = NULL;
                size_t len = 20;
                getline(&line, &len, fp);
                if(feof(fp)){
                    file_left = false;
                    break;
                }
                if (line == " "){
                    continue;
                }
                if (line == "\n"){
                    continue;
                }
                if (line == ""){
                    continue;
                }
                lines.push_back(line);
            }
            sort(lines.begin(),lines.end());
            string max_kmer = "";
            int max_count = 0; 
            for(int j=0; j<lines.size(); j++){
                int a = 0 ;
                if(lines[j]==" "){
                    continue;
                }
                if(lines[j]=="\n"){
                    continue;
                }
                if(lines[j]==""){
                    continue;
                }
                while(lines[j] == lines[j+a]){
                    a++;
                }
                if(a > max_count){
                    max_count = a;
                    max_kmer = lines[j];
                }
                j+= a - 1 ;
                
            }
            // results.push_back({max_kmer,max_count});
        }

    }

    // end time 
    calctime = tock(&calc);
    cout << "Time: " << calctime << " seconds" << endl;


    // open output files results.txt
    ofstream outfile;
    outfile.open("results.txt");
    for(int i=0; i<results.size();i++){
        outfile << results[i].second << " " << results[i].first;
    }   
}