//并查集
//食物链
#include <iostream>
using namespace std;
int father[50010] = { 0 };
int gender[50010] = { 0 };
//gender[i]=0 i和father[i]是同类
//gender[i]=1 i吃father[i]
//gender[i]=2 father[i]吃i
int getfather(int a)
{
	if (father[a] == a) return a;
	int temp = getfather(father[a]);
	gender[a] = (gender[a] + gender[father[a]]) % 3;
	//枚举的复杂的合并2333
	//希望是对的呀~
	father[a] = temp;
	return father[a];
}
bool merge(int d, int x, int y)
{
	//得到一句d x y的话，进行猜测
	//如果与之前的话不矛盾就输出true
	//否则输出false
	int fx = getfather(x);
	int fy = getfather(y);
	if (fx == fy)
	{
		if (d == 1 && gender[x] == gender[y]) return true;
		if (d == 2 && (gender[x] - gender[y] + 3) % 3 == 1) return true;
		//枚举出来的23333
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