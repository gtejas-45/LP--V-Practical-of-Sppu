#include <iostream>
#include <cuda_runtime.h>

using namespace std;

// ---------------- CUDA KERNEL ----------------
__global__ void matmul(int *A, int *B, int *C, int N)
{
    int Row = blockIdx.y * blockDim.y + threadIdx.y;
    int Col = blockIdx.x * blockDim.x + threadIdx.x;

    if (Row < N && Col < N)
    {
        int sum = 0;

        for (int k = 0; k < N; k++)
        {
            sum += A[Row * N + k] * B[k * N + Col];
        }

        C[Row * N + Col] = sum;
    }
}

// ---------------- MAIN ----------------
int main()
{
    int N = 4;
    int size = N * N * sizeof(int);

    int *A, *B, *C;
    int *d_A, *d_B, *d_C;

    // -------- Host memory --------
    A = (int*)malloc(size);
    B = (int*)malloc(size);
    C = (int*)malloc(size);

    // -------- Initialize matrices --------
    cout << "Matrix A:\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i * N + j] = i + j;
            cout << A[i * N + j] << " ";
        }
        cout << endl;
    }

    cout << "\nMatrix B:\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            B[i * N + j] = i * j;
            cout << B[i * N + j] << " ";
        }
        cout << endl;
    }

    // -------- Device memory --------
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, size);

    // -------- Copy Host → Device --------
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    // -------- Kernel config --------
    dim3 blockSize(16, 16);
    dim3 gridSize((N + 15) / 16, (N + 15) / 16);

    matmul<<<gridSize, blockSize>>>(d_A, d_B, d_C, N);

    cudaDeviceSynchronize();

    // -------- Copy Device → Host --------
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    // -------- Result --------
    cout << "\nResult Matrix (C = A x B):\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << C[i * N + j] << " ";
        }
        cout << endl;
    }

    // -------- Free memory --------
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(A);
    free(B);
    free(C);

    return 0;
}
