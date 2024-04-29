#include<bits/stdc++.h>
#include<omp.h>
#include<chrono>

using namespace std;
using namespace std::chrono;


int minx(vector<int>&arr)
{
    int n = arr.size();
    int minval = arr[0];

    for(int i = 0 ; i<arr.size(); i++)
    {
        if(minval>arr[i])
        {
            minval = arr[i];
        }
    }

    return minval;
}

int para_minx(vector<int>&arr)
{
    int n = arr.size();
    int minval = arr[0];
    #pragma omp parallel for reduction(min:minval)
    for(int i = 0 ; i<arr.size(); i++)
    {
        if(minval>arr[i])
        {
            minval = arr[i];
        }
    }

    return minval;
}

int maxp(vector<int>&arr)
{
    int n = arr.size();
    int maxval = arr[0];

    for(int i = 0 ; i<arr.size(); i++)
    {
        if(maxval<arr[i])
        {
            maxval = arr[i];
        }
    }

    return maxval;
}

int para_maxp(vector<int>&arr)
{
    int n = arr.size();
    int maxval = arr[0];
    #pragma omp parallel for reduction(max:maxval)
    for(int i = 0 ; i<arr.size(); i++)
    {
        if(maxval<arr[i])
        {
            maxval = arr[i];
        }
    }

    return maxval;
}

int sumx(vector<int>&arr)
{
    int n = arr.size();
    int sum = 0;
    for(int i = 0 ; i<n ;i++)
    {
        sum+=arr[i];
    }

    return sum;
}

int para_sumx(vector<int>&arr)
{
    int n = arr.size();
    int sum = 0;
    #pragma parallel for reduction(+:sum)
    for(int i = 0 ; i<n ;i++)
    {
        sum+=arr[i];
    }

    return sum;
}

int avgx(vector<int>&arr)
{
    int n = arr.size();
    return (double)sumx(arr)/n;
}

int para_avgx(vector<int>&arr)
{
    int n = arr.size();
    return (double)para_sumx(arr)/n;
}

int main()
{
    int n = 1000000;

    vector<int>arr(n);

    for(int i = 0 ; i<n ;i++)
    {
        arr[i] = rand()%50000;
    }

    auto start = high_resolution_clock::now();
    para_minx(arr);
    auto end = high_resolution_clock::now();
    auto para_min = duration_cast<nanoseconds>(end-start);
    cout<<"Parallel min : "<<para_min.count()<<endl;

    start = high_resolution_clock::now();
    minx(arr);
    end = high_resolution_clock::now();
    auto seq_min = duration_cast<nanoseconds>(end-start);
    cout<<"Sequential min : "<<seq_min.count()<<endl;

    start = high_resolution_clock::now();
    para_maxp(arr);
    end = high_resolution_clock::now();
    auto para_max = duration_cast<nanoseconds>(end-start);
    cout<<"Parallel max : "<<para_max.count()<<endl;

    start = high_resolution_clock::now();
    maxp(arr);
    end = high_resolution_clock::now();
    auto seq_max = duration_cast<nanoseconds>(end-start);
    cout<<"Sequential max : "<<seq_max.count()<<endl;

    start = high_resolution_clock::now();
    sumx(arr);
    end = high_resolution_clock::now();
    auto seq_sum = duration_cast<nanoseconds>(end-start);
    cout<<"Sequential sum : "<<seq_sum.count()<<endl;

    start = high_resolution_clock::now();
    para_sumx(arr);
    end = high_resolution_clock::now();
    auto para_sum = duration_cast<nanoseconds>(end-start);
    cout<<"Parallel sum : "<<para_sum.count()<<endl;
    
    start = high_resolution_clock::now();
    para_avgx(arr);
    end = high_resolution_clock::now();
    auto para_avg = duration_cast<nanoseconds>(end-start);
    cout<<"Parallel avg : "<<para_avg.count()<<endl;

    start = high_resolution_clock::now();
    avgx(arr);
    end = high_resolution_clock::now();
    auto seq_avg = duration_cast<nanoseconds>(end-start);
    cout<<"Sequential avg : "<<seq_avg.count()<<endl;


}


