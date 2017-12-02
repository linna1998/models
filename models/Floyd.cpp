// Floyd
// 求每一对顶点之间的最短路径, O(n^3)
// 伪代码片段
for (int i = 1; i <= vtxnum; ++i)
{
	for (int j = 1; j <= vtxnum; ++j)
	{
		dist[i][j] = cost[i][j]; // cost是边权值, dist是两点间最短距离
		if (dist[i][j] < INFINITE) //i到j有边
			path[i, j] = [i] + [j]; //path是路径
	}
}
for (k = 1; k <= vtxnum; ++k)
{//每次求中间点标号不超过k的i到j最短路
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