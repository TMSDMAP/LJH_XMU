/*
9.2 德才论
分数 21
作者 陈丽
单位 浙江大学
宋代史学家司马光在《资治通鉴》中有一段著名的“德才论”：“是故才德全尽谓之圣人，才德兼亡谓之愚人，德胜才谓之君子，才胜德谓之小人。凡取人之术，苟不得圣人，君子而与之，与其得小人，不若得愚人。”

现给出一批考生的德才分数，请根据司马光的理论给出录取排名。

输入格式：
输入第一行给出 3 个正整数，分别为：n（≤10
5
 ），即考生总数；l（≥60），为录取最低分数线，即德分和才分均不低于 l 的考生才有资格被考虑录取；h（<100），为优先录取线——德分和才分均不低于此线的被定义为“才德全尽”，此类考生按德才总分从高到低排序；才分不到但德分到优先录取线的一类考生属于“德胜才”，也按总分排序，但排在第一类考生之后；德才分均低于 h，但是德分不低于才分的考生属于“才德兼亡”但尚有“德胜才”者，按总分排序，但排在第二类考生之后；其他达到最低线 l 的考生也按总分排序，但排在第三类考生之后。

随后 n 行，每行给出一位考生的信息，包括：准考证号、德分、才分，其中准考证号为 8 位整数，德才分为区间 [0, 100] 内的整数。数字间以空格分隔。

输出格式：
输出第一行首先给出达到最低分数线的考生人数 m，随后 m 行，每行按照输入格式输出一位考生的信息，考生按输入中说明的规则从高到低排序。当某类考生中有多人总分相同时，按其德分降序排列；若德分也并列，则按准考证号的升序输出。*/
//总而言之
//德分d 才分c
//1.d>=h&&c>=h 按d+c排
//2.d>=h&&c<h 按d+c排
//3.d<h&&c<h&&d>=c 按d+c排
//4.d<h&&c<h&&d<c 按d+c排
//看似很复杂,实则就是变一下比较规则(写一个compare函数)然后快排
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
struct DCL {
	char s[10];
	int d;
	int c;
	int flag;
};         //设一个结构体数组
int n, l, h;
DCL a[100000];
DCL b[100000];
void judge(DCL& S)     //判断属于哪一类
{
	if (S.d >= h && S.c >= h) S.flag = 1;
	else if (S.d >= h && S.c < h) S.flag = 2;
	else if (S.d < h && S.c < h && S.d >= S.c) S.flag = 3;
	else S.flag = 4;
}
bool compare(DCL&s1, DCL&s2)       //判断s1比s2大,大就返回true
{
	if (s1.flag < s2.flag) return true;
	else if (s1.flag > s2.flag) return false;
	else
	{
		if (s1.d + s1.c > s2.d + s2.c) return true;
		else if (s1.d + s1.c < s2.d + s2.c) return false;
		else
		{
			if (s1.d > s2.d) return true;
			else if (s1.d < s2.d) return false;
			else
			{
				if (strcmp(s1.s, s2.s) < 0) return true;
				else return false;
			}
		}
	}
}
int partition(DCL a[], int low, int high)
{
	DCL key = a[low];
	while (low < high)
	{
		while (low < high && compare(a[high], key)) high--;   //变一下
		a[low] = a[high];
		while (low < high && compare(key, a[low])) low++;
		a[high] = a[low];
	}
	a[low] = key;
	return low;
}
void qsort(DCL a[], int low, int high)
{
	if (low < high)
	{
		int k = partition(a, low, high);
		qsort(a, low, k - 1);
		qsort(a, k + 1, high);
	}
}         //套模板
int main()
{
	int m = 0;
	int count = 0;
	cin >> n >> l >> h;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i].s >> a[i].d >> a[i].c;
		if (a[i].d >= l && a[i].c >= l)
		{
			count++;
			judge(a[i]);
		}
	}
	//cout << a[0].flag << endl;
	for (int i = 0; i < n; i++)
	{
		if (a[i].flag != 0)
			b[m++] = a[i];
	}
	qsort(b, 0, m-1);
	cout << count << endl;
	//cout << m << endl;
	for (int i = m-1; i>=0; i--)
	{
		cout << b[i].s << " " << b[i].d << " " << b[i].c << endl;
	}
}