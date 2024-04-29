#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void merge(vector<int> &arr, int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> left(n1);
    vector<int> right(n2);
    for (int i = 0; i < n1; i++)
    {
        left[i] = arr[low + i];
    }

    for (int i = 0; i < n2; i++)
    {
        right[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergesort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void para_mergesort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                mergesort(arr, low, mid);
            }
#pragma omp section
            {
                mergesort(arr, mid + 1, high);
            }
        }

        merge(arr, low, mid, high);
    }
}

void bubblesort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void para_bubblesort(vector<int> &arr)
{
    int n = arr.size();

    for (int i = 0; i < n - 1; i++)
    {
#pragma omp parallel for
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main()
{
    int n = 10000;
    vector<int> arr, arr_copy;
    arr.resize(n);
    arr_copy.resize(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
        arr_copy[i] = arr[i];
    }

    auto start = high_resolution_clock::now();
    bubblesort(arr);
    auto end = high_resolution_clock::now();
    auto seq_bubble = duration_cast<milliseconds>(end - start);
    cout << "Sequential bubble sort time : " << seq_bubble.count() << endl;

    start = high_resolution_clock::now();
    para_bubblesort(arr_copy);
    end = high_resolution_clock::now();
    auto para_bubble = duration_cast<milliseconds>(end - start);
    cout << "Parallel bubble sort time : " << para_bubble.count() << endl;

    start = high_resolution_clock::now();
    mergesort(arr, 0, n-1);
    end = high_resolution_clock::now();
    auto seq_mergesort = duration_cast<milliseconds>(end - start);
    cout << "Sequential merge sort time : " << seq_mergesort.count() << endl;

    start = high_resolution_clock::now();
    para_mergesort(arr_copy, 0, n-1);
    end = high_resolution_clock::now();
    auto para_mergesort = duration_cast<milliseconds>(end - start);
    cout << "Parallel merge sort time : " << para_mergesort.count() << endl;
}