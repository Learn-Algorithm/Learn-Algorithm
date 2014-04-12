#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <ctime>
#include <cmath>
#include <time.h>

using namespace std;

#define MAX 500000000

int main() {
   
    srand(time(0));

    const int min = 97;
    const int max = 122;

    FILE* fp;

    if((fp=fopen("inputfile.txt","w"))==NULL){
        printf("cannotopenthefile.\n");
        exit(0);
    }

    for(int i = 0 ; i < MAX ; i++) {
        string word;
        for(int j = 0 ; j < 3 ; j++) {
    	    char temp = min+rand()%(max-min);
            word += temp;
        }
        word+='\n';
        fputs(word.c_str(),fp);
    }

    fclose(fp);

	return 0;
}