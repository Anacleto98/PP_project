#include <cmath>
#include <vector>
#include <iostream>
#include "lib/test.cpp"

#define MIN 1<<6
#define MAX 1<<26

int main()
{
    int i = MIN;
    int r;
    int correct;
    std::vector<int> arr;

    for(;i <= MAX; i*=2)
    {
        arr.clear();
        arr.resize(i);

        r = sqrt(i);

        for(int j = 0; j < i; j++)
        {
            arr[j] = rand() % r;
        }

        std::cout<<"Testing n: "<<i<<"; r: "<<r<<" ... ";
        correct = test_correctness(arr,r);
        if(correct == 1)
        {
            std::cout<<"Passed ✓"<<std::endl;
        }
        else
        {
            std::cout<<"Failed X"<<std::endl;
        }
    }
    return 0;
}