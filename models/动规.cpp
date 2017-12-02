// ״̬ѹ������
//������֮ΰ��·
#include <iostream>
#include <algorithm>
using namespace std;
#define INF 0x3fffffff
int N = 0;
int gettime[17][17] = { 0 };
int visittime[(1 << 16) + 1][17] = { 0 };
//visittime[i][j]��ʾ�߹�i�б�1�ĵ�����ͣ��j�������Сʱ��

int visit(int state, int island)
//state��ʾҪ�ߵ���״̬
//island��ʾҪ�ߵ��ĵ���
{
	if (island == 0 && state != 1) return visittime[state][island];
	//����0����㣬��ʼ��״ֻ̬����(1,0)
	//������������һ������֦��������
	//��1001ms������18ms����666666������
	if (visittime[state][island] != INF) return visittime[state][island];
	for (int i = 0; i<N; i++)
	{
		if (((state&(1 << i)) == (1 << i)) && (i != island))
			//��ʾ״̬state���Դ�i���������ܴ��յ�����2333
		{
			if (gettime[i][island]>visittime[state][island]) continue;//��֦
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