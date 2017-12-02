//单词前缀树
// POJ Word Puzzles
#include <iostream>
#include <string.h>
#include <queue>
#include <vector>
#include <string>
using namespace std;

int L = 0, C = 0, W = 0;
//the number of lines, 0 < L <= 1000, 
//the number of columns, 0 < C <= 1000, 
//the number of words to be found, 0 < W <= 1000. 
char graph[1010][1010];
string word[1010];

int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };
//分别对应于字母A-H的行为

struct trienode
{
	trienode* child[26];
	trienode* prev;//前缀指针
	bool badnode;//是否是危险节点
	trienode()
	{
		memset(child, 0, sizeof(child));
		badnode = false;
		prev = NULL;
	}
};
trienode tree[100010];
//1000个字符串，每个。。鬼知道多长QAQ
int nodecount = 0;
void insert(trienode* root, string str)
//将str插入字典树
{
	for (int i = 0; i<str.size(); i++)
	{
		if (root->child[str[i] - 'A'] == NULL)
		{
			root->child[str[i] - 'A'] = tree + nodecount;
			nodecount++;
		}
		root = root->child[str[i] - 'A'];
	}
	root->badnode = true;//???
}
void build()
//在trie树上加前缀指针
{
	for (int i = 0; i<26; i++)
		tree[0].child[i] = tree + 1;
	tree[0].prev = NULL;
	tree[1].prev = tree;
	deque<trienode*> q;
	q.push_back(tree + 1);
	while (!q.empty())
	{
		trienode* root = q.front();
		q.pop_front();
		for (int i = 0; i<26; i++)
		{
			trienode* p = root->child[i];
			if (p)
			{
				trienode* prev = root->prev;
				while (prev)
				{
					if (prev->child[i])
					{
						p->prev = prev->child[i];
						if (p->prev->badnode) p->badnode = true;
						////自己的pPrev指向的节点是危险节点，则自己也是危险节点
						break;
					}
					else prev = prev->prev;
				}
				q.push_back(p);
			}
		}
	}
}
bool judge(int x, int y, char op, string str)
{
	//判断从(x,y)开始沿着op方向发展的字符串是否为str
	int len = str.length();
	int intop = op - 'A';
	int samenum = 0;
	for (int i = 0; i<len; i++)
	{
		if ((x + i*dx[intop]<0) || (x + i*dx[intop] >= L) || (y + i*dy[intop]<0) || (y + i*dy[intop] >= C)) break;
		if (graph[x + i*dx[intop]][y + i*dy[intop]] == str[i]) samenum++;
	}
	if (samenum == len) return true;
	return false;
}
int main()
{
	cin >> L >> C >> W;
	for (int i = 0; i<L; i++)
	{
		for (int j = 0; j<C; j++)
		{
			cin >> graph[i][j];
		}
	}
	for (int i = 0; i<W; i++)
	{
		cin >> word[i];
	}
	for (int i = 0; i<W; i++)
	{
		for (int x = 0; x<L; x++)
		{
			for (int y = 0; y<C; y++)
			{
				for (char op = 'A'; op <= 'H'; op++)
				{
					if (judge(x, y, op, word[i]))
					{
						cout << x << " " << y << " " << op << endl;
					}
				}
			}
		}
	}
	return 0;
}