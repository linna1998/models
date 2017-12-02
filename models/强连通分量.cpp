// ����ͼǿ��ͨ��֧��Tarjan�㷨
// POJ 1236
//��Ŀ����:N(2<N<100)��ѧУ֮���е��������, ÿ��ѧУ�õ�һ�������, ����ͨ�������������ܱߵ�ѧУ����, ����1����ʼ������Ҫ����ٸ�ѧУ�������, ʹ�����������е�ѧУ���ն��ܵõ����.2, ������Ҫ��Ӽ���������·(��), ʹ������һ��ѧУ���������, �������ɴδ���, ���������е�ѧУ���ն��ܵõ������
//�����㷨������Korasaju Algorithm�������ͼ���е�ǿ��ͨ����(��ȻComzyh���õ�Tarjan), Ȼ�����е�ǿ��ͨ��������һ����(����), ����ԭ��������ͼ��������һ��DAGͼ(�����޻�ͼ); ��2������ֱ��¼�����ɵ�DAGͼ�е�ÿ������(����ԭ���Ķ����ǿ��ͨ����������)�Ƿ��г��ߺ����, ������ÿ������, ���û�����, ��ans1++; ���û�г���, ans2++.�������Ϊans1��max(ans1, ans2).
#include <cstdio>
#include <cstring>
#include <cstdlib>
int tab[101][101];
int DFN[101], LOW[101], stack[200], instack[200];
int f[101];
int belong[101];
int top, RB, RT;//ջ��,���һ��ǿ��ͨ�������,���һ��ʱ��� 
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
	if (RB == 1)ans = 0;//�����һ������,��Ȼ���������� 
	printf("%d\n%d", ans1, ans);
	system("pause");
}
void Tarjan(int x)
{
	int i, t;//t= top / to ����;, 
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