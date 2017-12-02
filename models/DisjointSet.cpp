//���鼯
//ʳ����
#include <iostream>
using namespace std;
int father[50010] = { 0 };
int gender[50010] = { 0 };
//gender[i]=0 i��father[i]��ͬ��
//gender[i]=1 i��father[i]
//gender[i]=2 father[i]��i
int getfather(int a)
{
	if (father[a] == a) return a;
	int temp = getfather(father[a]);
	gender[a] = (gender[a] + gender[father[a]]) % 3;
	//ö�ٵĸ��ӵĺϲ�2333
	//ϣ���ǶԵ�ѽ~
	father[a] = temp;
	return father[a];
}
bool merge(int d, int x, int y)
{
	//�õ�һ��d x y�Ļ������в²�
	//�����֮ǰ�Ļ���ì�ܾ����true
	//�������false
	int fx = getfather(x);
	int fy = getfather(y);
	if (fx == fy)
	{
		if (d == 1 && gender[x] == gender[y]) return true;
		if (d == 2 && (gender[x] - gender[y] + 3) % 3 == 1) return true;
		//ö�ٳ�����23333
		return false;
	}
	father[fx] = fy;
	gender[fx] = (-gender[x] + gender[y] + d + 2) % 3;
	return true;
}
int main()
{
	int N = 0, K = 0;
	int d = 0, x = 0, y = 0;
	long long int result = 0;
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
	{
		father[i] = i;
		gender[i] = 0;
	}
	for (int i = 0; i < K; i++)
	{
		cin >> d >> x >> y;
		if (x > N || y > N)
		{
			result++;
			continue;
		}
		if (d == 2 && x == y)
		{
			result++;
			continue;
		}
		if (!merge(d, x, y))
		{
			result++;
			continue;
		}
	}
	cout << result << endl;
	return 0;
}