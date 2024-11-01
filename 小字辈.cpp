/*
题目描述
5.3 小字辈
分数 25
作者 陈越
单位 浙江大学
本题给定一个庞大家族的家谱，要请你给出最小一辈的名单。

输入格式：
输入在第一行给出家族人口总数 N（不超过 100 000 的正整数） —— 简单起见，我们把家族成员从 1 到 N 编号。随后第二行给出 N 个编号，其中第 i 个编号对应第 i 位成员的父/母。家谱中辈分最高的老祖宗对应的父/母编号为 -1。一行中的数字间以空格分隔。

输出格式：
首先输出最小的辈分（老祖宗的辈分为 1，以下逐级递增）。然后在第二行按递增顺序输出辈分最小的成员的编号。编号间以一个空格分隔，行首尾不得有多余空格。
*/
//本题目主要难点在于如何找到并按顺序输出最小辈分
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int max_deep = 1;
const int N = 1e5 + 5;
vector<int> son[N], res; //考虑到这不是二叉树,可以使用sonvector数组来存储每棵子树
void dfs(int x, int deep)  //可以使用dfs,对每棵子树进行BFS找到最大深度并记录,并且不断更新res容器
{
	if (deep > max_deep)   //有更大深度时清空容器并更新深度,记录元素
	{ 
		res.clear();
		max_deep = deep;
		res.push_back(x);
	}
	else if (deep == max_deep)  //进入res容器
		res.push_back(x);
	for (auto t : son[x]) dfs(t, deep + 1);  //对每棵子树dfs
}
/*
void bfs(int root) {
	queue<pair<int, int>> q; // 队列中存储节点及其深度
	q.push({root, 1});       // 从根节点开始，假设根节点深度为1
	max_deep = 1;            // 初始化最大深度为1
	res.clear();             // 清空结果容器

	while (!q.empty()) {
		auto [node, depth] = q.front();
		q.pop();

		if (depth > max_deep) {   // 更新最大深度并清空结果容器
			max_deep = depth;
			res.clear();
			res.push_back(node);
		} else if (depth == max_deep) { // 深度相同的节点加入结果
			res.push_back(node);
		}

		// 将当前节点的子节点加入队列，深度+1
		for (int child : son[node]) {
			q.push({child, depth + 1});
		}
	}
}*/         //这是使用BFS实现,注意使用队列同时存储节点及其深度
int main()
{
	int n, T;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int t;
		cin >> t;
		if (t == -1) T = i;
		else son[t].push_back(i);   //每棵子树初始化
	}
	dfs(T, 1);  
	cout << max_deep << endl;
	sort(res.begin(), res.end());  //调用算法库进行快排
	cout << res[0]; 
	for (int i = 1; i < res.size(); ++i) cout << " " << res[i];
}