/*
8.3 是否同一棵二叉搜索树
分数 28
作者 陈越
单位 浙江大学
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。随后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。
*/
//做法一是将每个序列都创建树，遍历输出结果相同就认为是一样的
//做法二是根据给定序列创建一棵树，然后去遍历每个元素，遍历路径应该是一样的，如果不一样，
#include <iostream>
#include <algorithm>
using namespace std;
int N;
typedef struct TreeNode
{
	int data;
	bool flag;
	TreeNode* lchild, * rchild;
}TreeNode, * Tree;
Tree Insert(Tree T, int e)
{
	if (T == NULL)
	{
		T = (Tree)malloc(sizeof(TreeNode));
		T->data = e;
		T->flag = false;
		T->lchild = T->rchild = NULL;
		return T;
	}
	else
		if (T->data > e)
		{
			T->lchild = Insert(T->lchild, e);
		}
		else
		{
			T->rchild = Insert(T->rchild, e);
		}
	return T;
} //注意初始化问题
bool check(Tree T, int e)
{
	if (T->flag)
	{
		if (e < T->data) return check(T->lchild, e);
		else if (e > T->data) return check(T->rchild, e);
		else return false;
	}
	else
	{
		if (e == T->data)
		{
			T->flag = true;
			return true;
		}
		else return false;
	}
}   //给出的序列都是true，如果出现false，要么是陌生节点，要么是要访问的节点
Tree creat()
{
	Tree T;
	int e;
	cin >> e;
	T = (Tree)malloc(sizeof(TreeNode));
	T->data = e;
	T->flag = false;
	T->lchild = T->rchild = NULL;
	for (int i = 1; i < N; i++)
	{
		cin >> e;
		T = Insert(T, e);
	}return T;
}    //使用循环创建树，插入数据，对第一个节点要初始化，不然会报错
void reset(Tree T)
{
	if (T->lchild)
		reset(T->lchild);
	if (T->rchild)
		reset(T->rchild);
	T->flag = false;
}
void freeTree(Tree T)
{
	if (T->lchild)
		freeTree(T->lchild);
	if (T->rchild)
		freeTree(T->rchild);
	free(T);
}
int main()
{

	while (1)
	{
		cin >> N;
		//cout << N << endl;
		if (N == 0) break;
		int L;
		cin >> L;
		Tree T;
		T = creat();
		for (int i = 0; i < L; i++)
		{
			int flag = 0;
			int e;
			cin >> e;
			if (e == T->data) T->flag = true;
			else flag = 1;   //flag=1表示有错误，因为第一个节点必须是根节点
			for (int j = 1; j < N; j++)
			{
				cin >> e;
				if (!check(T, e) && !flag)
				{
					flag = 1;
					//cout << "No" << endl;
					//break;
				}
			}
			if (flag == 0) cout << "Yes" << endl;
			else cout << "No" << endl;
			reset(T);  //记得每趟序列重置flag
		}
		freeTree(T);
	}
	return 0;
}