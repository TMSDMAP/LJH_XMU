/*
6.3 一笔画
分数 15
作者 张志梅
单位 青岛大学
小丁最近迷恋上一个游戏，传说中的“一笔画”游戏。

那么什么是一笔画？如下图，顾名思义就是一笔可以完成的图。一笔画最基本的要求是在画图的过程中，笔不能离开纸，且笔所画过的线不能重复，最后画完所有的线便算完成。

虽然小丁喜欢玩这个游戏，但有时候花费半天也找不到答案。小丁听说写一个计算机程序便能判断是否可以一笔画图，所以他希望善良可爱的你来帮帮他的忙。

快来帮帮弱小，可怜，又无助的小丁。

评测数据加强啦，来验题吧~~

输入格式:
给出图中的节点数N（1<=N<=1000,编号1-N）和边数M；随后M行给出存在边的两个节点的编号。

输出格式:
能够一笔画的图输出Y，否则输出N。*/


/*
题目解析:我使用了一笔画定理:
1.
图形是联通的;
2.
图形中的奇点（与奇数条边相连的点）个数为0或2；*/
#include <iostream>
#include <vector>
using namespace std;
vector<int> adjList[1000];    //使用邻接表存储
bool visited[1000];
int t1;
int flag = 0;
void dfs(int v)				//dfs判断图形是否联通
{
	visited[v] = true;
	for (int i : adjList[v])
	{
		if (!visited[i])
		{
			dfs(i);
		}
	}
	//cout << sum <<" "<<t1<< endl;
	//if (sum == t1) flag = 1;
}
int main()
{
	int N, M;
	cin >> N >> M;
	int a, b;
	int s = 0;
	int t1 = N;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}
	//cout << t1;
	dfs(1);
	int count = 0;
	for (int i = 1; i <=N; i++)
		if (visited[i] == true) count++;
	//cout << count;
	int sum[1000] = { 0 };
	for (int i = 1; i <= N; i++)
	{
		for (int j : adjList[i])
			sum[i]++;
		if (sum[i] % 2 == 1) s++;			//计算奇数顶点个数
	}
	if ((s==0||s==2)&&count==N) cout << "Y";
	else cout << "N";
}



