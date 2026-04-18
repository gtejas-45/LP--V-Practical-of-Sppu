//dfs
// ==========================================================
// Parallel DFS using OpenMP (Safe Version)
// ==========================================================

#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

const int MAX = 100000;

vector<int> graph[MAX];
bool visited[MAX];

// Mutex for thread safety
omp_lock_t lock;

// Parallel DFS
void dfs(int start)
{
    stack<int> s;
    s.push(start);

    while (!s.empty())
    {
        int curr = s.top();
        s.pop();

        // Lock for safe visited check
        omp_set_lock(&lock);

        if (!visited[curr])
        {
            visited[curr] = true;
            cout << curr << " ";
        }
        else
        {
            omp_unset_lock(&lock);
            continue;
        }

        omp_unset_lock(&lock);

        // Parallel exploration of neighbors
        #pragma omp parallel for
        for (int i = 0; i < graph[curr].size(); i++)
        {
            int adj = graph[curr][i];

            omp_set_lock(&lock);

            if (!visited[adj])
            {
                s.push(adj);
            }

            omp_unset_lock(&lock);
        }
    }
}

int main()
{
    int n, m, start;

    cout << "Enter number of nodes, edges, start node:\n";
    cin >> n >> m >> start;

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Initialize visited safely
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Initialize lock
    omp_init_lock(&lock);

    cout << "\nDFS Traversal: ";

    dfs(start);

    cout << endl;

    // Destroy lock
    omp_destroy_lock(&lock);

    return 0;
}
