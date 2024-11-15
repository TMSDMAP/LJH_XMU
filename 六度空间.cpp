/*
6.4 六度空间
分数 25
作者 DS课程组
单位 浙江大学
“六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。这个理论可以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个，也就是说，最多通过五个人你就能够认识任何一个陌生人。”如图1所示。

“六度空间”理论虽然得到广泛的认同，并且正在得到越来越多的应用。但是数十年来，试图验证这个理论始终是许多社会学家努力追求的目标。然而由于历史的原因，这样的研究具有太大的局限性和困难。随着当代人的联络主要依赖于电话、短信、微信以及因特网上即时通信等工具，能够体现社交网络关系的一手数据已经逐渐使得“六度空间”理论的验证成为可能。

假如给你一个社交网络图，请你对每个节点计算符合“六度空间”理论的结点占结点总数的百分比。

输入格式:
输入第1行给出两个正整数，分别表示社交网络图的结点数N（1<N≤10
3
 ，表示人数）、边数M（≤33×N，表示社交关系数）。随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个结点的编号（节点从1到N编号）。

输出格式:
对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。每个结节点输出一行，格式为“结点编号:（空格）百分比%”。*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
vector<int> adjList[1005];     //邻接表存储
int N, M;

void bfs()      //使用bfs遍历
{
	for (int i = 1; i <=N; i++)
	{
		bool visited[1005] = { false }; //每次都要清空数组
		queue<pair<int, int>> q;
		double count = 0;   //每次bfs都要用到visited!
		if (!visited[i])
		{
			visited[i] = true;
			q.push({ i,0 });
			while (!q.empty())
			{
				int node = q.front().first;
				int dist = q.front().second;
				q.pop();
				//cout << dist << endl;
				if (dist <= 6) count++;       //只有当dist<=6时才计数加一
				if (dist > 6) continue;
				for (int j : adjList[node])
					if (!visited[j])
					{
						visited[j] = true;
						q.push({ j,dist + 1 });
					}
			}
			//cout << count << endl;
			double ave = (count / N)*100;
			printf("%d: %.2f%%\n",i,ave);
		}
	}
}
int main()
{
	cin >> N>> M;
	int a, b;
	for (int i = 1; i <=M; i++)
	{
		cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}
	bfs();
}
