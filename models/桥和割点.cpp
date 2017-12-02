// �ź͸��
//���ر���ͨ����ͼ������ŵĳ��� 
#include <iostream> 
#include <vector> 
#include <algorithm>
using namespace std;
#define MyMax 200
typedef vector<int> Edge;
vector<Edge> G(MyMax);
bool Visited[MyMax];
int dfn[MyMax];
int low[MyMax];
int Father[MyMax]; //DFS����ÿ����ĸ��ڵ�
bool bIsCutVetext[MyMax]; //ÿ�����ǲ��Ǹ��
int nTime; //Dfsʱ��� 
int n, m; //n�ǵ�����m�Ǳ���
void Tarjan(int u, int father) //father ��u�ĸ��ڵ�
{
	Father[u] = father;
	int i, j, k;
	low[u] = dfn[u] = nTime++;
	for (i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i];
		if (!dfn[v])
		{
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
		}
		else if (father != v) //�������ڵ�Ļر߲����ǣ������󲻳��� 
			low[u] = min(low[u], dfn[v]);
	}
}
void Count() { //��������� 
	int nRootSons = 0;
	int i;
	Tarjan(1, 0);
	for (i = 2; i <= n; i++)
	{
		int v = Father[i];
		if (v == 1) nRootSons++; //DFS���и��ڵ��м������� 
		else
		{
			if (dfn[v] <= low[i]) bIsCutVetext[v] = true;
		}
	}
	if (nRootSons > 1) bIsCutVetext[1] = true;
	for (i = 1; i <= n; i++)
		if (bIsCutVetext[i]) cout << i << endl;
	for (i = 1; i <= n; i++)
	{
		int v = Father[i];
		if (v > 0 && dfn[v] < low[i]) cout << v << "," << i << endl;
	}
}
int main()
{
	int u, v;
	int i;
	nTime = 1;
	cin >> n >> m; //n�ǵ�����m�Ǳ���
	for (i = 1; i <= m; i++) {
		cin >> u >> v; //���Ŵ�1��ʼ
		G[v].push_back(u);
		G[u].push_back(v);
	}
	memset(dfn, 0, sizeof(dfn));
	memset(Father, 0, sizeof(Father));
	memset(bIsCutVetext, 0, sizeof(bIsCutVetext));
	Count();
	return 0;
}