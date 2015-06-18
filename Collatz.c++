// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;

#define CACHE_SIZE 1000000
#ifdef CACHE_SIZE
int cache[CACHE_SIZE];
#endif 

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {

    int max = 0;
    int counter = 1;

    if(i > j){  // the case if input is in reverse order
        int temp = j;
        j = i;
        i = temp;
    }

    /*
    Given positive integers, b and e, let m = (e / 2) + 1.
    If b < m, then max_cycle_length(b, e) = max_cycle_length(m, e).
    Discussed this optimization in a quiz in class.
    */
    int halvedNum = (j/2) + 1;
    
    if (i < halvedNum){
       i = halvedNum;
    }

    for(int start = i; start <= j; start++){
        int temp = start;

        while(temp != 1){
            if(temp < 1000000){ //only deal with indices inside the upper bound
                #ifdef CACHE_SIZE
                if(cache[temp] != 0){ //if entry is not empty
                    counter += cache[temp]; //add current counter to prev value
                }
                #endif
            }
            if(temp % 2 == 0){ //even number case
                temp = temp/2;
                counter++;
            } else{ //odd number case
                temp = (temp * 3) + 1;
                counter++;
            }
        }

        #ifdef CACHE_SIZE
        if(cache[temp] == 0){ //if entry not present in cache, then cache it
            cache[temp] = counter;
        }
        #endif

        if(counter > max){
            max = counter;
        }

        counter = 1;
    }

    return max;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
