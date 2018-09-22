#include <cstdio>
typedef long long lli;

lli tree[1000001];
lli arr[1000001];
int n, m, k;

void update(int i, lli diff)
{
    while(i <= n) {
        tree[i] += diff;
        i += (i & -i);
    }
}

lli sum(int i)
{
    lli s = 0;
    while(i > 0) {
        s += tree[i];
        i -= (i & -i);
    }

    return s;
}

lli sum(int a, int b)
{
    return sum(b) - sum(a-1);
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);

    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &arr[i]);
        update(i, arr[i]);
    }

    for(int i = 1; i <= m+k; i++)
    {
        int a, b;
        lli c;
        scanf("%d %d %lld", &a, &b, &c);
        if(a == 1)
        {
            update(b, c - arr[b]);
            arr[b] = c;
        }
        if(a == 2) printf("%lld\n", sum(b, c));
    }
}
