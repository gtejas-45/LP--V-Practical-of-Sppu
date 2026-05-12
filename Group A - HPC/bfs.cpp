// ==========================================================
// Parallel BFS using OpenMP (Graph Input Version)
// ==========================================================

#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

const int MAX = 100000;

vector<int> graph[MAX];
bool visited[MAX];

// Lock for thread safety
omp_lock_t lock;

// Parallel BFS
void bfs(int start)
{
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++)
        {
            int curr;

            // Safe queue access
            omp_set_lock(&lock);

            if (!q.empty())
            {
                curr = q.front();
                q.pop();
                cout << curr << " ";
            }

            omp_unset_lock(&lock);

            // Explore neighbors
            for (int j = 0; j < graph[curr].size(); j++)
            {
                int adj = graph[curr][j];

                omp_set_lock(&lock);

                if (!visited[adj])
                {
                    visited[adj] = true;
                    q.push(adj);
                }

                omp_unset_lock(&lock);
            }
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

    // Initialize visited array
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Initialize lock
    omp_init_lock(&lock);

    cout << "\nBFS Traversal: ";

    bfs(start);

    cout << endl;

    // Destroy lock
    omp_destroy_lock(&lock);

    return 0;
}
