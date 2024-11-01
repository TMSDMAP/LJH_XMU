/*
题目简介
5.1 笛卡尔树
分数 25
作者 DS课程组
单位 浙江大学
笛卡尔树是一种特殊的二叉树，其结点包含两个关键字 k1和 k2。首先笛卡尔树是关于 k1 的二叉查找树，
即结点左子树的所有 k1 值都比该结点的 k1  值小，右子树则大。其次所有结点的 k2  关键字满足优先队列（不妨设为最小堆）的顺序要求，
即该结点的 k2​  值比其子树中所有结点的 k2 值小。给定一棵二叉树，请判断该树是否笛卡尔树。

输入格式:
输入首先给出正整数 n（≤1000），为树中结点的个数。随后 n 行，每行给出一个结点的信息，包括：结点的 k1 值、k2 值、左孩子结点编号、右孩子结点编号。
设结点从0~(n−1)顺序编号。
若某结点不存在孩子结点，则该位置给出 −1。

输出格式:
输出YES如果该树是一棵笛卡尔树；否则输出NO。*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define INF 500000
typedef struct TreeNode {
	int k1;
	int k2;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;    //创建二叉树结构体
int isBST(TreeNode* T, int min, int max)   //判断是否为二叉查找树
{											//这里同时设立min和max,一边比较时只用到了一边,可以不用引用(不涉及相关操作)
	if (T == NULL)   //树为空返回1(true)
		return 1;
	if (T->k1 <= min || T->k1 >= max) return 0;  //违背任意一个就OUT
	int t = isBST(T->lchild, min, T->k1) && isBST(T->rchild, T->k1, max);  //只有左子树递归且右子树递归均成立时才返回1
	return t;
}
int is_minHeap(TreeNode* T, int min)    //判断是否为最小堆
{
	if (T == NULL)
		return 1;						//树为空,返回true
	/*if ((T->lchild != NULL && T->lchild->k2 < T->k2) ||
		(T->rchild != NULL && T->rchild->k2 < T->k2))  
		return 0;*/
	if (T->k2 < min) return 0;   //两种方法都可以的
	int t = is_minHeap(T->lchild, T->k2) && is_minHeap(T->rchild, T->k2);
	return t;
}
int main()
{
	int n;
	TreeNode a[1005],*T=NULL;  //初始化为空
	int flag[1005] = { 0 };
	scanf("%d",&n);
	int l, r;
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%d%d", &(a[i].k1), &a[i].k2, &l, &r);
		if (l != -1)
		{
			a[i].lchild = &a[l];
			flag[l] = 1;
		}                                //连接链表(结构体数组)
		else
		{
			a[i].lchild = NULL;
		}
		if (r != -1)
		{
			a[i].rchild = &a[r];
			flag[r] = 1;
		}
		else
		{
			a[i].rchild = NULL;
		}
	}
	for (int i = 0; i < n; i++)
		if (flag[i] == 0) {
			T = &a[i]; break;
		}  //寻找根节点
	if (isBST(T, -INF, INF) && is_minHeap(T, T->k2))
		printf("YES\n");
	else
	{
		printf("NO\n");
	}
	return 0;
}