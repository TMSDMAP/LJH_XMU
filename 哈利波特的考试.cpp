﻿/*
7-4 哈利·波特的考试
分数 25
作者 陈越
单位 浙江大学
哈利·波特要考试了，他需要你的帮助。这门课学的是用魔咒将一种动物变成另一种动物的本事。例如将猫变成老鼠的魔咒是 haha，将老鼠变成鱼的魔咒是 hehe 等等。反方向变化的魔咒就是简单地将原来的魔咒倒过来念，例如 ahah 可以将老鼠变成猫。另外，如果想把猫变成鱼，可以通过念一个直接魔咒 lalala，也可以将猫变老鼠、老鼠变鱼的魔咒连起来念：hahahehe。

现在哈利·波特的手里有一本教材，里面列出了所有的变形魔咒和能变的动物。老师允许他自己带一只动物去考场，要考察他把这只动物变成任意一只指定动物的本事。于是他来问你：带什么动物去可以让最难变的那种动物（即该动物变为哈利·波特自己带去的动物所需要的魔咒最长）需要的魔咒最短？例如：如果只有猫、鼠、鱼，则显然哈利·波特应该带鼠去，因为鼠变成另外两种动物都只需要念 4 个字符；而如果带猫去，则至少需要念 6 个字符才能把猫变成鱼；同理，带鱼去也不是最好的选择。

输入格式:
输入说明：输入第 1 行给出两个正整数 n (≤100)和 m，其中 n 是考试涉及的动物总数，m 是用于直接变形的魔咒条数。为简单起见，我们将动物按 1~n 编号。随后 m 行，每行给出了 3 个正整数，分别是两种动物的编号、以及它们之间变形需要的魔咒的长度(≤100)，数字之间用空格分隔。

输出格式:
输出哈利·波特应该带去考场的动物的编号、以及最长的变形魔咒的长度，中间以空格分隔。如果只带1只动物是不可能完成所有变形要求的，则输出 0。如果有若干只动物都可以备选，则输出编号最小的那只。*/

//求最短路径可以使用迪杰斯特拉算法或者弗洛伊德算法，迪杰斯特拉算法是求所有点到某一点的最短路径，弗洛伊德算法是求每一对顶点之间的最短路径
//这里使用的是弗洛伊德算法
#include <iostream>
#define Inf 0x7f7f7f7f
using namespace std;
int arcs[105][105];   //使用邻接矩阵无向图存储（因为反向长度不变）
int D[105][105];      //用来存储最短路径
void floyd(int n)
{
    for (int v = 1; v <=n; v++)
        for (int w = 1; w <=n; w++)
        {
            if (v == w) D[v][w] = 0;
            else if (arcs[v][w] != 0)
                D[v][w] = arcs[v][w];
            else
                D[v][w] = Inf;
            //if(D[v][w]!=Inf)
           // cout<<D[v][w]<<endl;
        }       //先对D最短路径数组进行初始化
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <=n; v++)
            for (int w = 1; w <=n; w++) 
               //关键的三重循环   注意u作为中介节点，只能放在最外层循环，因为每次中间节点的选择要使用更新过的数据，如果放在内层的话会导致不是每个点的数据都更新，重点是对矩阵的不断更新
            {
               // cout << D[v][w] << endl;
                if (D[v][u] != Inf && D[u][w] != Inf&&D[v][u] + D[u][w] < D[v][w]) {   //注意是要排除不等于Inf的点
                    D[v][w] = D[v][u] + D[u][w];
                }

            }
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        arcs[a][b] = c;
        arcs[b][a] = c;
    }
    floyd(n);

    int v;
    int max[105] = { -1 };
    int s[105] = { -1 };
    for (int i = 1; i <=n; i++)
    {
       // cout << endl;
        //int max = -1;
        for (int j = 1; j <=n; j++)
        {
            if (i != j && D[i][j] == Inf) s[i] = 1;
           // if (D[i][j] != Inf) cout << D[i][j] << " ";
            // cout<<D[i][j]<<endl;
             //if(D[i][j]==0) {cout<<0;return 0;}
            if (D[i][j] != Inf&& D[i][j] > max[i]) { max[i] = D[i][j]; }
        }
    }           //注意看题目要求是要在所有最长的路径中找出最短的一条
   // cout << endl;
    int q = Inf;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == 1) { cout << '0' << endl; return 0; }
    }
    for (int i = 1; i <=n; i++)
    {
       // cout << max[i] << " ";
        if (max[i] < q) { q = max[i]; v = i; }          //注意找出最短的一条
    }
    cout << v << " " << q;
    return 0;
}
