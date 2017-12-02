// 计算几何
//POJ 2007 Scrambled Polygon 给定凸多边形顶点，要求按反时针序输出。
//叉积排序 
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
struct Vector
{
	double x, y;
	Vector(int xx, int yy) :x(xx), y(yy) { }
	Vector() { }
	double operator ^ (const Vector & v) const
	{
		return x*v.y - v.x*y;
	}
};
#define Point Vector
Vector operator - (const Point & p1, const Point & p2)
{ //从A点指向B点的矢量AB可用B-A来表示
	return Vector(p1.x - p2.x, p1.y - p2.y);
	//矢量从 p2指向p1
}
bool operator < (const Point & p1, const Point & p2)
{
	//如果p1^p2 〉0，说明p1经逆时针旋转<180度可以到p2，则 p1 < p2
	if ((Vector(p2 - Point(0, 0)) ^ Vector(p1 - Point(0, 0))) > 0)
		return true;
	return false;
}
Point ps[60];
int main()
{
	int x, y;
	int n = 0;
	while (cin >> ps[n].x >> ps[n].y)
		++n;
	sort(ps + 1, ps + n);
	cout << "(0,0)" << endl;
	for (int i = n - 1; i > 0; --i)
		cout << "(" << ps[i].x << "," << ps[i].y << ")" << endl;
	return 0;
}

//极角序扫描法求凸包
//POJ1113 Wall 
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>
using namespace std;
#define EPS 1e-6
int Sign(double x)
{ // 判断 x 是大于0,等于0还是小于0
	return fabs(x) < EPS ? 0 : x > 0 ? 1 : -1;
}
struct Point
{
	double x, y;
	Point(double xx = 0, double yy = 0) :x(xx), y(yy) { }
	Point operator-(const Point & p) const
	{
		return Point(x - p.x, y - p.y);
	}
	bool operator <(const Point & p) const
	{
		if (y < p.y) return true;
		else if (y > p.y) return false;
		else return x < p.x;
	}
};
typedef Point Vector;
double Cross(const Vector & v1, const Vector & v2)
{//叉积
	return v1.x * v2.y - v2.x * v1.y;
}
double Distance(const Point & p1, const Point & p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
struct Comp
{ //用来定义极角排序规则的函数对象
	Point p0; //以p0为原点进行极角排序,极角相同的，离p0近算小
	Comp(const Point & p) :p0(p.x, p.y) { }
	bool operator ()(const Point & p1, const Point & p2) const
	{
		int s = Sign(Cross(p1 - p0, p2 - p0));
		if (s > 0)
			return true;
		else if (s < 0)
			return false;
		else
		{
			if (Distance(p0, p1) < Distance(p0, p2))
				return true;
			else
				return false;
		}
	}
};
int Graham(vector<Point> & points, vector<Point> & stack)
{
	//points是点集合
	if (points.size() < 3)
		return 0; //返回凸包顶点数
	stack.clear();
	//先按坐标排序，最左下的放到points[0]
	sort(points.begin(), points.end());
	//以points[0] 为原点进行极角排序
	sort(points.begin() + 1, points.end(), Comp(points[0]));
	stack.push_back(points[0]);
	stack.push_back(points[1]);
	stack.push_back(points[2]);
	for (int i = 3; i < points.size(); ++i)
	{
		while (true)
		{
			Point p2 = *(stack.end() - 1);
			Point p1 = *(stack.end() - 2);
			if (Sign(Cross(p2 - p1, points[i] - p2) <= 0))
				//p2->points[i]没有向左转，就让p2出栈
				stack.pop_back();
			else
				break;
		}
		stack.push_back(points[i]);
	}
	return stack.size();
}