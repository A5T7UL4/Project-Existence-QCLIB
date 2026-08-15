#include "header.h"
#include <iostream>
#include <float.h>
#include <cmath>
#include <vector>
#include<complex>
#include<algorithm>
using namespace std;

int main(){
    // defining ket and bra now
    double sqt = sqrt(2);
    double inv = 1.0/sqt;
    vector<vector<pair<double,double>>> a = {
        {{inv,0.0},{inv,0.0}},
        {{inv,0.0},{-inv,0.0}}
    };
    vector<vector<pair<double,double>>> rho = {
        {{0.75,0.0},{0.25,0.0}},
        {{0.25,0.0},{0.25,0.0}}
    };
    print_complex_matrix(mixed_state_evolution(a,rho));
    
    //complexeigenvalue(b,l2);
    
    
}