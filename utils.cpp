#include <array>
#include <vector>
#include <iostream>

template <std::size_t N>
void print_array(std::array<int,N> arr){
    int i = 0;
    for(; i < N-1; i++)
        std::cout<<arr[i]<<"-";
    std::cout<<arr[i]<<std::endl;
}

template <std::size_t N,std::size_t M>
void print_2darray(std::array<std::array<int,M>,N> arr){
    for(int i = 0; i<N; i++)
        print_array(arr[i]);
}



void print_2dvector(std::vector<std::vector<int>> &vec)
{
    for(int i=0;i<vec.size();i++)
    {
        for(int j = 0; j<vec[i].size(); j++)
        {
            std::cout<<"-"<<vec[i][j]<<"-";
        }
        std::cout<<std::endl;
    }
}

void print_vector(std::vector<int> &vec)
{
    int i=0;
    for(;i<vec.size();i++)
        std::cout<<"-"<<vec[i]<<"-";
    std::cout<<std::endl;
    
}

int check_ordered(std::vector<int> &vec)
{
    int check = 1;
    for(int i = 1; i < vec.size(); i++)
    {
        if(vec[i]<vec[i-1])
        {
            std::cout<<"Error in position: "<<i<<" vec[i]:"<<vec[i]<<" vec[i-1]:"<<vec[i-1]<<std::endl;
            check = 0;
        }
            
    }
    return check;
}