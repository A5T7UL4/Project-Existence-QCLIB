//header.h
#include <iostream>
#include <vector>
#include <float.h>
#include <cmath>
#include<complex>
#include<algorithm>
using namespace std;

#ifndef HEADER_H
#define HEADER_H

//void initiator();
bool are_equal_scalars(pair<double,double>  a,pair<double,double>  b,double eps);
pair<double,double> Multiply2scalars(pair<double,double>  a,pair<double,double>  b);
double abs_of_scalar(pair<double,double> a);
pair<double,double> conjugate_of_scalar(pair<double,double> a);
pair<double,double> divide(pair<double,double> a,pair<double,double> b);
pair<double,double> add2scalars(pair<double,double> a,pair<double,double> b);
pair<double,double> subtract(pair<double,double> a,pair<double,double> b);
pair<double,double> complex_sqrt(pair<double,double> a);
pair<double,double> inner_product(vector<vector<pair<double,double>>>a,vector<vector<pair<double,double>>> b);
vector<vector<pair<double,double>>> outer_product(vector<vector<pair<double,double>>> a,vector<vector<pair<double,double>>> b);
vector<vector<pair<double,double>>> tensor_product(vector<vector<pair<double,double>>> a,vector<vector<pair<double,double>>> b);
pair<double,double> trace(vector<vector<pair<double,double>>> a);
vector<vector<pair<double,double>>> MatrixMultiplication(vector<vector<pair<double,double>>>  a,vector<vector<pair<double,double>>>  b);
vector<vector<pair<double,double>>> MatrixAddition(vector<vector<pair<double,double>>>  a,vector<vector<pair<double,double>>>  b);
vector<vector<pair<double,double>>> Scalar2matrix(pair<double,double>   scalar,vector<vector<pair<double,double>>>   a);
bool are_equal_matrices(vector<vector<pair<double,double>>>   A,vector<vector<pair<double,double>>>   B,double eps);
vector<vector<pair<double,double>>> ConjugateTranspose(vector<vector<pair<double,double>>>   A);
bool isUnitary(vector<vector<pair<double,double>>>   U);
bool isMixed(vector<vector<pair<double,double>>>  a);
void print_complex_matrix(vector<vector<pair<double,double>>>  a);

void hessenberg(vector<vector<pair<double,double>>> & A);
void implicitQrStep(vector<vector<pair<double,double>>>& A, int k_start, int ien, bool exceptional);
double sumabs(pair<double,double>   a);
void complexeigenvalue(vector<vector<pair<double,double>>> & A,vector<pair<double,double>> & lamda);

bool isDensityMatrix(vector<vector<pair<double,double>>>  a);
vector<vector<pair<double,double>>> identity(int n);
vector<vector<pair<double,double>>> Projector(vector<vector<pair<double,double>>>   A,pair<double,double>   eigenval,vector<pair<double,double>>   lamda);

vector<vector<pair<double,double>>> pure_state_evolution(vector<vector<pair<double,double>>>   U,vector<vector<pair<double,double>>>   psi);
vector<vector<pair<double,double>>> mixed_state_evolution(vector<vector<pair<double,double>>>   U, vector<vector<pair<double,double>>>   rho);

vector<vector<pair<double,double>>> pure_state_measurement(vector<vector<pair<double,double>>>   M_m,vector<vector<pair<double,double>>>   psi,double   p_m);
vector<vector<pair<double,double>>> mixed_state_measurement(vector<vector<pair<double,double>>>   M_m,vector<vector<pair<double,double>>>   rho,double p_m);

vector<vector<pair<double,double>>> state_of_composite_system(vector<vector<vector<pair<double,double>>>>   rho );
vector<vector<pair<double,double>>> partial_trace(vector<vector<pair<double,double>>>   A,vector<int>   partial_system);


#endif