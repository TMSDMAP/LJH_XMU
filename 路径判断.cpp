/*
题目简介
6.2 路径判断
分数 15
作者 DS课程组
单位 临沂大学
给定一个有N个顶点和E条边的无向图，请判断给定的两个顶点之间是否有路径存在。
假设顶点从0到N−1编号。

输入格式:
输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。

随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。

最后一行给出两个顶点编号i，j（0≤i,j<N）,i和j之间用空格分隔。

输出格式:
如果i和j之间存在路径，则输出"There is a path between i and j."，

否则输出"There is no path between i and j."。
*/
#include <iostream>
using namespace std;
int G[10][10] = {0};			//使用邻接矩阵进行存储
bool visited[10];
int f, e;
int t;
bool dfs(int v)				//可以使用DFS来搜索,如果顶点为e,则说明存在路径,否则就不存在
{
	if (v == e) return true;
	visited[v] = true;
	for (int i = 0; i < t; i++)
	{
		if (!visited[i] && (G[v][i] || G[i][v]) && i != v)
			if (dfs(i)) return true;
	}
	return false;
}
int main()
{
	int N, E;
	cin >> N >> E;
	t = N;
	int a, b;
	for (int i = 0; i < E; i++) {
		cin >> a >> b;
		G[a][b] = 1;
	}
	cin >> f >> e;
	if (dfs(f))
		cout << "There is a path between "<<f<<" and "<<e<<".";
	else
	{
		cout << "There is no path between " << f << " and " << e << ".";
	}
	return 0;
}			//十分基础的一道题,考察DFS