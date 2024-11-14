/*
题目简介
6.0 列出连通集
分数 10
作者 陈越
单位 浙江大学
给定一个有 n 个顶点和 m 条边的无向图，请用深度优先遍历（DFS）和广度优先遍历（BFS）分别列出其所有的连通集。假设顶点从 0 到 n−1 编号。进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。

输入格式:
输入第 1 行给出 2 个整数 n (0<n≤10) 和 m，分别是图的顶点数和边数。随后 m 行，每行给出一条边的两个端点。每行中的数字之间用 1 空格分隔。

输出格式:
按照"{ v1v2​... vk​ }"的格式，每行输出一个连通集。先输出 DFS 的结果，再输出 BFS 的结果。*/

#include <iostream>
#include <queue>
using namespace std;
int G[10][10] = { 0 };
int visited[10] = {0};
int t;
queue<int> q;          //队列用于广搜
void dfs(int v)         //深搜模板
{
	 cout << v << " ";
	visited[v] = true;
	for (int i = 0; i < t; i++)
	{
		if (!visited[i] && (G[v][i]||G[i][v])&&i!=v)      //注意这里作者使用的是无向图,所以两端都要判断
			dfs(i);                      //dfs递归
	}
}
void bfs()                     //bfs
{
	for (int i = 0; i < t; i++)     //对每个元素遍历,入队,主要是为了防止非连通图遗漏节点
	{
		if (!visited[i])
		{
			cout << "{ ";
			visited[i] = true;
			cout << i << " ";
			q.push(i);               //如果未被访问,入队列
			while (!q.empty())         //遍历栈找到邻接节点入队列
			{
			int	u = q.front();
				q.pop();				//出队列
				for (int j = 0; j < t; j++)
				{
					if (!visited[j] && (G[u][j] || G[j][u]) && j != u)
					{
						visited[j] = true;
						cout << j << " ";
						q.push(j);
					}
				}
			}
			cout << "}" << endl;
		}

	}
}
int main()
{
	int n, m;
	cin >> n >> m;
	t = n;
	for (int i = 0; i < m; i++)
	{
		int j, k;
		cin >> j >> k;
		G[j][k] = 1;
	}
	/*for (int i = 0; i < n; i++)
		for(int j = 0;j<n;j++)
		cout << G[i][j] << " ";*/
	for (int i = 0; i < n; i++)
	{
		if (!visited[i])
		{
			cout << "{ ";
			dfs(i);
			cout << "}" << endl;
		}
	}
	for (int i = 0; i < n; i++)
		visited[i] = 0;
	bfs();
}