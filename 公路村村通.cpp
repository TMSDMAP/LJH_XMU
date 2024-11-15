//最小生成树
/*
6.5 公路村村通
分数 25
作者 陈越
单位 浙江大学
现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，求使每个村落都有公路连通所需要的最低成本。

输入格式:
输入数据包括城镇数目正整数 n（≤1000）和候选道路数目 m（≤3n）；随后的 m 行对应 m 条道路，每行给出 3 个正整数，分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。为简单起见，城镇从 1 到 n 编号。

输出格式:
输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出 −1，表示需要建设更多公路。*/
//最小生成树问题,使用prim算法解决(稀疏图)
#include <iostream>
#include <queue>
#include <vector>
#define INF 0x3F3F3F3F
using namespace std;
bool visited[1005];
int lowcost[1005]= {INF};  //lowcost数组存储每个节点到已选中节点的最短路径
vector<pair<int, int>> adjList[1005];        //邻接表存储权重和顶点序号
int Prim(int v, int n)
{
	int sw = 0;
	visited[v] = true;
	for (auto i : adjList[v])
		lowcost[i.first] = i.second;
	for (int k = 0; k < n - 1; k++)
	{
		int minCost = INF;
		int minIndex = -1;
		for (int j = 1; j <= n; j++)       //寻找未访问节点到已选中节点的(min(lowcost))最短的路径的权重
		{
			if (!visited[j] && lowcost[j] < minCost) {
				minCost = lowcost[j];
				minIndex = j;
			}
		}
		if (minIndex == -1)        //非连通图,返回-1
			return -1;
		visited[minIndex] = true;
		sw += minCost;
		for (auto i : adjList[minIndex])
		{
			int l = i.first;
			int weight = i.second;
			if (!visited[l] && weight < lowcost[l])			//更新lowcost数组
				lowcost[l] = weight;
		}
	}
	return sw;
}
int main()
{
	int n, m;
	cin >> n >> m;
	int a, b,w;
	for (int i = 1; i <= m; i++)			//一定要注意1-n要一致,输入为1-n就不能再是0-n-1
	{
		cin >> a >> b >> w;
		adjList[a].push_back({ b,w });
		adjList[b].push_back({ a,w });
	}
	for (int i = 1; i <=n; i++)
		lowcost[i] = INF;
	lowcost[1] = 0;			//初始化数组
	int k = Prim(1, n);
	cout << k;
}