#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <random>
#include <ctime>
#include <omp.h> 

using namespace std;

template <typename T>
void mult(const vector<vector<T>>& A, const vector<vector<T>>& B, int n, int m, int k)
{  
    vector<vector<T>> C(m, vector<T>(n));
    for (int i = 0; i < m; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            for (int l = 0; l < k; ++l) 
            {
                C[i][j] += A[i][l] * B[l][j];
            }
        }
    }
}


template <typename T>
void parallel_mult(int num_threads, const vector<vector<T>>& A, const vector<vector<T>>& B)
{              
    int m = A.size();                   
    int n = B[0].size();                
    int k = B.size();  
    vector<vector<T>> C(n, vector<T>(m));
    omp_set_num_threads(num_threads);
    #pragma omp parallel for
    for (int i = 0; i < m; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            for (int l = 0; l < k; ++l) 
            {
                C[i][j] += A[i][l] * B[l][j];
            }
        }
    }
}


int main(int argc, char** argv)
{
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    int k = atoi(argv[3]);
    int t = atoi(argv[4]);
    vector<vector<float>> A(m, vector<float>(n));
    srand(time(0));
    for (int i = 0; i < m; ++i) 
    {
        for (int j = 0; j < n; ++j) A[i][j] = (float) rand() / RAND_MAX; 
    }

    vector<vector<float>> B(n, vector<float>(k));
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < k; ++j) B[i][j] = (float) rand() / RAND_MAX; 
    }

    time_t start = time(NULL);
    if (t == 1)
    {
        mult<float>(A, B, n, m, k);
    }
    else {parallel_mult<float>(t, A, B);}
    time_t end = time(NULL);
    double elapsed = difftime(end, start);
    cout << "Время выполнения: " << elapsed << " секунд\n";
    return 0;
}

    