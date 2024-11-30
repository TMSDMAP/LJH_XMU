/*
7-2 任务调度的合理性
分数 25
作者 DS课程组
单位 浙江大学
假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成了其它一些子任务后才能执行。“任务调度”包括一组子任务、以及每个子任务可以执行所依赖的子任务集。

比如完成一个专业的所有课程学习和毕业设计可以看成一个本科生要完成的一项工程，各门课程可以看成是子任务。有些课程可以同时开设，比如英语和 C 程序设计，它们没有必须先修哪门的约束；有些课程则不可以同时开设，因为它们有先后的依赖关系，比如 C 程序设计和数据结构两门课，必须先学习前者。

但是需要注意的是，对一组子任务，并不是任意的任务调度都是一个可行的方案。比如方案中存在“子任务 a 依赖于子任务 b，子任务 b 依赖于子任务 c，子任务 c 又依赖于子任务 a”，那么这三个任务哪个都不能先执行，这就是一个不可行的方案。你现在的工作是写程序判定任何一个给定的任务调度是否可行。

输入格式:
输入说明：输入第一行给出子任务数 n（≤100），子任务按 1~n 编号。随后 n 行，每行给出一个子任务的依赖集合：首先给出依赖集合中的子任务数 k，随后给出 k 个子任务编号，整数之间都用空格分隔。

输出格式:
如果方案可行，则输出 1，否则输出 0。*/
//所有的子任务构成图，需要先从入度为零的节点入手，把它移除后，与之相邻的节点入度减一接着移出其他入度为零的节点，这就是拓扑排序
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> graph;   //建立一个邻接表来存储图结构
vector<int> inDegree;   //使用vector类型的入度数组来存储入度
void FindInDegree(int n)
{
    inDegree.resize(n, 0);    //使用resize初始化
    for (int i = 0; i < n; i++)
        for (auto neighbor : graph[i])  //使用邻接表的好处
            inDegree[neighbor]++;
}  //先统计入度
bool TopologicalSort(int n)   //进行拓扑排序
{
    queue<int> q;           //这里使用的是队列进行拓扑排序，使用栈也可以
    for (int i = 0; i < n; i++)
        if (inDegree[i] == 0)
            q.push(i);     //入度为零进队列
    int count = 0;
    while (!q.empty())
    {
        int s = q.front();
        q.pop();                                
        count++;                        //出队列，将与之相邻节点入度减一，将入度为零节点入队列
        for (auto neighbor : graph[s])
        {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0)
                q.push(neighbor);
        }
    }
    return count == n;     //判断是否存在异常问题
}
int main()
{
    int n, k;
    cin >> n;
    graph.resize(n);   //使用resize规划大小
    for (int i = 0; i < n; i++)
    {
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int s;
            cin >> s;
            graph[i].push_back(s - 1);
        }
    }
    FindInDegree(n);
    cout << TopologicalSort(n);
    return 0;
}
