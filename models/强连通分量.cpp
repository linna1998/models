// 有向图强连通分支的Tarjan算法
// POJ 1236
//题目大意:N(2<N<100)各学校之间有单向的网络, 每个学校得到一套软件后, 可以通过单向网络向周边的学校传输, 问题1：初始至少需要向多少个学校发放软件, 使得网络内所有的学校最终都能得到软件.2, 至少需要添加几条传输线路(边), 使任意向一个学校发放软件后, 经过若干次传送, 网络内所有的学校最终都能得到软件。
//具体算法：先用Korasaju Algorithm求出有向图所有的强连通分量(当然Comzyh是用的Tarjan), 然后将所有的强连通分量缩成一个点(缩点), 这样原来的有向图就缩成了一个DAG图(有向无环图); 用2个数组分别记录新生成的DAG图中的每个顶点(包括原来的顶点和强连通分量的缩点)是否有出边和入边, 最后遍历每个顶点, 如果没有入边, 则ans1++; 如果没有出边, ans2++.最后所求即为ans1和max(ans1, ans2).
#include <cstdio>
#include <cstring>
#include <cstdlib>
int tab[101][101];
int DFN[101], LOW[101], stack[200], instack[200];
int f[101];
int belong[101];
int top, RB, RT;//栈顶,最后一个强连通分量编号,最后一个时间戳 
int ein[101], eout[101], ans, ans1, ans2;
int N;
//Function
void Tarjan(int x);
int getf(int x);
inline void add(int x, int y);//add x to y
int main()
{
	int i, j, to;
	scanf("%d", &N);
	memset(tab, 0, sizeof(tab));
	for (i = 1; i <= N; i++)
		while (scanf("%d", &to), to)
			tab[i][++tab[i][0]] = to;
	//
	memset(DFN, 0, sizeof(DFN));
	memset(instack, 0, sizeof(instack));
	top = RB = RT = 0;
	for (i = 1; i <= N; i++)
		f[i] = i;
	for (i = 1; i <= N; i++)
		if (!DFN[i])
			Tarjan(i);
	//for (i=1;i<=N;i++)printf("%4d belong to %4d\n",i,belong[i]);
	memset(ein, 0, sizeof(ein));
	memset(eout, 0, sizeof(eout));
	for (i = 1; i <= N; i++)
		if (tab[i][0])
		{
			eout[belong[i]] = 1;
			for (j = 1; j <= tab[i][0]; j++)
				if (getf(i) != getf(tab[i][j]))ein[belong[tab[i][j]]] = 1;
		}
	ans1 = ans2 = 0;
	for (i = 1; i <= RB; i++)
	{
		if (!ein[i])ans1++;
		if (!eout[i])ans2++;
	}
	ans = (ans1 > ans2) ? ans1 : ans2;
	if (RB == 1)ans = 0;//如果就一个分量,显然不用再连接 
	printf("%d\n%d", ans1, ans);
	system("pause");
}
void Tarjan(int x)
{
	int i, t;//t= top / to 多用途, 
	stack[++top] = x;
	DFN[x] = LOW[x] = ++RT;
	instack[x] = 1;
	for (i = 1; i <= tab[x][0]; i++)
	{
		t = tab[x][i];
		if (!DFN[t])
		{
			Tarjan(t);
			if (LOW[t] < LOW[x])
				LOW[x] = LOW[t];
		}
		else
			if (instack[t] && DFN[t] < LOW[x])
				LOW[x] = DFN[t];
	}
	if (LOW[x] == DFN[x])
	{
		RB++;
		do
		{
			t = stack[top--];
			add(t, x);
			belong[t] = RB;
			instack[t] = 0;
		} while (t != x);
	}
}
int getf(int x)
{
	if (f[x] == x)return x;
	else return f[x] = getf(f[x]);
}
inline void add(int x, int y)//add x to y
{
	int fx = getf(x), fy = getf(y);
	if (fx == fy)return;
	f[fx] = fy;
}