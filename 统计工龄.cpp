/*
9.4 统计工龄
分数 20
作者 陈越
单位 浙江大学
给定公司 n 名员工的工龄，要求按工龄增序输出每个工龄段有多少员工。

输入格式:
输入首先给出正整数 n（≤10
5
 ），即员工总人数；随后给出 n 个整数，即每个员工的工龄，范围在 [0, 50]。

输出格式:
按工龄的递增顺序输出每个工龄的员工个数，格式为：“工龄:人数”。每项占一行。如果人数为 0 则不输出该项。
*/
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int a[100000];
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a + n);   //用自带的sort函数，懒得自己写了
	cout << a[0] << ":";
	int count = 1;
	for (int i = 1; i < n; i++)
	{
		if (a[i] == a[i - 1]) count++;   //count计数
		else
		{
			cout << count << endl;
			cout << a[i] << ":";
			count = 1;
		}
	}
	cout << count;  //最后没有换行，哈哈哈！！！？
	return 0;
}