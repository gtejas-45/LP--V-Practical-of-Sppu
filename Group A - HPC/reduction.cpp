#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

// ---------------- MIN ----------------
void min_reduction(vector<int>& arr) {
    int min_value = INT_MAX;

    #pragma omp parallel for reduction(min:min_value)
    for (int i = 0; i < arr.size(); i++) {
        min_value = (arr[i] < min_value) ? arr[i] : min_value;
    }

    cout << "Minimum value: " << min_value << endl;
}

// ---------------- MAX ----------------
void max_reduction(vector<int>& arr) {
    int max_value = INT_MIN;

    #pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < arr.size(); i++) {
        max_value = (arr[i] > max_value) ? arr[i] : max_value;
    }

    cout << "Maximum value: " << max_value << endl;
}

// ---------------- SUM ----------------
void sum_reduction(vector<int>& arr) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }

    cout << "Sum: " << sum << endl;
}

// ---------------- AVERAGE ----------------
void average_reduction(vector<int>& arr) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }

    double avg = (arr.size() > 0) ? (double)sum / arr.size() : 0;

    cout << "Average: " << avg << endl;
}

// ---------------- MAIN ----------------
int main() {
    vector<int> arr;
    int n, x;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> x;
        arr.push_back(x);
    }

    cout << "\n--- Parallel Reduction Results ---\n";

    min_reduction(arr);
    max_reduction(arr);
    sum_reduction(arr);
    average_reduction(arr);

    return 0;
}
