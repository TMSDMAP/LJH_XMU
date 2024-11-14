/*
题目简介
6.1 图深度优先遍历
分数 10
作者 朱允刚
单位 吉林大学
编写程序对给定的有向图（不一定连通）进行深度优先遍历，图中包含n个顶点，编号为0至n-1。本题限定在深度优先遍历过程中，如果同时出现多个待访问的顶点，则优先选择编号最小的一个进行访问，以顶点0为遍历起点。

输入格式:
输入第一行为两个整数n和e，分别表示图的顶点数和边数，其中n不超过20000，e不超过50。接下来e行表示每条边的信息，每行为两个整数a、b，表示该边的端点编号，但各边并非按端点编号顺序排列。

输出格式:
输出为一行整数，每个整数后一个空格，即该有向图的深度优先遍历结点序列。*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> adjList[20000];           //使用邻接表实现,这是一个稀疏图
bool visited[20000];
void dfs(int v)
{
	visited[v] = true;
	cout << v << " ";
	for (int i : adjList[v])      //所有与v相连的节点
	{
		if (!visited[i])
			dfs(i);
	}
}
int main()
{
	int n, e;
	int a, b;
	cin >> n >> e;
	for (int i = 0; i < e; i++)
	{
		cin >> a >> b;
		adjList[a].push_back(b);
	}
	for (int i = 0; i < n; i++)
	{
		if (!adjList[i].empty())
			sort(adjList[i].begin(), adjList[i].end());      //先对邻接节点排序
	}
	for (int i = 0; i < n; i++) {
		if (!visited[i])
			dfs(i);
	}
}