// 迭代加深搜索
// 有深度限制的深搜
//150000kB 1228ms 3149 B 
//为什么我写的深搜结果内存耗得和广搜差不多QAQ
//反正最后蜜汁AC了哈哈哈啊哈
//哈哈哈就算输出“No Moves Needed”时也要输出中间相同的数字！！
//哈哈哈哈啊哈
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int changelist[8][7] =
{ 0,2,6,11,15,20,22,
1,3,8,12,17,21,23,
10,9,8,7,6,5,4,
19,18,17,16,15,14,13,
23,21,17,12,8,3,1,
22,20,15,11,6,2,0,
13,14,15,16,17,18,19,
4,5,6,7,8,9,10 };
int center[8] = { 6,7,8,12,17,16,15,11 };

struct node
{
	string list;//24位数表示在一个string中
	string op;//操作序列，表示在string中
	int len;//操作序列长度
	node(string llist = "", string oop = "", int llen = 0)
	{
		list = llist;
		op = oop;
		len = llen;
	}
};
node* move(node* old_node, char c)
{
	//对in中的数按照c的规则进行移动
	int temp;
	int op = c - 'A';
	node* new_node = new node(old_node->list, old_node->op, old_node->len);
	new_node->len++;
	new_node->op += c;
	temp = new_node->list[changelist[op][0]];
	for (int j = 0; j < 6; j++)
		new_node->list[changelist[op][j]] = new_node->list[changelist[op][j + 1]];
	new_node->list[changelist[op][6]] = temp;
	return new_node;
}
int legal(node * in)
{
	//如果不是解返回-1
	//如果是解返回中间那个都相同的数
	for (int i = 1; i < 8; i++)
		if (in->list[center[0]] != in->list[center[i]]) return -1;
	return in->list[center[0]];
}
int different(node* in)
//返回最少需要的操作次数
{
	//int num[3]={0};
	//for (int i=0;i<8;i++)
	//	num[in->list[center[i]]-'0']++;
	//int temp=max(num[0],num[1]);
	//temp=max(temp,num[2]);
	//return 8-temp;
	//	//Stack around the variable 'num' was corrupted.
	////QAQ

	int num1 = 0, num2 = 0, num3 = 0;
	int temp = 0;
	for (int i = 0; i < 8; i++)
	{
		if (in->list[center[i]] == '1') num1++;
		else if (in->list[center[i]] == '2') num2++;
		else if (in->list[center[i]] == '3') num3++;
	}
	temp = max(num1, num2);
	temp = max(temp, num3);
	return 8 - temp;
}
node* search(node* start, int deep)
{
	if (start == NULL) return NULL;
	//找到了解，就返回指到解的指针
	//没找到解，就返回NULL
	if (legal(start) != -1) return start;
	//表示找到了解，会返回一个东西，但我还没想好返回什么QAQ
	if (deep <= 0) return NULL;
	//表示深搜到底，要回退，返回空的指针
	if (different(start) > deep) return NULL;
	//可行性剪枝

	char pre = '\0';
	if (start->len > 0) pre = start->op[start->len - 1];
	node* new_node = new node;
	node * temp_node = new node;
	for (int i = 0; i < 8; i++)
	{
		if (pre == 'A' && i == 5) continue;
		if (pre == 'B' && i == 4) continue;
		if (pre == 'C' && i == 7) continue;
		if (pre == 'D' && i == 6) continue;
		if (pre == 'E' && i == 1) continue;
		if (pre == 'F' && i == 0) continue;
		if (pre == 'G' && i == 3) continue;
		if (pre == 'H' && i == 2) continue;
		//前后两次相同旋转是需要剪枝的
		new_node = move(start, (char)('A' + i));
		temp_node = search(new_node, deep - 1);
		if (temp_node != NULL) return temp_node;
	}
	return NULL;
}
int main()
{
	char s;
	int d = 0;
	while (true)
	{
		node* start = new node;
		node* temp = new node;
		cin >> s;
		if (s == '0') break;
		start->list.push_back(s);
		for (int i = 1; i < 24; i++)
		{
			cin >> s;
			start->list.push_back(s);
		}
		d = 0;
		while (true)
			//默认有解
		{
			temp = search(start, d);
			if (temp != NULL) break;
			d++;
		}
		if (temp->len == 0) cout << "No moves needed" << endl;
		else 	cout << temp->op << endl;
		cout << temp->list[6] << endl;
	}
	return 0;
}