/*
8.2 二分查找
分数 28
作者 李廷元
单位 中国民用航空飞行学院
请实现有重复数字的有序数组的二分查找。

输出在数组中第一个大于等于查找值的位置，如果数组中不存在这样的数，则输出数组长度加一。

输入格式:
输入第一行有两个数，第一个数为数组长度n（≤10^6），第二个数为需要查找的数。

接下来有n个整数，以空格或换行符分隔。

输出格式:
输出待查找的数的位置。
*/
#include <iostream>
#include <algorithm>
#define N 1000005
using namespace std;
int a[N];
int binary_search(int key, int n)
{
	int l = 0;
	int r = n - 1;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (a[mid] == key)
		{
			while (a[mid] == a[mid - 1])
			{
				mid--;
			}   //由于有重复数字，要定位在第一个大于等于查找值的位置，所以等于时mid要--
			return mid;
		}
		else if (a[mid] >= key) r = mid - 1;
		else l = mid + 1;
	}
	return l;
}  //二分查找模板
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a + n);
	if (a[n - 1] < m)
		cout << n + 1 << endl;
	else
	{
		int k = binary_search(m, n);
		cout << k + 1 << endl;
	}
}