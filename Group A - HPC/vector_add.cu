#include <iostream>
#include <cuda_runtime.h>

using namespace std;

// ---------------- CUDA KERNEL ----------------
__global__ void addVectors(int *A, int *B, int *C, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n)
    {
        C[i] = A[i] + B[i];
    }
}

// ---------------- MAIN FUNCTION ----------------
int main()
{
    int n = 1000000;
    int size = n * sizeof(int);

    int *A, *B, *C;
    int *d_A, *d_B, *d_C;

    // -------- Host memory allocation --------
    A = (int*)malloc(size);
    B = (int*)malloc(size);
    C = (int*)malloc(size);

    // -------- Initialize arrays --------
    for (int i = 0; i < n; i++)
    {
        A[i] = i;
        B[i] = i * 2;
    }

    // -------- Device memory allocation --------
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    // -------- Copy Host → Device --------
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    // -------- Launch kernel --------
    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;

    addVectors<<<gridSize, blockSize>>>(d_A, d_B, d_C, n);

    // Wait for GPU to finish
    cudaDeviceSynchronize();

    // -------- Copy Device → Host --------
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    // -------- Print first 10 values --------
    cout << "Result (first 10 elements):\n";
    for (int i = 0; i < 10; i++)
    {
        cout << C[i] << " ";
    }
    cout << endl;

    // -------- Free memory --------
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
}
