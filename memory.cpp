#include "parallel_sort.cpp"
#include "serial_sort.cpp"
#include <vector>
#include "utils.cpp"
#include <omp.h>
#include <cmath>

#define INSTANCE 100


int main()
{
    
    omp_set_nested(1);
    omp_set_dynamic(0);
    omp_set_num_threads(8);
    

    int n = INSTANCE;
    int r = sqrt(n);
    std::vector<int> a(n);
    std::vector<int> res(n);

    for(int i=0; i<n; i++)
        a[i] =  rand() % r;

    for(int i = 1; i<=8;i*=2)
    {
        res = parallel_sort(a,r);
    }

    return 0;
}