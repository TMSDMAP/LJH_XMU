/*题目简介
是否完全二叉搜索树
分数 25
作者 陈越
单位 浙江大学
将一系列给定数字顺序插入一个初始为空的二叉搜索树（定义为左子树键值大，右子树键值小），你需要判断最后的树是否一棵完全二叉树，并且给出其层序遍历的结果。

输入格式：
输入第一行给出一个不超过20的正整数N；第二行给出N个互不相同的正整数，其间以空格分隔。

输出格式：
将输入的N个正整数顺序插入一个初始为空的二叉搜索树。在第一行中输出结果树的层序遍历结果，数字间以1个空格分隔，行的首尾不得有多余空格。第二行输出YES，如果该树是完全二叉树；否则输出NO。
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef struct TreeNode {
	int val;
	TreeNode* lchild;
	TreeNode* rchild;
}TreeNode,*Tree;  //创建树有关结构体
int N;            //输入元素个数N
int a[20];        //数组记录层序遍历元素顺序
int k = 0;		  //使用K实现元素读入a数组
void Insert(Tree &T, int x)   //实现元素依次与根结点比较并插入到新结点
{
	if (T == NULL) return;  //空树返回空
	if (x > T->val)                   // 大于根节点值时
		if ((T->lchild) == NULL) {          //如果此时左子树没被占用
			T->lchild = (Tree)malloc(sizeof(TreeNode));  
			T->lchild->lchild = T->lchild->rchild = NULL;  //开辟左子树空间并将其子树初始化为空
			(T->lchild)->val = x; }  //给左子树赋值
		else Insert(T->lchild, x);   //否则就再次与左子树比较,实现递归插入
	else
	{      //右子树同理
		if ((T->rchild) == NULL) {     
			T->rchild = (Tree)malloc(sizeof(TreeNode));
			T->rchild->lchild = T->rchild->rchild = NULL;
			(T->rchild)->val = x;
		}                    
		else Insert(T->rchild, x);         
	}
}
bool isCompleteTree(Tree T)   //通过层序遍历判断是否为完全二叉树并返回bool值
{
	if (T == NULL) return true;  //返回空子树
	queue<Tree> q;   //层序遍历使用队列作为存储结构
	q.push(T);   //根节点入队列
	bool k1 = true;   //初始化k1作为判断
	bool leaf = false;  //判断前面的结点是否出现出度小于2的情况
	while (!q.empty())    //队列元素循环
	{
		Tree cur = q.front();  //取头元素
		q.pop();  //泵出
		a[k++] = cur->val;  //进入a数组
		if (cur->lchild == NULL && cur->rchild != NULL)  //只要左子树为空且右子树不为空就返回false
		{
			k1 = false;  //这里使用k1来记录,而不是直接返回false是因为数组a要完全记录所有元素
		}
		if (leaf) {   //如果前面的结点出现特殊情况
			if (cur->lchild != NULL || cur->rchild != NULL) //后面结点都不可能再有子节点,否则返回false
				k1 = false;
		}
		if (cur->lchild != NULL && cur->rchild == NULL||cur->lchild==NULL&&cur->rchild==NULL)  //两种情况:左子树不空,右子树空和左右子树均为空
		{
			leaf = true;
		}
		if (cur->lchild != NULL) q.push(cur->lchild);  //左孩子进队列
		if (cur->rchild != NULL) q.push(cur->rchild);  //右孩子进队列
	}
	return k1;
}
int main()
{
	Tree T;
	T = (Tree)malloc(sizeof(TreeNode));  //创建并初始化根节点
	T->lchild = T->rchild = NULL;  
	cin >> N;
	int num[20];  //num数组存储输入元素
	for (int i = 0; i < N; i++)
		cin >> num[i];
	T->val = num[0];
	for (int i = 1; i < N; i++)  
	{
		Insert(T, num[i]);  //对每个元素依次插入
	}
	int l = isCompleteTree(T); //层序遍历(BFS)
	for (int i = 0; i <N-1; i++)
	{
		cout << a[i] << " "; //输出
	}
	cout << a[N - 1] << endl; 
	if (l)
		cout << "YES" << endl;  
	else
	{
		cout << "NO" << endl;
	}
}