/*
9.3 插入排序还是堆排序
分数 22
作者 陈越
单位 浙江大学
根据维基百科的定义：

插入排序是迭代算法，逐一获得输入数据，逐步产生有序的输出序列。每步迭代中，算法从输入序列中取出一元素，将之插入有序序列中正确的位置。如此迭代直到全部元素有序。

堆排序也是将输入分为有序和无序两部分，迭代地从无序部分找出最大元素放入有序部分。它利用了大根堆的堆顶元素最大这一特征，使得在当前无序区中选取最大元素变得简单。

现给定原始序列和由某排序算法产生的中间序列，请你判断该算法究竟是哪种排序算法？

输入格式：
输入在第一行给出正整数 n (≤100)；随后一行给出原始序列的 n 个整数；最后一行给出由某排序算法产生的中间序列。这里假设排序的目标序列是升序。数字间以空格分隔。

输出格式：
首先在第 1 行中输出 Insertion Sort 表示插入排序、或 Heap Sort 表示堆排序；然后在第 2 行中输出用该排序算法再迭代一轮的结果序列。题目保证每组测试的结果是唯一的。数字间以空格分隔，且行首尾不得有多余空格。
*/
//作者一开始想要通过中间序列前后的有序性比较来判断，但是始终有一个点过不了，可能是有对称序列存在，因此最保险的方法是
//使用选择排序和堆排序每一步进行比较，使用flag来判断是否成立。（这里在flag变为1后仍然进行了一次循环，可以输出下一次的中间序列）
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;
int a[100];
int b[100];//中间序列
int c[100];
void insertsort(int a[],int start,int end)
{
	int i;
	int j = end + 1;
	int key = a[j];
	for ( i = end; i >= start; i--)
	{
		if (a[i] > key)
			a[i + 1] = a[i];
		else break;
	}
	a[i + 1] = key;
}      //插入排序
bool judge(int a[], int b[], int n)
{
	for (int i = 0; i < n; i++)
		if (a[i] != b[i]) return false;
	return true;
}         //判断序列是否相等
void toMaxHeap(int a[], int size, int index)
{
	int l = 2 * index + 1;
	int r = 2 * index + 2;
	int maxIndex = index;
	if (l<size && a[l]>a[maxIndex]) maxIndex = l;
	if (r<size && a[r]>a[maxIndex]) maxIndex = r;
	if (maxIndex != index) {
		swap(a[index], a[maxIndex]);
		toMaxHeap(a, size, maxIndex);
	}
}     //堆排序模板
void heapsort(int a[],int length)
{
	int flag = 0;
	int startIndex = (length - 2) / 2;
	for (int i = startIndex; i >= 0; i--)
		toMaxHeap(a, length, i);
	for (int i = length - 1; i > 0; i--) {
		swap(a[i], a[0]);
		toMaxHeap(a, i, 0);
		if (flag == 1) break;
		if (judge(a, b, length)) flag = 1;
	}
}     //堆排序模板
int main()
{
	int n;
	int flag = 0;
	int count1 = 0; int count2 = 0;
	int k1, k2;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		cin >> b[i];
	//sort(a, a + n);
	for (int i = 0; i < n; i++)
		c[i] = a[i];
	/*for (int i = 1; i < n; i++)
	{
		if (b[i + 1] > b[i]) count1++;
		else {
			k1 = i;
			 break;
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		if (b[i - 1] < b[i]) count2++;
		else
		{
			k2 = i;
			break;
		}
	}*/
	//cout << count1 << " " << count2;
	/*if (count1>count2)
	{
		flag = 1;
		cout << "Insertion Sort" << endl;
	}
	else cout << "Heap Sort" << endl;*/
	//k1,k2是分界点
	//cout << k1;
	for (int k1 = 0; k1 < n; k1++)
		{
			insertsort(a, 0, k1); //单次插入排序
			/*cout << a[0];
			for (int i = 1; i < n; i++)
				cout << " " << a[i];
			cout << endl;*/
			if (flag == 1) break;
			if (judge(a, b, n))
			{
				flag = 1;
				cout << "Insertion Sort" << endl;
			}
		}
	if (flag == 1)
		{
			cout << a[0];
			for (int i = 1; i < n; i++)
				cout << " " << a[i];
		}
	if(flag==0)
	{
		cout << "Heap Sort" << endl;
		heapsort(c, n);
		cout << c[0];
		for (int i = 1; i < n; i++)
			cout << " "<< c[i];
	}
}

