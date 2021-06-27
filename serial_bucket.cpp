#include <vector>
#include <iostream> 



std::vector<int> serial_sort(std::vector<int> &arr, int r)
{
    int n = arr.size();
    std::vector<int> result;
    std::vector<std::vector<int>> buckets (r);

    for(int i = 0; i < n; i++)
        buckets[arr[i]].push_back(arr[i]);

    for(int i = 0; i < r; i++)
        for(int j = 0; j < buckets[i].size(); j++)
            result.push_back(buckets[i][j]);

    return result;
}


int main()
{
    int n = 100;
    int r = 10;

    std::vector<int> arr(n);
    std::vector<int> res(n);

    for(int i = 0; i < n; i++)
        arr[i] = rand() % r;
    
    res = serial_sort(arr,r);

    for(int i = 0; i < n; i++)
        std::cout<<res[i]<<"-";
    std::cout<<std::endl;

    return 0;
}