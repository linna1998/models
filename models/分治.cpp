// 分治
// 求排列的逆序数
#include <iostream>
using namespace std;

int n = 0; //n <= 100000
int in[100010] = { 0 };
int temp[100010] = { 0 };
//temp[], used in Merge
long long int result = 0;
void Merge(int l, int mid, int r)
{
	int i = l, j = mid + 1;
	int k = l;
	//k表示填到的in里的序号
	for (int t = l; t <= r; t++)
		temp[t] = in[t];
	while (i <= mid && j <= r)
	{
		if (temp[i] < temp[j])
		{
			in[k] = temp[i];
			k++;
			i++;
		}
		else
		{
			in[k] = temp[j];
			k++;
			j++;
			result += (mid - i + 1);
		}
	}
	if (i == mid + 1)
	{
		while (k <= r)
		{
			in[k] = temp[j];
			k++;
			j++;
		}
	}
	else if (j == r + 1)
	{
		while (k <= r)
		{
			in[k] = temp[i];
			k++;
			i++;
			//result+=r-mid;
		}
	}//填入尾部
}
void MergeSort(int l, int r)
{
	int mid = l + (r - l) / 2;
	if (l == r) return;
	MergeSort(l, mid);
	MergeSort(mid + 1, r);
	Merge(l, mid, r);
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &in[i]);
	MergeSort(0, n - 1);
	cout << result << endl;
	return 0;
}