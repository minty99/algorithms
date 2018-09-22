#include <cstdio>
typedef long long lli;

int n, m, k;
lli arr[1200000];
lli tree[4000000];

lli init(int node, int start, int end)
{
    if(start == end) return tree[node] = arr[start];
    else return tree[node] = init(node*2, start, (start+end)/2) + init(node*2+1, (start+end)/2+1, end);
}

void update(int node, int start, int end, int index, lli diff)
{
    if(start <= index && index <= end)
    {
        tree[node] += diff;
        if(start != end)
        {
            update(node*2, start, (start+end)/2, index, diff);
            update(node*2+1, (start+end)/2+1, end, index, diff);
        }
    }
}

lli sum(int node, int start, int end, int left, int right)
{
    if(left <= start && end <= right) return tree[node];
    if(right < start || end < left) return 0;
    return sum(node*2, start, (start+end)/2, left, right) + sum(node*2+1, (start+end)/2+1, end, left, right);
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);

    for(int i = 1; i <= n; i++) scanf("%lld", &arr[i]);
    init(1, 1, n);

    for(int i = 1; i <= m+k; i++)
    {
        int a, b;
        lli c;
        scanf("%d %d %lld", &a, &b, &c);
        if(a == 1)
        {
            update(1, 1, n, b, c - arr[b]);
            arr[b] = c;
        }
        if(a == 2) printf("%lld\n", sum(1, 1, n, b, c));
    }
}
