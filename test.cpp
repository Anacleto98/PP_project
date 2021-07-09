#include "parallel_sort.cpp"
#include "serial_sort.cpp"
#include <vector>
#include "utils.cpp"
#include <omp.h>


int main()
{
    int n = 100000;
    int r = 1000;
    omp_set_nested(1);
    omp_set_dynamic(0);
    
    double start,end;

    
    std::vector<int> a(n);
    std::vector<int> res(n);

    for(int i=0; i<n; i++)
        a[i] =  rand() % r;

    for(int i = 1; i<=8;i*=2)
    {
        omp_set_num_threads(i);
        start = omp_get_wtime();
        res = parallel_sort(a,r);
        end = omp_get_wtime();
        std::cout<<"With "<<i<<" threads: "<<end-start<<std::endl;
    }

    return 0;
}