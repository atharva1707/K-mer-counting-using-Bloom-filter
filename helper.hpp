#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>
#include <omp.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;



int compare_and_swap(int *var, int exp, int new_value);
void tick(struct timeval *t);
double tock(struct timeval *t);
string get_string(int i, int k);
int value(char a);
long long hash1(string s, int k);
long long hash2(string s, int k);
long long hash3(string s, int k);
long long hash4(string s, int k);