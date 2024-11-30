/*
7-3 最短工期
分数 25
作者 陈越
单位 浙江大学
一个项目由若干个任务组成，任务之间有先后依赖顺序。项目经理需要设置一系列里程碑，在每个里程碑节点处检查任务的完成情况，并启动后续的任务。现给定一个项目中各个任务之间的关系，请你计算出这个项目的最早完工时间。

输入格式：
首先第一行给出两个正整数：项目里程碑的数量 N（≤100）和任务总数 M。这里的里程碑从 0 到 N−1 编号。随后 M 行，每行给出一项任务的描述，格式为“任务起始里程碑 任务结束里程碑 工作时长”，三个数字均为非负整数，以空格分隔。

输出格式：
如果整个项目的安排是合理可行的，在一行中输出最早完工时间；否则输出"Impossible"。*/

//关键路径，涉及最早发生时间和最迟开始时间
//这里求最早发生时间即可，ve（0）=0开始递推
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
vector<vector<int>> graph;
vector<int> inDegree;
int ve[105];
int path[105][105];
void FindInDegree(int n)
{
    inDegree.resize(n, 0);
    for (int i = 0; i < n; i++)
        for (auto neighbor : graph[i])
            inDegree[neighbor]++;
}
stack<int> T;   //T栈是用来存储拓扑序列顶点栈
bool TopologicalOrder(int n)
{
    stack<int> S;  //S栈来存储零入度点
    FindInDegree(n);
    int count = 0;
    for (int i = 0; i < n; i++)
        if (inDegree[i] == 0) 
            S.push(i);      //入栈
    while (!S.empty())
    {
        int j = S.top();
        S.pop();
        T.push(j);
        count++;   
        for (auto neighbor : graph[j])      
        {
            if (--inDegree[neighbor] == 0) S.push(neighbor);
            if (ve[j] + path[j][neighbor] > ve[neighbor]) ve[neighbor] = ve[j] + path[j][neighbor];   //更新最早发生时间
        }
    }
    if (count < n) return false;
    return true;
}
int count = 0;
int main()
{
    int N, M;
    cin >> N >> M;
    graph.resize(N);
    for (int i = 0; i < M; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back(b);
        path[a][b] = c;
    }
    //cout<<1<<endl;
    if (!TopologicalOrder(N)) cout << "Impossible";
    else
    {
        int max = -1;
        for (int i = 0; i < N; i++)
        {
            if (ve[i] > max) max = ve[i];
        }   //找出最大的ve[i]并输出
        cout << max;
    }

    return 0;
}
