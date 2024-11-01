/*
问题描述
5.2 修理牧场
分数 25
作者 DS课程组
单位 浙江大学
农夫要修理牧场的一段栅栏，他测量了栅栏，发现需要 n 块木头，每块木头长度为整数 li​ 个长度单位，于是他购买了一条很长的、能锯成 n 块的木头，即该木头的长度是 li​ 的总和。

但是农夫自己没有锯子，请人锯木的酬金跟这段木头的长度成正比。为简单起见，不妨就设酬金等于所锯木头的长度。例如，要将长度为 20 的木头锯成长度为 8、7 和 5 的三段，第一次锯木头花费 20，将木头锯成 12 和 8；第二次锯木头花费 12，将长度为 12 的木头锯成 7 和 5，总花费为 32。如果第一次将木头锯成 15 和 5，则第二次锯木头花费 15，总花费为 35（大于 32）。

请编写程序帮助农夫计算将木头锯成 n 块的最少花费。

输入格式:
输入首先给出正整数 n（≤10
4
 ），表示要将木头锯成 n 块。第二行给出 n 个正整数（≤50），表示每段木块的长度。

输出格式:
输出一个整数，即将木头锯成 n 块的最少花费。*/
//典型的哈夫曼树
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct{
	unsigned int weight;
	unsigned int parent, lchild, rchild;   //构建哈夫曼树节点
}HTNode,*HuffmanTree;   
int flag[10005] = { 0 };  //设立标志数组
void Select(HuffmanTree &HT, int n, int& s1, int& s2)  //n是在前i个元素中找到两个最小值
{
	int min1 = 0x7FFFFFFF;  // 初始化一个很大的值作为最小值的初始比较值
	int min2 = 0x7FFFFFFF;  
	s1 = -1;  //最小值
	s2 = -1;  //次小值
	for (int i = 0; i < n; i++) {
		if (!flag[i]&&HT[i].weight < min1) {   //若第i个元素未被取值(即取值后被抹去),且权值小于最小值
			min2 = min1;						//次小值一定要比最小值大,这里让二者相等
			s2 = s1;
			min1 = HT[i].weight;          //s1,s2均更新,s2=s1,s1=i;
			s1 = i;
		}
		else if (!flag[i]&& HT[i].weight < min2) {  //判断完最小值后再判断次小值
			min2 = HT[i].weight;
			s2 = i;
		}
	}
}  //哈夫曼树得到两个最小值
void HuffmanTreebuild(HuffmanTree &HT, int* w, int n)   //创建哈夫曼树
{
	if (n <= 1) return;  //节点小于等于1,返回
	int m = 2 * n - 1;	//总结点树等于叶节点*2+1
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	HuffmanTree p;
	int i;
	for ( p = HT,  i = 0; i < n; i++, p++, w++) //初始化前n个元素
	{
		p->weight = *w;
		p->parent = p->lchild = p->rchild = 0;
	}
	for (; i < m; i++, p++) //初始化其余元素
	{
		p->weight = p->parent = p->lchild = p->rchild = 0;
	}
	int s1, s2;
	for (i = n; i < m; i++)
	{
		Select(HT, i,s1,s2);  //找到最小,次小值
		flag[s1] = flag[s2] = 1;  //做上标记
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;        //分别进行赋值即可
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	int w[60];
	HuffmanTree HT;
	for (int i = 0; i < n; i++)
		scanf("%d",&w[i]);
	HuffmanTreebuild(HT, w, n);
	int sum = 0;
	for (int i = n; i < 2 * n - 1; i++)
	{
		sum += HT[i].weight;   //这里要求的是所有n+1到m节点的总和
	}
	printf("%d\n",sum);
}