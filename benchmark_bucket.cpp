#include "parallel_sort_optimized.cpp"
#include <vector>
#include "utils.cpp"
#include <omp.h>
#include <benchmark/benchmark.h>

void BM_serial_sort(benchmark::State& state) {
    

    omp_set_nested(1);
    omp_set_dynamic(0);
    omp_set_num_threads(1);
    
    int n = state.range(0);
    int r = sqrt(n);
    std::vector<int> arr(n);
    std::vector<int> result(n);

    for(int i=0;i<n;i++)
        arr[i] = rand() % r;
    

    for (auto _ : state) {
        result = parallel_sort(arr,r);
    }
    state.SetComplexityN(state.range(0));
}

void BM_parallel_sort_2(benchmark::State& state) {
    

    omp_set_nested(1);
    omp_set_dynamic(0);
    omp_set_num_threads(2);
    
    int n = state.range(0);
    int r = sqrt(n);
    std::vector<int> arr(n);
    std::vector<int> result(n);

    for(int i=0;i<n;i++)
        arr[i] = rand() % r;
    

    for (auto _ : state) {
        result = parallel_sort(arr,r);
    }
    state.SetComplexityN(state.range(0));
}

void BM_parallel_sort_4(benchmark::State& state) {
    

    omp_set_nested(1);
    omp_set_dynamic(0);
    omp_set_num_threads(4);
    
    int n = state.range(0);
    int r = sqrt(n);
    std::vector<int> arr(n);
    std::vector<int> result(n);

    for(int i=0;i<n;i++)
        arr[i] = rand() % r;
    

    for (auto _ : state) {
        result = parallel_sort(arr,r);
    }
    state.SetComplexityN(state.range(0));
}

void BM_parallel_sort_8(benchmark::State& state) {
    

    omp_set_nested(1);
    omp_set_dynamic(0);
    omp_set_num_threads(8);
    
    int n = state.range(0);
    int r = sqrt(n);
    std::vector<int> arr(n);
    std::vector<int> result(n);

    for(int i=0;i<n;i++)
        arr[i] = rand() % r;
    

    for (auto _ : state) {
        result = parallel_sort(arr,r);
    }
    state.SetComplexityN(state.range(0));
}

void BM_parallel_sort_16(benchmark::State& state) {
    

    omp_set_nested(1);
    omp_set_dynamic(0);
    omp_set_num_threads(16);
    
    int n = state.range(0);
    int r = sqrt(n);
    std::vector<int> arr(n);
    std::vector<int> result(n);

    for(int i=0;i<n;i++)
        arr[i] = rand() % r;
    

    for (auto _ : state) {
        result = parallel_sort(arr,r);
    }
    state.SetComplexityN(state.range(0));
}


BENCHMARK(BM_serial_sort)
    ->RangeMultiplier(2)->Range(4096, 1<<25)->UseRealTime()->Complexity(benchmark::oN);

BENCHMARK(BM_parallel_sort_2)
    ->RangeMultiplier(2)->Range(4096, 1<<25)->UseRealTime()->Complexity(benchmark::oN);


BENCHMARK(BM_parallel_sort_4)
    ->RangeMultiplier(2)->Range(4096, 1<<25)->UseRealTime()->Complexity(benchmark::oN);

BENCHMARK(BM_parallel_sort_8)
    ->RangeMultiplier(2)->Range(4096, 1<<25)->UseRealTime()->Complexity(benchmark::oN);

BENCHMARK(BM_parallel_sort_16)
    ->RangeMultiplier(2)->Range(4096, 1<<25)->UseRealTime()->Complexity(benchmark::oN);





BENCHMARK_MAIN();