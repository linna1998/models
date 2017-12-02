// 状态压缩动规
//海贼王之伟大航路
#include <iostream>
#include <algorithm>
using namespace std;
#define INF 0x3fffffff
int N = 0;
int gettime[17][17] = { 0 };
int visittime[(1 << 16) + 1][17] = { 0 };
//visittime[i][j]表示走过i中标1的岛屿且停在j岛屿的最小时间

int visit(int state, int island)
//state表示要走到的状态
//island表示要走到的岛屿
{
	if (island == 0 && state != 1) return visittime[state][island];
	//由于0是起点，开始的状态只能是(1,0)
	//啊啊啊啊啊这一条疯狂剪枝啊啊啊啊
	//从1001ms剪到了18ms！！666666！！！
	if (visittime[state][island] != INF) return visittime[state][island];
	for (int i = 0; i<N; i++)
	{
		if (((state&(1 << i)) == (1 << i)) && (i != island))
			//表示状态state可以从i走来，不能从终点走来2333
		{
			if (gettime[i][island]>visittime[state][island]) continue;//剪枝
			visittime[state][island] = min(visittime[state][island], 
				visit(state - (1 << island), i) + gettime[i][island]);
		}
	}
	return visittime[state][island];
}
int main()
{
	scanf("%d", &N);
	for (int i = 0; i<N; i++)
		for (int j = 0; j<N; j++)
			scanf("%d", &gettime[i][j]);
	for (int i = 0; i <= (1 << N); i++)
		for (int j = 0; j<17; j++)
			visittime[i][j] = INF;
	visittime[1][0] = 0;
	printf("%d\n", visit((1 << N) - 1, N - 1));
	return 0;
}