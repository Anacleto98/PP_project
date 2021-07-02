#include <omp.h> 
#include <iostream>
#include <vector>
#include <assert.h>
#include "utils.cpp"
#include <benchmark/benchmark.h>


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

        #pragma omp parallel for num_threads(4)
        for(int i = offset; i < S; i++){
            p_sum[i] = b[i]+b[i-range];
        }
        offset *= 2;
    }

    
    
    return p_sum;
}



/*
int main()
{

    int N = 100000000; 
    std::vector<int> a(N,1);
    std::vector<int> res(N,0);
    omp_set_nested(1);

    res = prefix_sum(a);

    for(int i = 0; i<N; i++)
        assert(res[i]==(i+1));


    return 0;
}
*/

void BM_parallel_sort(benchmark::State& state) {

    //omp_set_nested(1);
    int n = state.range(0);

    std::vector<int> arr(n,1);
    std::vector<int> result(n,0);



    for (auto _ : state) {
        result = prefix_sum(arr);
    }
    state.SetComplexityN(state.range(0));
}


BENCHMARK(BM_parallel_sort)
    ->RangeMultiplier(2)->Range(32, 1<<20)->Complexity();

BENCHMARK_MAIN();

