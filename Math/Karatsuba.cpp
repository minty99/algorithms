#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

vector<int> a, b;
vector<int> karatsuba(const vector<int> &a, const vector<int> &b);
void addTo(vector<int> &to, const vector<int> &a, int k);
void normalize(vector<int> &v);
vector<int> slow_multiply(const vector<int> &a, const vector<int> &b);
vector<int> operator+(const vector<int> &a, const vector<int> &b);
vector<int> operator-(const vector<int> &a, const vector<int> &b);

int main()
{
    char sa[330000], sb[330000];
    scanf("%s %s", sa, sb);
    bool plus = true;
    if(sa[0] == '-') plus = !plus;
    if(sb[0] == '-') plus = !plus;
    for(int i = strlen(sa)-1; i >= 0; i--)
    {
        if(sa[i] == '-') continue;
        a.push_back(sa[i] - '0');
    }
    for(int i = strlen(sb)-1; i >= 0; i--)
    {
        if(sb[i] == '-') continue;
        b.push_back(sb[i] - '0');
    }

    vector<int> result = karatsuba(a, b);

    if(result.size() == 1 && result[0] == 0) printf("0");
    else
    {
        if(!plus) printf("-");
        for(int i = result.size()-1; i >= 0; i--) printf("%d", result[i]);
    }
}

// a = a1 * 10^k + a0, b = b1 * 10^k + b0
// a * b = (a1*b1) * 10^2k + (a1*b0 + a0*b1) * 10^k + a0*b0
// a1*b1 = z2, a1*b0+a0*b1 = z1, a0*b0 = z0
// (a1+a0)(b1+b0) = z2 + z1 + z0
// So, z1 = (a1+a0)(b1+b0) - z2 - z1
// Time Complexity: O(n^lg3)
vector<int> karatsuba(const vector<int> &a, const vector<int> &b)
{
    int an = a.size(), bn = b.size();
    if(an < bn) return karatsuba(b, a);
    if(an <= 50) return slow_multiply(a, b);
    int half = an / 2;
    vector<int> a0(a.begin(), a.begin()+half);
    vector<int> a1(a.begin()+half, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(bn, half));
    vector<int> b1(b.begin() + min<int>(bn, half), b.end());

    vector<int> z2 = karatsuba(a1, b1);
    vector<int> z0 = karatsuba(a0, b0);
    vector<int> z1 = karatsuba(a0+a1, b0+b1) - z0 - z2;

    vector<int> result;
    addTo(result, z0, 0);
    addTo(result, z1, half);
    addTo(result, z2, half*2);
    return result;
}

vector<int> operator+(const vector<int> &a, const vector<int> &b)
{
    vector<int> result(a);
    result.resize(max<int>(a.size(), b.size()));
    int k = 0;
    for(int n : b) result[k++] += n;
    normalize(result);
    return result;
}

vector<int> operator-(const vector<int> &a, const vector<int> &b)
{
    vector<int> result(a);
    result.resize(max<int>(a.size(), b.size()));
    int k = 0;
    for(int n : b) result[k++] -= n;
    normalize(result);
    return result;
}

void addTo(vector<int> &to, const vector<int> &a, int k)
{
    to.resize(max<int>(to.size(), k + a.size()), 0);
    for(int n : a) to[k++] += n;
    normalize(to);
}

void normalize(vector<int> &v)
{
    v.push_back(0);
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i] >= 0)
        {
            v[i+1] += v[i] / 10;
            v[i] %= 10;
        }
        else
        {
            int borrow = (abs(v[i]) + 9) / 10;
            v[i+1] -= borrow;
            v[i] += borrow * 10;
        }
    }
    while(v.size() > 1 && v.back() == 0) v.pop_back();
}

vector<int> slow_multiply(const vector<int> &a, const vector<int> &b)
{
    vector<int> c(a.size() + b.size() + 1, 0);
    for(int i = 0; i < a.size(); i++)
    {
        for(int j = 0; j < b.size(); j++)
        {
            c[i+j] += a[i] * b[j];
        }
    }
    normalize(c);
    return c;
}
