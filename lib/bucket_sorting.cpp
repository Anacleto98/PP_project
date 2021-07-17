#include <vector>

void bucket_sort(std::vector<int> &vec, int r)
{
    std::vector<std::vector<int>> buckets(r);

    for(int i = 0; i < vec.size(); i++)
    {
        buckets[vec[i]].push_back(vec[i]);
    }

    vec.clear();

    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < (buckets[i]).size(); j++)
        {
            vec.push_back(buckets[i][j]);
        }
    }
}