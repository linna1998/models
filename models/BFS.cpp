// 广搜
// 八数码问题
#include <iostream>
#include <bitset> 
#include <cstring> 
#include <cstdio>
#include <cstdlib> 
#include <set>
using namespace std;
int goalStatus = 123456780; //目标状态
const int MAXS = 400000;
char result[MAXS]; //要输出的移动方案 
struct Node
{
	int status; //状态 
	int father; //父节点指针，即myQueue的下标 
	char move; //父节点到本节点的移动方式 u/d/r/l 
	Node(int s, int f, char m) :status(s), father(f), move(m) { }
	Node() { }
};
Node myQueue[MAXS]; //状态队列，状态总数362880 
int qHead = 0; //队头指针 
int qTail = 1; //队尾指针 
char moves[] = "udrl"; //四种移动
int NewStatus(int status, char move)
{
	//求从status经过 move 移动后得到的新状态。若移动不可行则返回-1 
	char tmp[20];
	int zeroPos; //字符'0'的位置
	sprintf(tmp, "%09d", status); //需要保留前导0 
	for (int i = 0; i < 9; ++i)
		if (tmp[i] == '0')
		{
			zeroPos = i;
			break;
		}
	//返回空格的位置 
	switch (move)
	{
	case 'u':
		if (zeroPos - 3 < 0) return -1; //空格在第一行 
		else
		{
			tmp[zeroPos] = tmp[zeroPos - 3];
			tmp[zeroPos - 3] = '0';
		}
		break;
	case 'd':
		if (zeroPos + 3 > 8) return -1; //空格在第三行
		else
		{
			tmp[zeroPos] = tmp[zeroPos + 3];
			tmp[zeroPos + 3] = '0';
		}
		break;
	case 'l':
		if (zeroPos % 3 == 0) return -1; //空格在第一列 
		else
		{
			tmp[zeroPos] = tmp[zeroPos - 1];
			tmp[zeroPos - 1] = '0';
		}
		break;
	case 'r':
		if (zeroPos % 3 == 2)
			return -1; //空格在第三列
		else {
			tmp[zeroPos] = tmp[zeroPos + 1];
			tmp[zeroPos + 1] = '0';
		}
		break;
	}
	return atoi(tmp);
}
bool Bfs(int status) { //寻找从初始状态status到目标的路径，找不到则返回false
	int newStatus;
	set<int> expanded;
	myQueue[qHead] = Node(status, -1, 0);
	expanded.insert(status);
	while (qHead != qTail)
	{
		//队列不为空 
		status = myQueue[qHead].status;
		if (status == goalStatus) //找到目标状态
			return true;
		for (int i = 0; i < 4; i++)
		{ //尝试4种移动 
			newStatus = NewStatus(status, moves[i]);
			if (newStatus == -1) continue; //不可移，试下一种 
			if (expanded.find(newStatus) != expanded.end()) continue; //已扩展过，试下一种 
			expanded.insert(newStatus);
			myQueue[qTail++] = Node(newStatus, qHead, moves[i]); //新节点入队列 
		}
		qHead++;
	}
	return false;
}
int main() {
	char line1[50]; char line2[20];
	while (cin.getline(line1, 48)) {
		int i, j;
		//将输入的原始字符串变为数字字符串
		for (i = 0, j = 0; line1[i]; i++) {
			if (line1[i] != ' ') {
				if (line1[i] == 'x')
					line2[j++] = '0';
				else
					line2[j++] = line1[i];
			}
		}
		line2[j] = 0; //字符串形式的初始状态
		if (Bfs(atoi(line2)))
		{
			int moves = 0;
			int pos = qHead;
			do
			{
				//通过father找到成功的状态序列，输出相应步骤 
				result[moves++] = myQueue[pos].move;
				pos = myQueue[pos].father;
			} while (pos); //pos = 0 说明已经回退到初始状态了
			for (int i = moves - 1; i >= 0; i--)
				cout << result[i];
		}
		else cout << "unsolvable" << endl;
	}
}