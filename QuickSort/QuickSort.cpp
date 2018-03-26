#include <cstdio>
using namespace std;

int arr[5000000];

void swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

inline void print()
{
	for(int k : arr)
	{
		if(k == 0) break;
		printf("%d ", k);
	}
	puts("");
}

int Partition(int arr[], int left, int right)
{
	int last = arr[right];
	int index = left;
	// Lumoto-Partition algorithm: last보다 작은 것을 배열의 앞으로 다 보낸다.
	// 항상 index <= i 이다.
	for(int i = left; i < right; i++)
	{
		if(arr[i] <= last)
		{
			swap(arr[i], arr[index]);
			index++;
			printf("swap %d and %d: ", i, index-1); print();
		}
	}
	swap(arr[index], arr[right]);
	printf("swap %d and %d: ", index, right); print();
	printf("return pivot %d\n", index);
	return index;
}

void QuickSort(int arr[], int left, int right)
{
	printf("QuickSort(%d, %d)\n", left, right);
	if(left >= right) return;
	int pivot = Partition(arr, left, right);
	QuickSort(arr, left, pivot-1);
	QuickSort(arr, pivot+1, right);
}

int main()
{
	freopen("in.txt", "r", stdin);
	int n, k;
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
	QuickSort(arr, 0, n-1);
	for(int i = 0; i < n; i++) printf("%d ", arr[i]);
}
