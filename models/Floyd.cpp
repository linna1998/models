// Floyd
// ��ÿһ�Զ���֮������·��, O(n^3)
// α����Ƭ��
for (int i = 1; i <= vtxnum; ++i)
{
	for (int j = 1; j <= vtxnum; ++j)
	{
		dist[i][j] = cost[i][j]; // cost�Ǳ�Ȩֵ, dist���������̾���
		if (dist[i][j] < INFINITE) //i��j�б�
			path[i, j] = [i] + [j]; //path��·��
	}
}
for (k = 1; k <= vtxnum; ++k)
{//ÿ�����м���Ų�����k��i��j���·
	for (int i = 1; i <= vtxnum; ++i)
	{
		for (int j = 1; j <= vtxnum; ++j)
		{
			if (dist[i][k] + dist[k][j] < dist[i][j])
			{
				dist[i][j] = dist[i][k] + dist[k][j];
				path[i, j] = path[i, k] + path[k, j];
			}
		}
	}
}