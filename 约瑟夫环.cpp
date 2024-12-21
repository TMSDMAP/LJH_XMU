/*
1.1 约瑟夫环
分数 10
作者 李廷元
单位 中国民用航空飞行学院
N个人围成一圈顺序编号，从1号开始按1、2、3......顺序报数，报p者退出圈外，其余的人再从1、2、3开始报数，报p的人再退出圈外，以此类推。
请按退出顺序输出每个退出人的原序号。

输入格式:
输入只有一行，包括一个整数N(1<=N<=3000)及一个整数p(1<=p<=5000)。

输出格式:
按退出顺序输出每个退出人的原序号，数据间以一个空格分隔，但行尾无空格。
*/
//要自己写出来约瑟夫环
#include <iostream>
using namespace std;
struct List
{
	int data;
	struct List* next;
};
int N, p;
List* creat()
{
	List* p, * q, * head;
	q = p = (List*)malloc(sizeof(List));
	head = NULL;
	int i = 1;
	while (i <= N)
	{
		if (head == NULL)
			head = p;
		else q = p;
		p->data = i;
		p = (List*)malloc(sizeof(List));
		q->next = p;
		i++;
	}
	q->next = head;
	return q;
}   //创建循环链表
int main()
{

	cin >> N >> p;
	List* tail, * q;
	tail = creat();
	q = tail;   //指针始终比count慢一个身位
	int count = 1;
	while (N >= 1)  //这里会有N=1的情况！！！
	{
		//q = q->next;
		if (count == p)
		{
			count = 1;
			List* temp = q->next;
			q->next = q->next->next;
			N--;
			if (N == 0) cout << temp->data;
			else
				cout << temp->data << " ";
			free(temp);
		}   //这样直接判断，就算只有一个值也会count++，当然使用注释里的N==1判断也可以，但是要放在开头，不然会二次判断。
		else {
			count++;
			q = q->next;
		}
		/*if (N == 1)
		{
			cout << q->data;
			break;
		}*/
	}
}
