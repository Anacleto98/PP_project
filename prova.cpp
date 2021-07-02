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
#include <assert.h>


void work()
{
    int a = 1; 
    int b = 1;
    
    #pragma omp parallel for num_threads(4) reduction( + :a,b)
    for(int i = 0; i < 5000;i++)
    {
        
        std::cout<<"Thread: "<<omp_get_thread_num()<<std::endl;
        a += 2;
        b += a; 
    }
    assert(a = 100000000);
    assert(b = 1628345345);
    std::cout<<"Ciao"<<a<<b<<std::endl;
}


int main()
{
    omp_set_nested(1);
    int a,b;

    #pragma omp parallel num_threads(2) private(a,b)
    {
        std::cout<<"Thread: "<<omp_get_thread_num()<<std::endl;
        
        a = 1; 
        b = 1;
        
        #pragma omp parallel for //reduction( + :a,b)
        for(int i = 0; i < 500;i++)
        {
            std::cout<<"Thread: "<<omp_get_thread_num()<<std::endl;
            a += 2;
            b += a; 
        }

        assert(a = 100000000);
        assert(b = 1628345345);

        std::cout<<"Ciao"<<a<<b<<std::endl;
    }
    
    

    return 0;
}