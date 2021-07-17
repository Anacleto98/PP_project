#include <vector>
#include "utils.cpp"
#include "parallel_sort_optimized.cpp"

int test_correctness(std::vector<int> &vec, int r)
{
    int n = vec.size();
    std::vector<int> result(n);
    std::vector<int> count(r,0);
    
    for(int i = 0; i < n; i++)
    {
        count[vec[i]]++;
    }

    result = sort(vec,r);
    
    for(int i = 0; i < n; i++)
    {
        count[result[i]]--;
    }

    for(int i = 0; i < r; i++)
    {
        if(count[i]!=0)
            return 0;
    }
    

    return check_ordered(result);

}
