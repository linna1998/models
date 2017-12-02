// 网络流
// Poj 1273 Drainage Ditches
// 赤裸裸的网络流题目。给定点数，边数，每条边的容量，以及源点，汇点，求最大流。
// Sample Input 5 4  // 5点4边
// 1 2 40 1 4 20 2 4 20 2 3 30 3 4 10
// Sample Output 50

// 裸的解法
#include <iostream>
#include <queue>
using namespace std;
int G[300][300];
int Prev[300]; //路径上每个节点的前驱节点
bool Visited[300];
int n, m; //m是顶点数目，顶点编号从1开始 1是源，m是汇, n是边数
unsigned Augment()
{
	int v;
	int i;
	deque<int> q;
	memset(Prev, 0, sizeof(Prev));
	memset(Visited, 0, sizeof(Visited));
	Prev[1] = 0;
	Visited[1] = 1;
	q.push_back(1);
	bool bFindPath = false;
	//用bfs寻找一条源到汇的可行路径
	while (!q.empty())
	{
		v = q.front();
		q.pop_front();
		for (i = 1; i <= m; i++)
		{
			if (G[v][i] > 0 && Visited[i] == 0)
			{
				//必须是依然有容量的边，才可以走
				Prev[i] = v;
				Visited[i] = 1;
				if (i == m) {
					bFindPath = true;
					q.clear();
					break;
				}
				else
					q.push_back(i);
			}
		}
	}
	if (!bFindPath)
		return 0;
	int nMinFlow = 999999999;
	v = m;
	//寻找源到汇路径上容量最小的边，其容量就是此次增加的总流量
	while (Prev[v])
	{
		nMinFlow = min(nMinFlow, G[Prev[v]][v]);
		v = Prev[v];
	}
	//沿此路径添加反向边，同时修改路径上每条边的容量
	v = m;
	while (Prev[v])
	{
		G[Prev[v]][v] -= nMinFlow;
		G[v][Prev[v]] += nMinFlow;
		v = Prev[v];
	}
	return nMinFlow;
}
int main()
{
	while (cin >> n >> m)
	{
		//m是顶点数目，顶点编号从1开始
		int i, j, k;
		int s, e, c;
		memset(G, 0, sizeof(G));
		for (i = 0; i < n; i++)
		{
			cin >> s >> e >> c;
			G[s][e] += c; //两点之间可能有多条边
		}
		unsigned int MaxFlow = 0;
		unsigned int aug;
		while (aug = Augment())
			MaxFlow += aug;
		cout << MaxFlow << endl;
	}
	return 0;
}

// Dinic算法的解法
#include <iostream>
#include <queue> 
#include <vector> 
#include <algorithm>
#include <deque> 
using namespace std;
#define INFINITE 999999999 //Poj 1273 Drainage Ditches 的 Dinic算法
int G[300][300];
bool Visited[300];
int Layer[300];
int n, m; //1是源点，m是汇点
bool CountLayer()
{
	int layer = 0;
	deque<int>q;
	memset(Layer, 0xff, sizeof(Layer)); //都初始化成-1
	Layer[1] = 0; q.push_back(1);
	while (!q.empty())
	{
		int v = q.front();
		q.pop_front();
		for (int j = 1; j <= m; j++)
		{
			if (G[v][j] > 0 && Layer[j] == -1)
			{
				//Layer[j] == -1 说明j还没有访问过
				Layer[j] = Layer[v] + 1;
				if (j == m) //分层到汇点即可
					return true;
				else
					q.push_back(j);
			}
		}
	}
	return false;
}
int Dinic()
{
	int i;
	int s;
	int nMaxFlow = 0;
	deque<int> q; //DFS用的栈 
	while (CountLayer())
	{ //只要能分层 
		q.push_back(1); //源点入栈
		memset(Visited, 0, sizeof(Visited));
		Visited[1] = 1;
		while (!q.empty())
		{
			int nd = q.back();
			if (nd == m)
			{
				// nd是汇点 
				//在栈中找容量最小边
				int nMinC = INFINITE;
				int nMinC_vs; //容量最小边的起点
				for (i = 1; i < q.size(); i++)
				{
					int vs = q[i - 1];
					int ve = q[i];
					if (G[vs][ve] > 0)
					{
						if (nMinC > G[vs][ve])
						{
							nMinC = G[vs][ve];
							nMinC_vs = vs;
						}
					}
				}
				//增广，改图
				nMaxFlow += nMinC;
				for (i = 1; i < q.size(); i++)
				{
					int vs = q[i - 1];
					int ve = q[i];
					G[vs][ve] -= nMinC; //修改边容量
					G[ve][vs] += nMinC; //添加反向边
				}
				//退栈到 nMinC_vs成为栈顶，以便继续dfs
				while (!q.empty() && q.back() != nMinC_vs)
				{
					Visited[q.back()] = 0; //没有这个应该也对
					q.pop_back();
				}
			}
			else { //nd不是汇点
				for (i = 1; i <= m; i++)
				{
					if (G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 &&
						!Visited[i])
					{
						//只往下一层的没有走过的节点走
						Visited[i] = 1;
						q.push_back(i);
						break;
					}
				}
				if (i > m) //找不到下一个点
					q.pop_back(); //回溯
			}
		}
	}
	return nMaxFlow;
}
int main()
{
	while (cin >> n >> m)
	{
		int i, j, k;
		int s, e, c;
		memset(G, 0, sizeof(G));
		for (i = 0; i < n; i++)
		{
			cin >> s >> e >> c;
			G[s][e] += c; //两点之间可能有多条边
		}
		cout << Dinic() << endl;
	}
	return 0;
}