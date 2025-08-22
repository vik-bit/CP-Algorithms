#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, size; 

    DSU(int n) {  // initialize for n nodes (0..n-1)
        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    // Path compression:
    // While finding the root of x, we make every node on the path
    // point directly to the root. This flattens the tree.
    // -> Ensures nearly O(1) amortized time (Inverse Ackermann).
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // recursive compression
        return parent[x];
    }

    // Union by size:
    // Attach the smaller tree under the bigger one.
    // -> Keeps trees shallow, improves efficiency with path compression.
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // already in same set
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

    // Check if two nodes belong to same component
    bool same(int a, int b) {
        return find(a) == find(b);
    }

    // Get the size of the component containing x
    int getSize(int x) {
        return size[find(x)];
    }
};

int main() {
    int n = 5;
    DSU dsu(n);

    dsu.unite(0, 1);
    dsu.unite(1, 2);

    cout << dsu.same(0, 2) << "\n"; // 1 (true)
    cout << dsu.same(0, 3) << "\n"; // 0 (false)
    cout << dsu.getSize(0) << "\n"; // 3
}
