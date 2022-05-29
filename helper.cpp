#include "helper.hpp"
#define MOD 1299709

int compare_and_swap(int *var, int exp, int new_value)
{
    int old_value = *var;
    if (*var == exp)
    {
        *var = new_value;
        return 1;
    }
    return 0;
}

void tick(struct timeval *t)
{
    gettimeofday(t, NULL);
}

double tock(struct timeval *t)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (double)(now.tv_sec - t->tv_sec) +
           ((double)(now.tv_usec - t->tv_usec) / 1000000.);
}

string get_string(int i, int k)
{
    string s = "";
    while (k--)
    {
        int m = i % 4;
        i /= 4;
        switch (m)
        {
        case 0:
            s = "A" + s;
            break;
        case 1:
            s = "C" + s;
            break;
        case 2:
            s = "G" + s;
            break;
        case 3:
            s = "T" + s;
            break;
        }
    }
    return s;
}

int value(char a)
{
    switch (a)
    {
    case 'A':
        return 0;
    case 'C':
        return 1;
    case 'G':
        return 2;
    case 'T':
        return 3;
    }
    return -1;
}



long long hash1(string s, int k)
{
    long long hash = 0;
    for (int i = 0; i < k; i++)
    {
        hash *= 4;
        hash += value(s[i]);
        hash %= MOD;
    }
    return hash;
}


long long hash2(string s, int k)
{
    long long hash = 0;
    long long mul  = 1;
    for (int i = 0; i < k; i++)
    {
        hash *= 4;
        hash += value(s[i])*mul;
        hash %= MOD;
        mul *= 5;
        mul %= MOD;
    }
    return hash;
}


long long hash3(string s, int k)
{
    long long hash = 0;
    long long mul  = 1;
    for (int i = 0; i < k; i++)
    {
        hash *= 4;
        hash += value(s[i])*mul;
        hash %= MOD;
        mul *= 7;
        mul %= MOD;
    }
    return hash;
}

long long hash4(string s, int k)
{
    long long hash = 0;
    long long mul  = 1;
    for (int i = 0; i < k; i++)
    {
        hash *= 4;
        hash += value(s[i])*mul;
        hash %= MOD;
        mul *= 11;
        mul %= MOD;
    }
    return hash;
}