#include <vector>
#include <cmath>
#include <omp.h>
#include <iostream>
#include "bucket_sorting.cpp"

using namespace std;



std::vector<int> prefix_sum(std::vector<int> &a)
{
    int S = a.size();
    std::vector<int> b(S);
    std::vector<int> p_sum(S);
    int range = 1;
    int offset = 1;
    p_sum = a;

    for(; offset<S; range *= 2)
    {
    
        b = p_sum;

        #pragma omp parallel for 
        for(int i = offset; i < S; i++){
            p_sum[i] = b[i]+b[i-range];
        }
        
        offset *= 2;
    }
    return p_sum;
}



void partition(std::vector<int> &src, std::vector<std::vector<int>> &dest, int r)
{   
    int N = src.size();
    int j;

    #pragma omp parallel for private(j)
    for(int i = 0; i < N/r; i++)
        for(j = 0; j < r; j++)
            dest[i][j] = src[i*r+j];
    
    
    #pragma omp parallel for private(j)
    for(int i = 0; i < N/r; i++)
    {
        bucket_sort(dest[i],r);
        
        for(j = 0; j < r; j++)
        {
            src[i*r + j] = dest[i][j];
        }       
    }
}

void init_number(std::vector<std::vector<int>> &number, std::vector<std::vector<int>> &b, int N,int r)
{
    int j;
    #pragma omp parallel for private(j) 
    for(int i = 0; i < N/r; i++)
    {
        for(j = 0; j < r; j++)
        {
            number[b[i][j]][i]++;
        }
    }
}


void init_serial(std::vector<int> &serial,std::vector<std::vector<int>> &b,int N, int r)
{
    int count;
    int j,k;
    #pragma omp parallel for private(j,k,count)
    for(int i = 0; i < N/r; i++)
    {
        serial[i*r] = 0;

        for(j = 1; j < r; j++)
        {
            count = 0;

            for(k = j-1; k >= 0 && b[i][j] == b[i][k]; k--)
            {
                count++;
            }
            serial[i*r+j] = count;
        }
    }
}



std::vector<int> parallel_sort(std::vector<int> &a, int r)
{
    int N = a.size();
    std::vector<int> result(a.size(),0);
    std::vector<std::vector<int>> number(r,std::vector<int>(N/r,0));
    std::vector<std::vector<int>> prefix_sums(r,std::vector<int>(N/r,0));
    std::vector<int> serial(N);
    std::vector<std::vector<int>> b(N/r,std::vector<int>(r));
    std::vector<int> cardinality(r,0);
    std::vector<int> global(r,0);
    

    partition(a,b,r);
   
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            init_number(number,b,N,r);
        }
        #pragma omp section
        {
            init_serial(serial,b,N,r);
        }
    }
   

    for(int i = 0; i< r; i++)
    {
        prefix_sums[i] = prefix_sum(number[i]);
    }


    #pragma omp parallel for 
    for(int i = 0; i < r; i++)
    {
        cardinality[i] = prefix_sums[i].back();
    }

    global = prefix_sum(cardinality);


  

    /////////////////////////////////////////////////////////////////


    int s,gl,pf;
    #pragma omp parallel for private(s,gl,pf)  
    for(int i = 0; i < N; i++)
    {
        if(a[i] > 0)
            gl = global[a[i]-1];
        else 
            gl = 0; 
        
        s = ceil(i/r)-1;

        if(s >= 0)
            pf = prefix_sums[a[i]][s];
        else 
            pf = 0;

        result[serial[i]+pf+gl] = a[i];

    }


    return result;

}

