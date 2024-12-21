/*
9.5 PAT排名汇总
分数 25
作者 陈越
单位 浙江大学
计算机程序设计能力考试（Programming Ability Test，简称PAT）旨在通过统一组织的在线考试及自动评测方法客观地评判考生的算法设计与程序设计实现能力，科学的评价计算机程序设计人才，为企业选拔人才提供参考标准（网址http://www.patest.cn）。

每次考试会在若干个不同的考点同时举行，每个考点用局域网，产生本考点的成绩。考试结束后，各个考点的成绩将即刻汇总成一张总的排名表。

现在就请你写一个程序自动归并各个考点的成绩并生成总排名表。

输入格式:
输入的第一行给出一个正整数N（≤100），代表考点总数。随后给出N个考点的成绩，格式为：首先一行给出正整数K（≤300），代表该考点的考生总数；随后K行，每行给出1个考生的信息，包括考号（由13位整数字组成）和得分（为[0,100]区间内的整数），中间用空格分隔。

输出格式:
首先在第一行里输出考生总数。随后输出汇总的排名表，每个考生的信息占一行，顺序为：考号、最终排名、考点编号、在该考点的排名。其中考点按输入给出的顺序从1到N编号。考生的输出须按最终排名的非递减顺序输出，获得相同分数的考生应有相同名次，并按考号的递增顺序输出。
*/
//应该是归并排序，但是我用的快排，过了
#include <iostream>
#include <algorithm>
using namespace std;
struct student
{
	char s[15];       //考号
	int score;		  //分数
	int number;       //组号
	int rank;      //在所有人的排名
	int irank;   //在组内排名
};
student S[30000];
bool compare(student a, student b)
{
	if (a.score > b.score) return true;
	else if (a.score == b.score)
	{
		if (strcmp(a.s, b.s) > 0) return false;
		else return true;
	}
	else return false;
}         //编写一个compare函数用于自带的sort函数
int main()
{
	int m = 0;
	int m1 = 0;
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int k;
		cin >> k;
		for (int j = 0; j < k; j++)
		{
			cin >> S[m].s >> S[m].score;
			S[m].number = i + 1;
			S[m].rank = m+1;
			S[m].irank = j + 1;
			m++;
		}       //初始化
		sort(S + m1, S + m, compare);   //对每一组进行排序
		for (int k = m1; k < m; k++)
			S[k].irank = k - m1 + 1;
		for (int k = m1+1; k < m; k++)
		{
			if (S[k].score == S[k - 1].score) S[k].irank = S[k - 1].irank;
		}
			m1 = m;
	}
	sort(S, S + m, compare);    //对全部排序
	cout << m << endl;
	for (int i = 0; i < m; i++)
	{
		S[i].rank = i+1;
	}
	for (int i = 1; i < m; i++)
	{
		if (S[i].score == S[i - 1].score)
			S[i].rank = S[i - 1].rank;
	}        //相同分数学生有相同名次
	for (int i = 0; i < m; i++)
	{
		cout << S[i].s << " " << S[i].rank << " " << S[i].number << " " << S[i].irank << endl;
	}
}