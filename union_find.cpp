#include <cstdio>
#include <vector>
using namespace std;

vector<int> parent;

int _find(int u) {
    return parent[u] == u ? u : (parent[u] = _find(parent[u]));
}

void _union(int u, int v) {
    parent[_find(v)] = _find(u);
}

int main()
{
    // freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d %d", &n, &m);
    parent.resize(n+1);

    for(int i = 0; i <= n; i++) parent[i] = i;

    for(int i = 1; i <= m; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        if(a == 0) _union(b, c);
        else printf("%s\n", _find(b) == _find(c) ? "YES" : "NO");
    }
}
