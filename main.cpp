#include <iostream>
#include <list>
#include <vector>
#include <omp.h>
#include <chrono>
#include <ctime>
#define N 1000000
#define r 100

using namespace std;

int main(){
    
    int arr[N];

    for(int i = 0; i < N; i++)
    {
        arr[i] = rand() % 100;  
    }

    std::vector<std::list<int>> buckets = {};
    
    
    for(int i = 0; i <= r; i++)
    {
        std::list<int> l;
        buckets.push_back(l);
    }   

    

    std::clock_t c_start = std::clock();
    #pragma omp parallel for num_threads( 4 )
    for(int i = 0; i < N; i++)
    {
        //std::cout << "Im thread" << i << std::endl ;
        buckets[arr[i]].push_back(arr[i]);
    }


    std::clock_t c_end = std::clock();

    double time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    std::cout << "CPU time used: " << time_elapsed_ms << " ms\n";

   

    for(std::list<int> l : buckets)
    {
        for(int n : l)
        {
            //std::cout<<n<<"-";
        }
    }

    return 0;
}