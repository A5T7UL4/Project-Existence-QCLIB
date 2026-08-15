//Source code file
#include "header.h"
#include <iostream>
#include <float.h>
#include <cmath>
#include <vector>
#include<complex>
#include<iomanip>
#include<algorithm>

using namespace std;

// Very basic complex number operations to be used later
bool are_equal_scalars(pair<double,double> a,pair<double,double> b,double eps){
    // eps means to what precision do we want it equal
    if(fabs(a.first - b.first) > eps) return false;
    if(fabs(a.second - b.second) > eps) return false;
    return true;
}
pair<double,double> Multiply2scalars(pair<double,double>  a,pair<double,double>  b){
    return {a.first*b.first - a.second*b.second,a.second*b.first + a.first*b.second};
}
double abs_of_scalar(pair<double,double>  a){
    double t = std::hypot(a.first,a.second);
    return t;
}
pair<double,double> conjugate_of_scalar(pair<double,double>  a){
    double t = -1.0;
    return {a.first,t*a.second};
}
pair<double,double> divide(pair<double,double> a,pair<double,double> b){
    double norm = b.first*b.first + b.second*b.second;
    pair<double,double> temp = Multiply2scalars(a,conjugate_of_scalar(b));
    return {temp.first / (norm) , temp.second / (norm)};
}
pair<double,double> add2scalars(pair<double,double> a,pair<double,double> b){
    return {a.first + b.first,a.second + b.second};
}

pair<double,double> subtract(pair<double,double> a,pair<double,double> b){
    return {a.first - b.first,a.second - b.second};
}
pair<double,double> complex_sqrt(pair<double,double> a){
    double abs_a = abs_of_scalar(a);
    if(abs_a == 0.0) return {0.0,0.0};
    double x = sqrt((abs_a + a.first)*0.5);
    double y = sqrt((abs_a - a.first)*0.5);

    if(a.second < 0.0) y = -y;
    return {x,y};
}


// Some basic operations between ket bra and density matrices
pair<double,double> inner_product(vector<vector<pair<double,double>>> a,vector<vector<pair<double,double>>>  b){
    // a and b have the same data type as a matrix to ease calculations later
    // n is the dimension of corresponding Hilbert space , in other words the dimension of row and column vector
    if(a.size() != b.size()){
        cout<<"2 vectors are not of same dimension"<<endl;
        return {DBL_MIN,DBL_MIN};
    }
    int n = a.size();
    pair<double,double> ans = {0.0,0.0};
    pair<double,double> temp;
    for(int i = 0;i<n;i++){
        temp = Multiply2scalars(a[i][0],conjugate_of_scalar(b[i][0]));
        ans.first += temp.first;
        ans.second += temp.second;
    }
    return ans;
}
vector<vector<pair<double,double>>> outer_product(vector<vector<pair<double,double>>> a,vector<vector<pair<double,double>>> b){
    int n = a.size();
    vector<vector<pair<double,double>>> ans = {};
    for(int i = 0;i<n;i++){
        ans.push_back({});
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            pair<double,double> temp = Multiply2scalars(a[i][0],conjugate_of_scalar(b[j][0]));
            ans[i].push_back(temp);
        }
    }
    return ans;
}

vector<vector<pair<double,double>>> tensor_product(vector<vector<pair<double,double>>> a,vector<vector<pair<double,double>>> b){
    // the drawback of this function is that you habe to pass even a pure state as vector<vector<pair<double,double>>> or 
    // straight away deal in its density matrix form
    int m1 = a.size();
    int n1 = a[0].size();
    int m2 = b.size();
    int n2 = b[0].size();
    vector<vector<pair<double,double>>> ans = {};

    for(int i = 0;i<m1*m2;i++){
        ans.push_back({});
    }

    for(int i = 0;i<m1*m2;i++){
        for(int j = 0;j<n1*n2;j++){
            ans[i].push_back(Multiply2scalars(a[i / m2][j / n2],b[i % m2][j % n2]));
        }
    }
    return ans;
}

pair<double,double> trace(vector<vector<pair<double,double>>> a){
    // trace can only be taken for square matrices
    if(a.size() != a[0].size()){
        cout<<"Not a square matrix"<<endl;
        return {DBL_MIN,DBL_MIN};
    }
    pair<double,double> ans = {0.0,0.0};
    int n = a.size();
    for(int i = 0;i<n;i++){
        ans.first += a[i][i].first;
        ans.second += a[i][i].second;
    }
    return ans;
}
 // write code for matrix multiplication as well
vector<vector<pair<double,double>>> MatrixMultiplication(vector<vector<pair<double,double>>> a,vector<vector<pair<double,double>>>   b){
    int m1 = a.size();
    int n1 = a[0].size();
    int m2 = b.size();
    int n2 = b[0].size();

    if(n1 != m2){
        cout<<"Matrix multiplication not possible"<<endl;
        return {{{0.0,0.0}}};
    }
    vector<vector<pair<double,double>>> ans = {};
    for(int i = 0;i<m1;i++){
        ans.push_back({});
    }
    for(int i = 0;i<m1;i++){
        for(int j = 0;j<n2;j++){
            ans[i].push_back({0.0,0.0});
            pair<double,double> temp = {0.0,0.0};
            for(int k = 0;k<n1;k++){
                temp = Multiply2scalars(a[i][k],b[k][j]);
                ans[i][j].first += temp.first;
                ans[i][j].second += temp.second;
            }
        }
    }
    return ans;
}
// end MatrixMultiplication
vector<vector<pair<double,double>>> MatrixAddition(vector<vector<pair<double,double>>>   a,vector<vector<pair<double,double>>>   b){
    if(a.size() != b.size() || a[0].size() != b[0].size()) {
        cout<<"Matrices not of same dimensions"<<endl;
        return {};
    }    
    vector<vector<pair<double,double>>> ans = a;
    int m = a.size();
    int n = a[0].size();
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            ans[i][j] = add2scalars(ans[i][j],b[i][j]);
        }
    }
    return ans;
}
vector<vector<pair<double,double>>> Scalar2matrix(pair<double,double>    scalar,vector<vector<pair<double,double>>>    a){
    // multiply a scalar to a matrix
    for(int i = 0;i<a.size();i++){
        for(int j = 0;j<a[0].size();j++){
            a[i][j] = Multiply2scalars(a[i][j],scalar);
        }
    }
    return a;
}
// end ScalarMultiplication
bool are_equal_matrices(vector<vector<pair<double,double>>> A,vector<vector<pair<double,double>>> B,double eps){
    if(A.size() != B.size()) return false;
    if(A[0].size() != B[0].size()) return false;

    for(int i = 0;i<A.size();i++){
        for(int j = 0;j<A[0].size();j++){
           if(!are_equal_scalars(A[i][j],B[i][j],eps)) return false;
        }
    }
    return true;
}
//end 
vector<vector<pair<double,double>>> ConjugateTranspose(vector<vector<pair<double,double>>>    A){
    vector<vector<pair<double,double>>> ans;
    int m = A.size();
    int n = A[0].size();
    for(int i = 0;i<n;i++){
        ans.push_back({});
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            ans[i].push_back({0.0,0.0});
        }
    }
    for(int i = 0;i<A.size();i++){
        for(int j = 0;j<A[0].size();j++){
            ans[i][j] = conjugate_of_scalar(A[j][i]);
        }
    }
    return ans;
}

bool isUnitary(vector<vector<pair<double,double>>>    U){
    if(are_equal_matrices(MatrixMultiplication(U,ConjugateTranspose(U)) ,identity(U.size()),1e-4)) return true;
    return false;
}
bool isMixed(vector<vector<pair<double,double>>>   a){ // a = rho the density operator
    pair<double,double> tr = trace(MatrixMultiplication(a,a));

    double epsilon = 1e-10;
    if(abs(tr.first - 1) < epsilon   && abs(tr.second) < epsilon) return false;
    else return true;
}
//end isMixed

void print_complex_matrix(vector<vector<pair<double,double>>> a){

    for(int i = 0;i<a.size();i++){
        for(int j = 0;j<a[0].size();j++){
            cout<<a[i][j].first<<" + i"<<a[i][j].second<<" ";
        }
        cout<<endl;
    }
    //this can be used for any matrix be key or bra or density matrix
}
//end print_complex_matrix



// The procedure complexeigenvalue computes the eigenvalues  
// of arbitrary n by n complex matrix (vector<vector<pair<double,double>>> a)
// A is the nxn Matrix, Lambda[] is the eigenvalues or the roots 
// 

void hessenberg(vector<vector<pair<double,double>>> & A){
    int n = A.size();
    if(n <= 2) return;
    for (int k = 0; k < n - 2; ++k){
        // 1. Extract the vector x from the k-th column, below the subdiagonal
        vector<pair<double,double>> x(n - k - 1);
        double norm_x_sq = 0.0;
        
        for (int i = k + 1; i < n; ++i){
            x[i - k - 1] = A[i][k];
            norm_x_sq += (x[i - k - 1].first)*(x[i - k - 1].first) + (x[i - k - 1].second)*(x[i - k - 1].second);
        }
        double norm_x = std::sqrt(norm_x_sq);
        
        if (norm_x == 0.0) continue; // Column is already zeroed out below subdiagonal
        // this may be need to be modified

        // 2. Compute the Householder vector v
        pair<double,double> x0 = x[0];
        pair<double,double> alpha;

        // Match the phase of x0 to prevent catastrophic cancellation
        if(abs_of_scalar(x0) == 0.0){
            alpha = {-norm_x,0.0};
        }
        else{
            alpha = Multiply2scalars({-norm_x,0.0},divide(x0,{abs_of_scalar(x0),0.0}));
        }
        
        vector<pair<double,double>> v = x;
        v[0] = subtract(v[0],alpha);
       
        double norm_v_sq = 0.0;
        for (const auto& val : v){
            norm_v_sq += (val.first)*(val.first) + (val.second)*(val.second);
        }
        double norm_v = std::sqrt(norm_v_sq);

        if (norm_v == 0.0) continue;

        // Normalize v
        for (auto& val : v){
            val = divide(val,{norm_v,0.0});
            
        }
        // 3. Apply Householder reflection from the left: A = (I - 2*v*v^*) * A
        // We only update the submatrix A[k+1:n, k:n]

        for (int j = k; j < n; ++j){
            pair<double,double> dot_product = {0.0,0.0};
            for (int i = k + 1; i < n; ++i){
                dot_product = add2scalars(dot_product,Multiply2scalars(conjugate_of_scalar(v[i-k-1]),A[i][j]));
            }
            for (int i = k + 1; i < n; ++i){
                A[i][j] = subtract(A[i][j],Multiply2scalars(Multiply2scalars({2.0,0.0},dot_product),v[i - k - 1]));
                
            }
        }
        // 4. Apply Householder reflection from the right: A = A * (I - 2*v*v^*)
        // We only update the submatrix A[0:n, k+1:n]

        for (int i = 0; i < n; ++i){
            pair<double,double> dot_product = {0.0,0.0};
            for (int j = k + 1; j < n; ++j){
                dot_product = add2scalars(dot_product,Multiply2scalars(A[i][j],v[j-k-1]));
            }
            for (int j = k + 1; j < n; ++j){
                A[i][j] = subtract(A[i][j],Multiply2scalars(Multiply2scalars({2.0,0.0},dot_product),conjugate_of_scalar(v[j - k - 1])));
            }
        
        }
        
    }
    // 5. Clean up computational noise (force strict zeros below the subdiagonal)
        for (int i = 2; i < n; ++i) {
            for (int j = 0; j < i - 1; ++j) {
                A[i][j] = {0.0, 0.0};
        }
    }

}


// Take the absolute value of the sum of the real and imag part of a complex number 
double sumabs(pair<double,double>  a){
    return fabs(a.first)+fabs(a.second);
}//end sumabs
//
void implicitQrStep(vector<vector<pair<double,double>>>& A, int k_start, int ien, bool exceptional) {
    pair<double,double> S;

    if (exceptional) {
        // Exceptional shift to break infinite periodic cycles
        double s = abs_of_scalar(A[ien][ien - 1]) + abs_of_scalar(A[ien - 1][ien - 2]);
        S = {s, s};
    } else {
        // Standard Wilkinson Shift from bottom-right 2x2 corner
        pair<double,double> a = A[ien - 1][ien - 1];
        pair<double,double> b = A[ien - 1][ien];
        pair<double,double> c = A[ien][ien - 1];
        pair<double,double> d = A[ien][ien];

        pair<double,double> tr = add2scalars(a, d);
        pair<double,double> det = subtract(Multiply2scalars(a, d), Multiply2scalars(b, c));
        pair<double,double> disc = complex_sqrt(subtract(Multiply2scalars(tr, tr), Multiply2scalars({4.0, 0.0}, det)));
        
        pair<double,double> l1 = divide(add2scalars(tr, disc), {2.0, 0.0});
        pair<double,double> l2 = divide(subtract(tr, disc), {2.0, 0.0});

        double t1 = abs_of_scalar(subtract(l1, d));
        double t2 = abs_of_scalar(subtract(l2, d));
        S = (t1 < t2) ? l1 : l2;
    }

    // Initialize bulge chasing vector from the start of the active block
    pair<double,double> x = subtract(A[k_start][k_start], S);
    pair<double,double> y = A[k_start + 1][k_start];

    for (int k = k_start; k < ien; ++k) {
        pair<double,double> c_rot, s_rot;
        double r = std::hypot(abs_of_scalar(x), abs_of_scalar(y));

        if (r == 0.0) {
            c_rot = {1.0, 0.0};
            s_rot = {0.0, 0.0};
        } else {
            c_rot = divide(conjugate_of_scalar(x), {r, 0.0});
            s_rot = divide(conjugate_of_scalar(y), {r, 0.0});
        }

        // --- CRITICAL FIX: Left Multiplication Loop Bounds ---
        // For k > k_start, column (k - 1) MUST be updated to zero out the subdiagonal bulge!
        int j_start = (k == k_start) ? k_start : k - 1;

        for (int j = j_start; j <= ien; ++j) {
            pair<double,double> t1 = A[k][j];
            pair<double,double> t2 = A[k + 1][j];

            A[k][j]     = add2scalars(Multiply2scalars(c_rot, t1), Multiply2scalars(s_rot, t2));
            A[k + 1][j] = add2scalars(Multiply2scalars(Multiply2scalars({-1.0, 0.0}, conjugate_of_scalar(s_rot)), t1),
                                      Multiply2scalars(conjugate_of_scalar(c_rot), t2));
        }

        // --- Right Multiplication (Columns k and k+1) ---
        for (int i = 0; i <= std::min(k + 2, ien); ++i) {
            pair<double,double> t1 = A[i][k];
            pair<double,double> t2 = A[i][k + 1];

            A[i][k]     = add2scalars(Multiply2scalars(conjugate_of_scalar(c_rot), t1), Multiply2scalars(conjugate_of_scalar(s_rot), t2));
            A[i][k + 1] = add2scalars(Multiply2scalars(Multiply2scalars({-1.0, 0.0}, s_rot), t1), Multiply2scalars(c_rot, t2));
        }

        // Propagate bulge down the subdiagonal
        if (k < ien - 1) {
            x = A[k + 1][k];
            y = A[k + 2][k];
        }
    }
}
void complexeigenvalue(vector<vector<pair<double,double>>> & A, vector<pair<double,double>> & lamda) {
    hessenberg(A); // Pre-condition step
    //print_complex_matrix(A);
    int n = A.size();
    lamda.resize(n);

    double eps = std::pow(2.0, -53);
    int max_iterations = 30 * n;
    int ien = n - 1;

    while (ien >= 0) {
        
        int its = 0;

        if (ien == 0) {
            lamda[0] = A[0][0];
            break;
        }

        while (its < max_iterations) {
            // Check for deflation at bottom
            double subdiag_mag = abs_of_scalar(A[ien][ien-1]);
            double diag_scale  = abs_of_scalar(A[ien-1][ien-1]) + abs_of_scalar(A[ien][ien]);

            if (subdiag_mag <= eps * diag_scale || subdiag_mag == 0.0) {
                lamda[ien] = A[ien][ien];
                A[ien][ien-1] = {0.0, 0.0};
                ien--;
                break;
            }

            // Check for internal decoupling boundary
            int k_start = 0;
            for (int k = ien - 1; k > 0; --k) {
                if (abs_of_scalar(A[k][k-1]) <= eps * (abs_of_scalar(A[k-1][k-1]) + abs_of_scalar(A[k][k])) ) {
                    A[k][k-1] = {0.0, 0.0};
                    k_start = k; // Focus active QR step starting from row/col k
                    break;
                }
            }

            // Run in-place QR step without slicing sub-matrices
            bool use_exceptional = (its == 10 || its == 20);
            implicitQrStep(A, k_start, ien, use_exceptional);
            its++;
        }

        // Pathological safety fall-through
        if (its >= max_iterations && ien >= 0) {
            std::cerr << "Warning: Convergence failure at index " << ien << endl;
            lamda[ien] = A[ien][ien];
            ien--;
        }
    }
}
bool isDensityMatrix(vector<vector<pair<double,double>>> a){
    vector<pair<double,double>> lamda = {};
    complexeigenvalue(a,lamda);
    double eps = 1e-10;
    
    for(int i = 0;i<lamda.size();i++){
        // all eigenvalues should be real and real part >= 0
        if(fabs(lamda[i].second) > eps) return false;
        if(lamda[i].first < 0) return false;
    }
    pair<double,double> tr = trace(a);
    if(fabs(tr.first - 1) > eps || fabs(tr.second) > eps) return false;
    // checking normalization condition
    return true;
}

vector<vector<pair<double,double>>> identity(int n){ // return n dimensional identity
    vector<vector<pair<double,double>>> I = {};
    for(int i = 0;i<n;i++){
        I.push_back({});
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(i == j) I[i].push_back({1.0,0.0});
            else I[i].push_back({0.0,0.0});
        }
    }
    return I;
}
// end identity

vector<vector<pair<double,double>>> Projector(vector<vector<pair<double,double>>>  A,pair<double,double> eigenval,vector<pair<double,double>> lamda){
    // to find this we need main matrix A , all set of eigenvalues and eigenvalue wrt which projector is to be found 
    vector<vector<pair<double,double>>> id = identity(A.size());
    vector<vector<pair<double,double>>> ans = id;
    for(int i = 0;i<lamda.size();i++){
        if(are_equal_scalars(eigenval,lamda[i],1e-5) == false){
            vector<vector<pair<double,double>>> temp = Scalar2matrix(divide({1.0,0.0},subtract(eigenval,lamda[i])),MatrixAddition(A,Scalar2matrix({-1*lamda[i].first,-1*lamda[i].second},id)));
            ans = MatrixMultiplication(ans,temp);
        }
    }
    return ans;
}

// we will return to write functions to generate eigenvectors

// first we shall emphasise on Postutaltes of Quantum Mechanics

/*
Ist Postulate on QM : Associated to any isolated physical system is a complex vector space with inner product 
ie A Hilbert Space known as State space of the system.The system is completelty described by it's state vector 
which is a unit vector in the system's state space.

(Density Matrix version) : Associated to any isolated physical system is a Hilbert space known as state space 
of the system.The system is completely descibed by it's Density Matrix which is a positive operator rho with
trace(rho) = 1 acting on the state space of the system.

As of 7/4/2026 , we can suitably express pure/mixed state of a system using vector<vector<pair<double,double>>>
noting that even ket and bra shall use the same data type(?).We can check if a density matrix is indeed a density 
matrix, whether its mixed or not.

IInd Postulate on QM : The evolution and dynamics of a closed quantum system is descibed by a Unitary transformation ie
ket(psi(t')) = U * ket(psi(t))

(Density Matrix Version) : The evolution of a closed quantum system is described by a Unitary transformation U ie the state
rho of the system at time t1 is relatd to the state rho' at time t2 by a Unitary tranformation U (U*U_dagger = I)
rho'  = U * rho * (U_dagger) // here U dagger is Conjugate transpose of U

We on 7/4/26 will need to work on this so we can show dynamics of a system correctly
We shall return on IIIrd and IVth postulates later
*/

vector<vector<pair<double,double>>> pure_state_evolution(vector<vector<pair<double,double>>>  U,vector<vector<pair<double,double>>>  psi){
    return MatrixMultiplication(U,psi);
}

vector<vector<pair<double,double>>> mixed_state_evolution(vector<vector<pair<double,double>>>  U, vector<vector<pair<double,double>>>  rho){
    if(! isUnitary(U)){
        cout<<"U input is not Unitary"<<endl;
        return {};
    }
    return MatrixMultiplication(MatrixMultiplication(U,rho),ConjugateTranspose(U));
}

/*
Now we shall discuss the IIIrd and IV th postulates of QM.

IIIrd Postulate on QM : Quantum Measurements are described by a collection {M m}.
These Operators act on the state space of the system being measured. The index m
refers to the measurement outcomes that may occur in the experiment. If the state of
the quantum system is ket(psi) immediately before the measurement then the probabiltity that 
result m occurs is given by : 
    p(m) = bra(psi)*(M m _ dagger) * (M m) * ket(psi)
    and the state of system after this measurement is given by :
    
    ket(psi ') = (M m)*ket(psi) / sqrt(p(m))

(Density Matrix Version) : (more general) Suppose we perform a measurement described by
Measurment Operators {M m}. If the initial state was ket(psi i) then the probability of 
getting result m is given by 
    p(m | i) = bra(psi i)*(M m _ dagger) * (M m) * ket(psi i)

    with the total probabilty of obtaining result m being 

    p(m) = trace((M m) * rho * (M m _ dagger))
    // here rho is the mixed state of system just before measurement. 
    The evolved state of system after this measurement is

    (rho _ m) = (M m) * rho * (M m _ dagger) / trace((M m) * rho * (M m _ dagger))


Lets proceed to implment the IIIrd postulate
*/

vector<vector<pair<double,double>>> pure_state_measurement(vector<vector<pair<double,double>>>  M_m,vector<vector<pair<double,double>>> psi,double p_m){
    // M_m is the measurement operator while ket psi is the pure state just before measurement
    // p_m is the probability

    
    auto it = MatrixMultiplication(ConjugateTranspose(M_m),ConjugateTranspose(psi));
    auto temp = MatrixMultiplication(ConjugateTranspose(it),it);
    // temp shall be a vector<vector<pair<double,double>>> but in its totality its a scalar
    p_m = temp[0][0].first;
    cout<<"The probability of obtaining corrsponding result is "<<p_m<<endl; 
    double temp2 = 1.0 / sqrt(p_m);
    return Scalar2matrix({temp2,0.0},it);
}

vector<vector<pair<double,double>>> mixed_state_measurement(vector<vector<pair<double,double>>>  M_m,vector<vector<pair<double,double>>>  rho,double p_m){
    // p_m is total probabilty of result m occuring
    // M_m is the measurement operator while rho is the mixed state of system just before measurement
    auto it = MatrixMultiplication(MatrixMultiplication(M_m,rho),ConjugateTranspose(M_m));
    auto it3 = trace(it);
    auto it2 = divide({1.0,0.0},it3);
    p_m = it3.first;
    cout<<"The probability of obtaining corrsponding result is "<<p_m<<endl;
    return Scalar2matrix(it2,it);
}

/*
IVth Postulate on QM : The state space of a Composite physical system is the tensor product 
of the state spaces of the component physical systems.
If we have systems numbered 1 to n and system no. i is prepared in state rho_i (mixed state)
then the joint state of the total system is
    rho(12...n) = (rho_1) x (rho_2) x ... x (rho_n) where x denotes tensor product

*/

vector<vector<pair<double,double>>> state_of_composite_system(vector<vector<vector<pair<double,double>>>>  rho ){

    // the input is a vector of denity matrices of subssystems of a sytem whose density matrix we wish to find
    vector<vector<pair<double,double>>> ans = rho[0];
    int j = 1;
    while(j < rho.size()){
        ans = tensor_product(ans,rho[j]);
        j++;
    }
    return ans;
}

vector<vector<pair<double,double>>> partial_trace(vector<vector<pair<double,double>>>  A,vector<int>  partial_system){
    //this code is written solely for std computational Basis. partial sytem includes indices of a basis state's value which are to 
    // be included i.e. wrt which we wish to find the partial trace.
    // note that these indices must be presented to us in a sorted manner

    /*We start these indexes from 0 for sake of this language
    for eg if we have |0101><1010| then partial system {1,3} would mean to include 2nd and 4th qubits respectively.
    */
    int n = partial_system.size();
    double t1,t2;
    t1 = A.size();
    t2 = 2.0;
    int b = round(log(t1)/log(t2));
    int p = int(pow(2,b - n));

    std::sort(partial_system.begin(),partial_system.end());

    vector<vector<pair<double,double>>> ans = {};
    
    for(int i = 0;i<p;i++){
        ans.push_back({});
    }
    
    for(int i = 0;i<p;i++){
        for(int j = 0;j< p ;j++){
            ans[i].push_back({0.0,0.0});
        }
    }
    //this code strictly assumes we are currently working in 32 qubits or lesser 
    for(int i = 0;i<A.size();i++){
        for(int j = 0;j<A.size();j++){
            int n1 = 0;
            int n2 = 0;
            int m1 = 0;
            int m2 = 0;
            // i is row j is column
            for(int k = 0;k<n;k++){
                if(i & (1 << (32 - partial_system[k])) ) n1 = n1 | (1<<(32 - partial_system[k]));
                if(j & (1 << (32 - partial_system[k])) ) n2 = n2 | (1<< (32 -partial_system[k]));
            }
            m1 = i ^ n1;
            m2 = j ^ n2;
            if(n1 == n2) {
                ans[m1][m2] = A[i][j];
            }
        }
    }
    return ans;
    //check code 
}

