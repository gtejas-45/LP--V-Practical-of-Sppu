#include <iostream>
#include <omp.h>

using namespace std;

// ---------------- MERGE FUNCTION ----------------
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

// ---------------- SEQUENTIAL MERGE SORT ----------------
void sequentialMergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;

        sequentialMergeSort(arr, l, m);
        sequentialMergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// ---------------- PARALLEL MERGE SORT ----------------
void parallelMergeSort(int arr[], int l, int r, int depth = 0)
{
    if (l < r)
    {
        int m = (l + r) / 2;

        // limit parallel threads (important fix)
        if (depth < 4)
        {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSort(arr, l, m, depth + 1);

                #pragma omp section
                parallelMergeSort(arr, m + 1, r, depth + 1);
            }
        }
        else
        {
            sequentialMergeSort(arr, l, m);
            sequentialMergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

// ---------------- MAIN ----------------
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

    // ---------- SEQUENTIAL ----------
    double start = omp_get_wtime();
    sequentialMergeSort(arr1, 0, n - 1);
    double end = omp_get_wtime();

    cout << "\nSequential Sorted Array:\n";
    for (int i = 0; i < n; i++)
        cout << arr1[i] << " ";

    cout << "\nTime (Sequential): " << end - start << " sec\n";

    // ---------- PARALLEL ----------
    start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        parallelMergeSort(arr2, 0, n - 1);
    }

    end = omp_get_wtime();

    cout << "\nParallel Sorted Array:\n";
    for (int i = 0; i < n; i++)
        cout << arr2[i] << " ";

    cout << "\nTime (Parallel): " << end - start << " sec\n";

    delete[] arr1;
    delete[] arr2;

    return 0;
}
