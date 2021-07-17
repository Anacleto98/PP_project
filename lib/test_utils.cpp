#include <vector>
#include "utils.cpp"
#include "parallel_sort.cpp"


int check_ordered(std::vector<int> &vec)
{
    for(int i = 1; i < vec.size(); i++)
    {
        if(vec[i]<vec[i-1])
        {
            std::cout<<"Error in position: "<<i<<" vec[i]:"<<vec[i]<<" vec[i-1]:"<<vec[i-1]<<std::endl;
            return 0;
        }     
    }
    return 1;
}


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
