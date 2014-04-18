#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

#define NANO  1000000000

int main() {

    struct timespec ts, te;
    double cost;
    clock_gettime(CLOCK_REALTIME, &ts);
        
    ifstream fin("inputfile.txt");
    string word;
    unordered_map<string, int> map;
    while(getline(fin, word)) {
        ++map[word];
    }

    clock_gettime(CLOCK_REALTIME, &te);    
    cost = te.tv_sec - ts.tv_sec + (double)(te.tv_nsec-ts.tv_nsec)/NANO;
    printf("cost: %-15.10f\n", cost);

    return 0;
}