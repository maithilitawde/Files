#include<iostream>

using namespace std;

__global__ void multiply (int *A , int *B , int *C, int size)
{
    int row = blockIdx.y*blockDim.y+threadIdx.y;
    int col = blockIdx.x*blockDim.x+threadIdx.x;

    if(row<size && col<size)
    {
        int sum = 0 ;
        for(int i = 0 ; i<size ; i++)
        {
            sum += A[row*size + i]*B[i*size + col];
        }
        C[row*size+col] = sum;
    }
}

void initialize(int *matrix , int size)
{
    for(int i = 0 ;i<size ; i++)
    {
        matrix[i] = rand()%10;
    }
}

void print(int *matrix , int size)
{
    for(int row = 0 ; row<size ; row++)
    {
        for(int col = 0 ; col<size ; col++)
        {
            cout<<matrix[row*size+col]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    int N = 2;
    int matrixsize = N*N;
    size_t matrixbytes = matrixsize*sizeof(int);

    int *A, *B, *C;

    A = new int[matrixsize];
    B = new int[matrixsize];
    C = new int[matrixsize];

    initialize(A,matrixsize);
    initialize(B,matrixsize);

    cout<<"A : "<<endl;
    print(A,N);
    cout<<endl;

    cout<<"B : "<<endl;
    print(B,N);
    cout<<endl;

    int *X,*Y,*Z;

    cudaMalloc(&X , matrixbytes);
    cudaMalloc(&Y , matrixbytes);
    cudaMalloc(&Z , matrixbytes);

    cudaMemcpy(X,A,matrixbytes , cudaMemcpyHostToDevice);
    cudaMemcpy(Y,B,matrixbytes , cudaMemcpyHostToDevice);

    int Threads = 2;
    int Blocks = (N)/Threads;

    dim3 threads(Threads, Threads);
    dim3 blocks(Blocks,Blocks);

    multiply<<<blocks,threads>>>(X,Y,Z,N);

    cudaMemcpy(C,Z,matrixbytes , cudaMemcpyDeviceToHost);
    cout<<"C : "<<endl;
    print(C,N);
    cout<<endl;

    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);







}