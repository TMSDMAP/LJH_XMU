/*
9.1 排序
分数 12
作者 陈越
单位 浙江大学
给定 n 个（长整型范围内的）整数，要求输出从小到大排序后的结果。

本题旨在测试各种不同的排序算法在各种数据情况下的表现。各组测试数据特点如下：

数据1：只有1个元素；
数据2：11个不相同的整数，测试基本正确性；
数据3：103个随机整数；
数据4：104个随机整数；
数据5：105个随机整数；
数据6：105个顺序整数；
数据7：105个逆序整数；
数据8：105个基本有序的整数；
数据9：105个随机正整数，每个数字不超过1000。
输入格式:
输入第一行给出正整数 n（≤10
5
 ），随后一行给出 n 个（长整型范围内的）整数，其间以空格分隔。

输出格式:
在一行中输出从小到大排序后的结果，数字间以 1 个空格分隔，行末不得有多余空格。
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
int n;
int partition(int a[], int low, int high)
{
	int key = a[low];
	while (low < high)
	{
		while (low < high && a[high] >= key) high--;
		a[low] = a[high];
		while (low < high && a[low] <= key) low++;
		a[high] = a[low];
	}
	a[low] = key;
	return low;
}          //快排模版要记熟!!!
void qsort(int a[],int low,int high)
{
	if (low < high)
	{
		int key = partition(a, low, high);
		qsort(a, low, key - 1);
		qsort(a, key + 1, high);
	}
}
int main()
{
	int a[100000];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	qsort(a, 0, n - 1);
	cout << a[0];
	for (int i = 1; i < n; i++)
		cout << " " << a[i];
}