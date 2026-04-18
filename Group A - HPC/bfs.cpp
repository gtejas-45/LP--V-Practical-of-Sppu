//BFS

// ==========================================================
// Practical 1(A): Parallel BFS using OpenMP
// ==========================================================

#include <iostream>
#include <queue>
#include <omp.h>
using namespace std;

// Tree node structure
struct Node {
    int data;
    Node *left, *right;
};

// Insert node level-wise
Node* insert(Node* root, int data) {
    if (!root) {
        root = new Node;
        root->data = data;
        root->left = root->right = NULL;
        return root;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        // Insert left
        if (!temp->left) {
            temp->left = new Node{data, NULL, NULL};
            return root;
        } else {
            q.push(temp->left);
        }

        // Insert right
        if (!temp->right) {
            temp->right = new Node{data, NULL, NULL};
            return root;
        } else {
            q.push(temp->right);
        }
    }
    return root;
}

// Parallel BFS
void bfs(Node* root) {
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            Node* curr;

            // Critical section for queue
            #pragma omp critical
            {
                curr = q.front();
                q.pop();
                cout << curr->data << " ";
            }

            // Push children
            #pragma omp critical
            {
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }
    }
}

int main() {
    Node* root = NULL;
    int data;
    char ch;

    do {
        cout << "Enter data: ";
        cin >> data;
        root = insert(root, data);

        cout << "Add more nodes (y/n)? ";
        cin >> ch;

    } while (ch == 'y' || ch == 'Y');

    cout << "\nBFS Traversal:\n";
    bfs(root);

    return 0;
}
