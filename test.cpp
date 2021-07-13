#include "parallel_sort_optimized.cpp"
#include "serial_sort.cpp"
#include <vector>
#include "utils.cpp"



int main()
{
    int n = 100000000;
    int r = 10000;

    omp_set_nested(1);
    omp_set_dynamic(0);
    omp_set_num_threads(8);
    
    
    std::vector<int> arr(n);
    std::vector<int> result(n);

    for(int i=0;i<n;i++)
        arr[i] = rand() % r;
    
    result = parallel_sort(arr,r);

    return 0;
}