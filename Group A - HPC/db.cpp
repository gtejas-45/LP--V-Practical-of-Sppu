#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

struct Record {
    int id;
    int salary;
    int age;
};

int main() {
    vector<Record> db;

    for (int i = 0; i < 100000; i++) {
        db.push_back({i, rand() % 100000, rand() % 50 + 20});
    }

    double sum = 0;
    int count = 0;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum,count)
    for (int i = 0; i < db.size(); i++) {
        if (db[i].age > 30) {
            sum += db[i].salary;
            count++;
        }
    }

    double avg = sum / count;
    double end = omp_get_wtime();

    cout << "Average Salary: " << avg << endl;
    cout << "Time: " << end - start << endl;
}
