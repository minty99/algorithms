#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bitset>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
vector<int> G[1001], V[1001];
bitset<1001> visited;
int d[1001];
priority_queue<pii, vector<pii>, greater<pii>> pq;

int main()
{
    // freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        G[a].push_back(b);
        V[a].push_back(c);
    }

    int from, to;
    scanf("%d %d", &from, &to);
    for(int i = 1; i <= n; i++) d[i] = 1e9;
    d[from] = 0;
    int curr = from;
    while(!visited[to])
    {
        visited[curr] = true;
        for(int i = 0; i < G[curr].size(); i++)
        {
            int k = G[curr][i];
            int v = V[curr][i];
            d[k] = min(d[curr] + v, d[k]);
            pq.emplace(d[k], k);
        }
        if(curr == to) break;
        while(visited[pq.top().second]) pq.pop();
        curr = pq.top().second;
        pq.pop();
    }

    printf("%d", d[to]);
}
