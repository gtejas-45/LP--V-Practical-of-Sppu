// ======================================================
// Parallel Bubble Sort (Odd-Even Transposition Sort)
// OpenMP Safe Version
// ======================================================

#include <iostream>
#include <omp.h>

using namespace std;

// Swap function (safe in this context because pairs don't overlap)
void swapValues(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Sequential Bubble Sort
void sequentialBubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swapValues(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

// Parallel Bubble Sort (Odd-Even Transposition Sort)
void parallelBubbleSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        // EVEN phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
            {
                swapValues(arr[j], arr[j + 1]);
            }
        }

        // ODD phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
            {
                swapValues(arr[j], arr[j + 1]);
            }
        }
    }
}

// ================= MAIN =================
int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int *arr1 = new int[n];
    int *arr2 = new int[n];

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr1[i];
        arr2[i] = arr1[i];
    }

    // -------- Sequential --------
    double start = omp_get_wtime();
    sequentialBubbleSort(arr1, n);
    double end = omp_get_wtime();

    cout << "\nSequential Sorted Array:\n";
    for (int i = 0; i < n; i++)
        cout << arr1[i] << " ";

    cout << "\nTime (Sequential): " << end - start << " sec\n";

    // -------- Parallel --------
    start = omp_get_wtime();

    parallelBubbleSort(arr2, n);

    end = omp_get_wtime();

    cout << "\nParallel Sorted Array:\n";
    for (int i = 0; i < n; i++)
        cout << arr2[i] << " ";

    cout << "\nTime (Parallel): " << end - start << " sec\n";

    delete[] arr1;
    delete[] arr2;

    return 0;
}
