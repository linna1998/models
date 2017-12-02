// ������
// Poj 1273 Drainage Ditches
// ���������������Ŀ������������������ÿ���ߵ��������Լ�Դ�㣬��㣬���������
// Sample Input 5 4  // 5��4��
// 1 2 40 1 4 20 2 4 20 2 3 30 3 4 10
// Sample Output 50

// ��Ľⷨ
#include <iostream>
#include <queue>
using namespace std;
int G[300][300];
int Prev[300]; //·����ÿ���ڵ��ǰ���ڵ�
bool Visited[300];
int n, m; //m�Ƕ�����Ŀ�������Ŵ�1��ʼ 1��Դ��m�ǻ�, n�Ǳ���
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
	//��bfsѰ��һ��Դ����Ŀ���·��
	while (!q.empty())
	{
		v = q.front();
		q.pop_front();
		for (i = 1; i <= m; i++)
		{
			if (G[v][i] > 0 && Visited[i] == 0)
			{
				//��������Ȼ�������ıߣ��ſ�����
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
	//Ѱ��Դ����·����������С�ıߣ����������Ǵ˴����ӵ�������
	while (Prev[v])
	{
		nMinFlow = min(nMinFlow, G[Prev[v]][v]);
		v = Prev[v];
	}
	//�ش�·����ӷ���ߣ�ͬʱ�޸�·����ÿ���ߵ�����
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
		//m�Ƕ�����Ŀ�������Ŵ�1��ʼ
		int i, j, k;
		int s, e, c;
		memset(G, 0, sizeof(G));
		for (i = 0; i < n; i++)
		{
			cin >> s >> e >> c;
			G[s][e] += c; //����֮������ж�����
		}
		unsigned int MaxFlow = 0;
		unsigned int aug;
		while (aug = Augment())
			MaxFlow += aug;
		cout << MaxFlow << endl;
	}
	return 0;
}

// Dinic�㷨�Ľⷨ
#include <iostream>
#include <queue> 
#include <vector> 
#include <algorithm>
#include <deque> 
using namespace std;
#define INFINITE 999999999 //Poj 1273 Drainage Ditches �� Dinic�㷨
int G[300][300];
bool Visited[300];
int Layer[300];
int n, m; //1��Դ�㣬m�ǻ��
bool CountLayer()
{
	int layer = 0;
	deque<int>q;
	memset(Layer, 0xff, sizeof(Layer)); //����ʼ����-1
	Layer[1] = 0; q.push_back(1);
	while (!q.empty())
	{
		int v = q.front();
		q.pop_front();
		for (int j = 1; j <= m; j++)
		{
			if (G[v][j] > 0 && Layer[j] == -1)
			{
				//Layer[j] == -1 ˵��j��û�з��ʹ�
				Layer[j] = Layer[v] + 1;
				if (j == m) //�ֲ㵽��㼴��
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
	deque<int> q; //DFS�õ�ջ 
	while (CountLayer())
	{ //ֻҪ�ֲܷ� 
		q.push_back(1); //Դ����ջ
		memset(Visited, 0, sizeof(Visited));
		Visited[1] = 1;
		while (!q.empty())
		{
			int nd = q.back();
			if (nd == m)
			{
				// nd�ǻ�� 
				//��ջ����������С��
				int nMinC = INFINITE;
				int nMinC_vs; //������С�ߵ����
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
				//���㣬��ͼ
				nMaxFlow += nMinC;
				for (i = 1; i < q.size(); i++)
				{
					int vs = q[i - 1];
					int ve = q[i];
					G[vs][ve] -= nMinC; //�޸ı�����
					G[ve][vs] += nMinC; //��ӷ����
				}
				//��ջ�� nMinC_vs��Ϊջ�����Ա����dfs
				while (!q.empty() && q.back() != nMinC_vs)
				{
					Visited[q.back()] = 0; //û�����Ӧ��Ҳ��
					q.pop_back();
				}
			}
			else { //nd���ǻ��
				for (i = 1; i <= m; i++)
				{
					if (G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 &&
						!Visited[i])
					{
						//ֻ����һ���û���߹��Ľڵ���
						Visited[i] = 1;
						q.push_back(i);
						break;
					}
				}
				if (i > m) //�Ҳ�����һ����
					q.pop_back(); //����
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
			G[s][e] += c; //����֮������ж�����
		}
		cout << Dinic() << endl;
	}
	return 0;
}