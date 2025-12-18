#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v;
};

int find(vector<int> &parent, int x)
{
    if (parent[x] != x)
        parent[x] = find(parent, parent[x]);
    return parent[x];
}

void unite(vector<int> &parent, vector<int> &rank, int x, int y)
{
    int u = find(parent, x);
    int v = find(parent, y);

    if (u != v)
    {
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else
        {
            parent[v] = u;
            rank[u]++;
        }
    }
}

int randomMinCut(int V, vector<Edge> edges)
{
    vector<int> parent(V + 1), rank(V + 1, 0);
    for (int i = 1; i <= V; i++)
        parent[i] = i;

    int temp = V;

    while (temp > 2)
    {
        int idx = rand() % edges.size();
        int u = find(parent, edges[idx].u);
        int v = find(parent, edges[idx].v);

        if (u != v)
        {
            unite(parent, rank, u, v);
            temp--;
        }
    }

    int cut = 0;
    for (auto it : edges)
    {
        if (find(parent, it.u) != find(parent, it.v))
            cut++;
    }

    return cut;
}

int main()
{
    int V = 4;
    vector<Edge> edges = {{1, 2}, {1, 3}, {1, 4}, {3, 4}, {2, 4}};

    int minCut = randomMinCut(V, edges);
    cout << "Random Min Cut: " << minCut << endl;

    return 0;
}
