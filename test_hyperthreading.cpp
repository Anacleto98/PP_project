#include <omp.h>
#include <iostream>
#include <cmath>

using namespace std;


void work(int i)
{
    double result1,result2,result3;
    result1 = sqrt(i)*cos(i)/sin(i)*sqrt(i+1);
    result2 = sqrt(i)*cos(i)/sin(i+1)*sqrt(i+1);
    result3 = sqrt(i)*cos(i+1)/sin(i)*sqrt(i+1);
    

}



int main()
{
    double start,end;

    for(int j = 1; j <= 16; j*=2)
    {
        omp_set_num_threads(j);
        cout<<j<<" threads"<<endl;
        start = omp_get_wtime();
        #pragma omp parallel for
        for(int i = 0; i < 10000000000000; i++)
            work(i);
        end = omp_get_wtime();
        cout<<end-start<<endl;

    }
    return 0;
}