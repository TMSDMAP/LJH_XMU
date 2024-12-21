/*
8.4 字符串关键字的散列映射
分数 29
作者 DS课程组
单位 浙江大学
给定一系列由大写英文字母组成的字符串关键字和素数P，用移位法定义的散列函数H(Key)将关键字Key中的最后3个字符映射为整数，每个字符占5位；再用除留余数法将整数映射到长度为P的散列表中。例如将字符串AZDEG插入长度为1009的散列表中，我们首先将26个大写英文字母顺序映射到整数0~25；再通过移位将其映射为3×32的平方+4×32+6=3206；然后根据表长得到3206%1009=179，即是该字符串的散列映射位置。

发生冲突时请用平方探测法解决。

输入格式:
输入第一行首先给出两个正整数N（≤500）和P（≥2N的最小素数），分别为待插入的关键字总数、以及散列表的长度。第二行给出N个字符串关键字，每个长度不超过8位，其间以空格分隔。

输出格式:
在一行内输出每个字符串关键字在散列表中的位置。数字间以空格分隔，但行末尾不得有多余空格。
*/
//由于这个题目给出了哈希函数和冲突解决方法，只需要按照题目建立函数就行了
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int N, P;

string a[1050];    //使用了string数组存储字符串
int get_Hash(char* s)   //得到对应的hash值
{
	int t = strlen(s);
	int k;
	if (t == 2)      //一定要注意可能出现小于3的情况
		k = (s[t - 2] - 'A') * 32 + s[t - 1] - 'A';
	else if (t == 1)
		k = s[t - 1] - 'A';
	else
		k = (s[t - 3] - 'A') * 32 * 32 + (s[t - 2] - 'A') * 32 + s[t - 1] - 'A';
	//cout << k << endl;
	while (k / P)      
	{
		k = k % P;
	}   //k对P取余，P是质数
	//cout << k << endl;
	if (a[k].empty() || a[k] == s)  //加上了a[k] == s是因为可能会有重复数字，此时就相当于查找了
	{
		a[k] = s;
		return k;
	}           
	else
	{
		int i = 0;
		while (++i)
		{
			int q = k + i * i;   //平方探测
			while (q >= P) q = q - P;
			int q1 = k - i * i;
			while (q1 < 0) q1 = q1 + P;
			if (a[q].empty() || a[q] == s) {
				a[q] = s; return q;
			}
			else if (a[q1].empty() || a[q1] == s) {
				a[q1] = s; return q1;
			}
		}   //道理都是一样的，while循环不断使用平方探测法去探测
	}
}
int main()
{
	cin >> N >> P;
	for (int i = 0; i < N; i++)
	{
		char s[10];
		cin >> s;
		int k = get_Hash(s);
		if (i < N - 1)
			cout << k << " ";
		else cout << k;
	}
	return 0;
}