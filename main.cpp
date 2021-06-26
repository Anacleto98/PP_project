#include <iostream>
#include <list>
#include <vector>
#include <omp.h>
#include <array>
#include <chrono>
#include <ctime>
#include <iterator>
#include "utils.cpp"
#include <cmath>


std::vector<int> prefix_sum(std::vector<int> a,int S)
{
    std::vector<int> b(S);
    std::vector<int> p_sum(S);
    int range = 1;
    int offset = 1;
    p_sum = a;

    for(; offset<S; range *= 2)
    {
        //std::copy(std::begin(p_sum), std::end(p_sum), std::begin(b)); // 
        b = p_sum;
        // this can be done in parallel
        #pragma omp parallel for
        for(int i = offset; i < S; i++){
            p_sum[i] = b[i]+b[i-range];
        }
        offset *= 2;
    }
    return p_sum;
}



std::vector<std::vector<int>> partition(std::vector<int> src, int r)
{   
    int N = src.size();
    std::vector<std::vector<int>> dest(N/r,std::vector<int>(r,0));
    int i,j;
    //#pragma omp parallel for private(j)
    for(i = 0; i < N/r; i++)
        for(j = 0; j < r; j++)
            dest[i][j] = src[i*r+j];
    return dest;
}



void init_number(std::vector<std::vector<int>> &number, std::vector<std::vector<int>> &b, int N, int r)
{
    #pragma parallel for 
    for(int i = 0; i < N/r; i++)
    {
        //#pragma parallel for 
        for(int j = 0; j < r; j++)
        {
            number[b[i][j]][i]++;
        }
    }
}


void init_serial(std::vector<int> &serial,std::vector<std::vector<int>> &b,int N, int r)
{
    int count;
    #pragma parallel for 
    for(int i = 0; i < N/r; i++)
    {
        serial[i*r] = 0;

        #pragma parallel for private(k,count)
        for(int j = 1; j < r; j++)
        {
            count = 0;
            for(int k = j-1; k >= 0; k--)
            {
                if(b[i][j] == b[i][k])
                    count++;
            }
            serial[i*r+j] = count;
        }
    }
}



std::vector<int> parallel_sort(std::vector<int> &a, size_t r)
{
    int N = a.size();
    std::vector<std::vector<int>> number(r,std::vector<int>(N/r,0));
    std::vector<std::vector<int>> prefix_sums(r,std::vector<int>(N/r,0));
    std::vector<int> serial(N);
    std::vector<std::vector<int>> b;
    std::vector<int> cardinality(r,0);
    std::vector<int> global(r,0);
    std::vector<int> result(N);
    b = partition(a,r);
    //print_2dvector(b);
    

    #pragma omp parallel
    {
        #pragma omp sections
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
    }

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                #pragma omp parallel for num_threads(4)
                for(int i = 0; i< r; i++)
                {
                    prefix_sums[i] = prefix_sum(number[i],N/r);
                }
            } 
            #pragma omp section
            {
                int j,sum;
                #pragma omp parallel for private(j,sum) num_threads(8)
                for(int i = 0; i < r; i++)
                {   
                    sum = 0;
                    //#pragma omp parallel for reduction(+:sum)
                    for(j = 0; j < N/r; j++)
                    {
                        sum += number[i][j];
                    } 
                    cardinality[i] = sum;
                }
            }        
        }
    }
    #pragma omp barrier

    global = prefix_sum(cardinality,r);

    /////////////////////////////////////////////////////////////////

    int s,gl,pf;
    #pragma omp parallel for private(s,gl,pf) num_threads(8)
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


int main(){
    
    const long unsigned int N = 2000000;
    std::vector<int> a(N);
    std::vector<int> result(N);
    
    int r=200;
    // aux data structure 

    for(int i=0;i<N;i++)
        a[i] = rand() % r;

    result = parallel_sort(a,r);

    //print_vector(result);    

    return 0;
}


