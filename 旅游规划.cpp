/*
7-1 旅游规划
分数 25
作者 陈越
单位 浙江大学
有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的过路费。现在需要你写一个程序，帮助前来咨询的游客找一条出发地和目的地之间的最短路径。如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

输入格式:
输入说明：输入数据的第 1 行给出 4 个正整数 n、m、s、d，其中 n（2≤n≤500）是城市的个数，顺便假设城市的编号为 0~(n−1)；m 是高速公路的条数；s 是出发地的城市编号；d 是目的地的城市编号。随后的 m 行中，每行给出一条高速公路的信息，分别是：城市 1、城市 2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过 500。输入保证解的存在。

输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。*/
//求两点间的最短路径，使用迪杰斯特拉算法，一定要熟记迪杰斯特拉算法！！！
//这个代码使用了大用量的数组来存储，在VSstudio上运行会显示StackOverflow在codeblock上可以运行
#include  <iostream>
using namespace std;
#define Inf 0x3f3f3f3f
struct  Cost {
	int dis;
	int price;
};   //Cost同时记录距离和价格
Cost D[500];
typedef struct {
	Cost arcs[501][501];
	int vexnum, arcnum;
}MGraph;    //建立邻接矩阵
MGraph G;
bool final[500];     //标志数组判断是否访问
int path[500];          //存储最短路径
void Dijkstra(MGraph G, int v0)
{
	for (int v = 0; v < G.vexnum; v++)
	{
		final[v] = false;
		D[v].dis = G.arcs[v0][v].dis;
		D[v].price = G.arcs[v0][v].price;
		if (D[v].dis != Inf) path[v] = v0;
		else path[v] = -1;
	}      //对数组进行初始化
	D[v0].dis = 0;
	final[v0] = true;
	for (int i = 1; i < G.vexnum; ++i)       //进行n-1次循环
	{
		int mini = Inf;
		int v;
		for (int w = 0; w < G.vexnum; w++)
		{

			if (!final[w])
				if (D[w].dis < mini) { v = w; mini = D[w].dis; }
		}           //这里是找到当前的最短路径点
		final[v] = true;
		for (int w = 0; w < G.vexnum; w++)
			if (!final[w] && (mini + G.arcs[v][w].dis < D[w].dis))
			{
				D[w].dis = mini + G.arcs[v][w].dis;
				D[w].price = D[v].price + G.arcs[v][w].price;
				path[w] = v;
			}                             //更新与该点的邻接点与源点的最短路径与价格（最短路径优先，所以先找到最短路径点，再找到最便宜的路径）
			else if (!final[w] && (mini + G.arcs[v][w].dis == D[w].dis) && (D[w].price > (D[v].price + G.arcs[v][w].price)))
			{
				D[w].dis = mini + G.arcs[v][w].dis;
				D[w].price = D[v].price + G.arcs[v][w].price;
				path[w] = v;    //用来记录w的前驱节点
			}
	}
}
int main()
{
	int n, m, s, d;
	cin >> n >> m >> s >> d;
	G.vexnum = n;
	G.arcnum = m;
	for (int i = 0; i < G.vexnum; i++)
		for (int j = 0; j < G.vexnum; j++)
		{
			if (j != i)
				G.arcs[i][j].dis = G.arcs[i][j].price = Inf;
			else
			{
				G.arcs[i][j].dis = 0;
			}
		}
	for (int i = 0; i < m; i++)
	{
		int j, k, q, p;
		cin >> j >> k >> q >> p;
		G.arcs[j][k].dis = G.arcs[k][j].dis = q;
		G.arcs[j][k].price = G.arcs[k][j].price = p;
	}
	Dijkstra(G, s);
	cout << D[d].dis << " " << D[d].price << endl;
}


