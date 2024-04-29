#include<iostream>
using namespace std;

__global__ void add(int*A , int*B , int*C , int size)
{
    int tid = blockIdx.x*blockDim.x + threadIdx.x;

    if(tid<size)
    {
        C[tid] = A[tid]+B[tid];
    }
    
}

void initialize(int *vector , int size)
{
    for(int i = 0 ; i<size ; i++)
    {
        vector[i] = rand()%10;
    }
}

void print(int *vector , int size)
{
    for(int i= 0 ; i<size ; i++)
    {
        cout<<vector[i]<<" ";
    }
}

int main()
{
    int N = 10;
    int vectorsize = N;

    size_t vectorbytes = vectorsize*sizeof(int);
    int *A ,*B,*C;

    A = new int[vectorsize];   //allocate
    B = new int[vectorsize];
    C = new int[vectorsize];

    initialize(A,N);
    initialize(B,N);

    cout<<"A : ";
    print(A,N);
    cout<<endl;

    cout<<"B : ";
    print(B,N);
    cout<<endl;

    int *X,*Y,*Z;

    cudaMalloc(&X, vectorbytes);  //memory allocate
    cudaMalloc(&Y, vectorbytes);
    cudaMalloc(&Z, vectorbytes);

    cudaMemcpy(X , A , vectorbytes , cudaMemcpyHostToDevice);  //memory allocate from local to cuda
    cudaMemcpy(Y , B , vectorbytes , cudaMemcpyHostToDevice);

    int threadsperblock = 256;       
    int blockspergrid = (N+ threadsperblock -1)/threadsperblock;   //to see if all elements are convered 

    add<<<blockspergrid, threadsperblock>>>(X,Y,Z,N);

    cudaMemcpy(C, Z , vectorbytes , cudaMemcpyDeviceToHost);

    cout<<"C : ";
    print(C,N);
    cout<<endl;

    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);

    





    

}