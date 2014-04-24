#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define MAX 500000000

int main() {

    srand(time(0));

    const int min = 97;
    const int max = 122;

    ofstream fout("inputfile.txt");

    for(int i = 0 ; i < MAX ; i++) {
        string word;
        for(int j = 0 ; j < 3 ; j++) {
            char temp = min+rand()%(max-min);
            word += temp;
        }
        fout << word << endl;
    }


    return 0;
}
