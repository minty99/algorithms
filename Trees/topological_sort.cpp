#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

vector<int> adj[33000];
int indeg[33000];
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for(int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        indeg[b]++;
    }

    queue<int> Q;
    for(int i = 1; i <= n; i++)
    {
        if(indeg[i] == 0) Q.push(i);
    }

    vector<int> topo;

    for(int i = 1; i <= n; i++)
    {
        int next = Q.front();
        Q.pop();
        topo.push_back(next);
        for(int j = 0; j < adj[next].size(); j++)
        {
            indeg[adj[next][j]]--;
            if(indeg[adj[next][j]] == 0) Q.push(adj[next][j]);
        }
    }

    for(int i = 0; i < topo.size(); i++) printf("%d ", topo[i]);
}
