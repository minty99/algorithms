#include <cstdio>
#include <iostream>
#include <cassert>
#include <array>
#include <queue>
#include <deque>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <bitset>
#include <random>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

typedef long long int lli;
typedef pair<int, int> pii;
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long long int ulli;

array<int, 3> edge[100000]; // Kruskal needs edges only!
vector<int> parent(10001);
lli tot = 0;

int _find(int u) {
    return parent[u] == u ? u : (parent[u] = _find(parent[u]));
}

void _union(int u, int v) {
    parent[_find(v)] = _find(u);
}

lli Kruskal(array<int, 3> E[], int e)
{
    lli ret = 0;
    for(int i = 0; i < e; i++)
    {
        if(_find(E[i][1]) == _find(E[i][2])) continue;
        else
        {
            _union(E[i][1], E[i][2]);
            ret += E[i][0];
        }
    }
    return ret;
}
int main()
{
    freopen("in.txt", "r", stdin);

    int v, e;
    scanf("%d %d", &v, &e);

    for(int i = 0; i < e; i++) scanf("%d %d %d", &edge[i][1], &edge[i][2], &edge[i][0]);
    sort(edge, edge+e);
    for(int i = 1; i <= v; i++) parent[i] = i;
    printf("%lld", Kruskal(edge, e));
}
