// ������������
// ��������Ƶ�����
//150000kB 1228ms 3149 B 
//Ϊʲô��д�����ѽ���ڴ�ĵú͹��Ѳ��QAQ
//���������֭AC�˹���������
//���������������No Moves Needed��ʱҲҪ����м���ͬ�����֣���
//������������
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
	string list;//24λ����ʾ��һ��string��
	string op;//�������У���ʾ��string��
	int len;//�������г���
	node(string llist = "", string oop = "", int llen = 0)
	{
		list = llist;
		op = oop;
		len = llen;
	}
};
node* move(node* old_node, char c)
{
	//��in�е�������c�Ĺ�������ƶ�
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
	//������ǽⷵ��-1
	//����ǽⷵ���м��Ǹ�����ͬ����
	for (int i = 1; i < 8; i++)
		if (in->list[center[0]] != in->list[center[i]]) return -1;
	return in->list[center[0]];
}
int different(node* in)
//����������Ҫ�Ĳ�������
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
	//�ҵ��˽⣬�ͷ���ָ�����ָ��
	//û�ҵ��⣬�ͷ���NULL
	if (legal(start) != -1) return start;
	//��ʾ�ҵ��˽⣬�᷵��һ�����������һ�û��÷���ʲôQAQ
	if (deep <= 0) return NULL;
	//��ʾ���ѵ��ף�Ҫ���ˣ����ؿյ�ָ��
	if (different(start) > deep) return NULL;
	//�����Լ�֦

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
		//ǰ��������ͬ��ת����Ҫ��֦��
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
			//Ĭ���н�
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