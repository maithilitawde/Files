#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Graph
{
    int V;
    vector<vector<int>> adj;

public:
    Graph(int v)
    {
        this->V = v;
        adj.resize(v);
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void parallel_bfs(int start)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        while (!q.empty())
        {

            {
                int u;


                {
                    u = q.front();
                    q.pop();
                    cout << u << " ";
                }

                if (!adj[u].size() == 0)
                {
#pragma omp parallel for
                    for (int i = 0; i < adj[u].size(); ++i)
                    {
                        int x = adj[u][i];

                        if (!visited[x])
                        {
#pragma omp critical // other threads wait
                            {
                                visited[x] = true;
                                q.push(x);
                            }
                        }
                    }
                }
            }
        }
    }

    void seq_bfs(int start)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            {
                int u;

                {
                    u = q.front();
                    q.pop();
                    cout << u << " ";
                }

                if (!adj[u].size() == 0)
                {

                    for (int i = 0; i < adj[u].size(); ++i)
                    {
                        int x = adj[u][i];

                        if (!visited[x])
                        {
                            visited[x] = true;
                            q.push(x);
                        }
                    }
                }
            }
        }
    }

    void parallel_dfs(int start)
    {
        vector<bool> visited(V, false);
        parallel_dfs_util(start, visited);
    }

    void parallel_dfs_util(int start, vector<bool> &visited)
    {
        visited[start] = true;
        cout << start << " ";

#pragma omp parallel for
        for (int i = 0; i < adj[start].size(); i++)
        {
            int y = adj[start][i];
            if (!visited[y])
            {
                parallel_dfs_util(y,visited);
            }
        }
    }

    void seq_dfs(int start)
    {
        vector<bool> visited(V, false);
        seq_dfs_util(start, visited);
    }

    void seq_dfs_util(int start, vector<bool> &visited)
    {
        visited[start] = true;
        cout << start << " ";

        for (int i = 0; i < adj[start].size(); i++)
        {
            int y = adj[start][i];
            if (!visited[y])
            {
                seq_dfs_util(y, visited);
            }
        }
    }

    
};

int main()
{
    cout << "Enter the no of vertices : ";
    int v;
    cin >> v;

    cout << "Enter the no of edges : ";
    int e;
    cin >> e;

    Graph g(v);
    for (int i = 0; i < e; i++)
    {
        cout << "Enter the vertex 1 and 2 : ";
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    auto start = high_resolution_clock::now();
    cout << "Parallel Bfs : ";
    g.parallel_bfs(0);
    cout<<endl;
    auto end = high_resolution_clock::now();
    auto para_bfs = duration_cast<milliseconds>(end - start);

    start = high_resolution_clock::now();
    cout << "Sequential bfs : ";
    g.seq_bfs(0);
    cout<<endl;
    end = high_resolution_clock::now();
    auto seq_bfs = duration_cast<milliseconds>(end - start);

    start = high_resolution_clock::now();
    cout << "Parallel dfs : ";
    g.parallel_dfs(0);
    cout<<endl;
    end = high_resolution_clock::now();
    auto para_dfs = duration_cast<milliseconds>(end - start);

    start = high_resolution_clock::now();
    cout << "Sequential dfs : ";
    g.seq_dfs(0);
    cout<<endl;
    end = high_resolution_clock::now();
    auto seq_dfs = duration_cast<milliseconds>(end - start);

    cout << "Sequential BFS Time: " << seq_bfs.count() << " milliseconds" << endl;
    cout << "Parallel BFS Time: " << para_bfs.count() << " milliseconds" << endl;
    cout << "Sequential DFS Time: " << seq_dfs.count() << " milliseconds" << endl;
    cout << "Paralell DFS Time: " << para_dfs.count() << " milliseconds" << endl;
}