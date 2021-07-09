#include <vector>
#include <cmath>

std::vector<int> serial_prefix_sum(std::vector<int> &a,int S)
{
    std::vector<int> b(S);
    std::vector<int> p_sum(S);
    int range = 1;
    int offset = 1;
    p_sum = a;

    for(; offset<S; range *= 2)
    {
        //std::copy(std::begin(p_sum), std::end(p_sum), std::begin(b)); // 
        b = p_sum;
        // this can be done in parallel

        for(int i = offset; i < S; i++){
            p_sum[i] = b[i]+b[i-range];
        }
        
        offset *= 2;
    }
    return p_sum;
}



std::vector<std::vector<int>> serial_partition(std::vector<int> &src, int r)
{   
    int N = src.size();
    std::vector<std::vector<int>> dest(N/r,std::vector<int>(r,0));
    int i,j;

    for(i = 0; i < N/r; i++)
        for(j = 0; j < r; j++)
            dest[i][j] = src[i*r+j];
    return dest;
}



void serial_init_number(std::vector<std::vector<int>> &number, std::vector<std::vector<int>> &b, int N, int r)
{
    int j;

    for(int i = 0; i < N/r; i++)
    {
        for(j = 0; j < r; j++)
        {
            number[b[i][j]][i]++;
        }
    }
}


void serial_init_serial(std::vector<int> &serial,std::vector<std::vector<int>> &b,int N, int r)
{
    int count;
    int j,k;

    for(int i = 0; i < N/r; i++)
    {
        serial[i*r] = 0;

        
        for(j = 1; j < r; j++)
        {
            count = 0;

            for(k = j-1; k >= 0; k--)
            {
                if(b[i][j] == b[i][k])
                    count++;
            }
            serial[i*r+j] = count;
        }
    }
}



std::vector<int> serial_sort(std::vector<int> &a, int r)
{
    int N = a.size();
    std::vector<std::vector<int>> number(r,std::vector<int>(N/r,0));
    std::vector<std::vector<int>> prefix_sums(r,std::vector<int>(N/r,0));
    std::vector<int> serial(N);
    std::vector<std::vector<int>> b;
    std::vector<int> cardinality(r,0);
    std::vector<int> global(r,0);
    std::vector<int> result(N);
    b = serial_partition(a,r);
    //print_2dvector(b);
    


    serial_init_number(number,b,N,r);
    serial_init_serial(serial,b,N,r);



    for(int i = 0; i< r; i++)
    {
        prefix_sums[i] = serial_prefix_sum(number[i],N/r);
    }

    int j,sum;

    for(int i = 0; i < r; i++)
    {   
        sum = 0;

        for(j = 0; j < N/r; j++)
        {
            sum += number[i][j];
        } 
        cardinality[i] = sum;
    }

    global = serial_prefix_sum(cardinality,r);

    /////////////////////////////////////////////////////////////////

    int s,gl,pf;

    for(int i = 0; i < N; i++)
    {
        if(a[i] > 0)
            gl = global[a[i]-1];
        else 
            gl = 0; 
        
        s = ceil(i/r)-1;
        if(s >= 0)
            pf = prefix_sums[a[i]][s];
        else 
            pf = 0;
        result[serial[i]+pf+gl] = a[i];
    }

    return result;
}
