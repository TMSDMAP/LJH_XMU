/*
1.2 链表去重
分数 10
作者 陈越
单位 浙江大学
给定一个带整数键值的链表 L，你需要把其中绝对值重复的键值结点删掉。即对每个键值 K，只有第一个绝对值等于 K 的结点被保留。同时，所有被删除的结点须被保存在另一个链表上。例如给定 L 为 21→-15→-15→-7→15，你需要输出去重后的链表 21→-15→-7，还有被删除的链表 -15→15。

输入格式：
输入在第一行给出 L 的第一个结点的地址和一个正整数 N（≤10
5
 ，为结点总数）。一个结点的地址是非负的 5 位整数，空地址 NULL 用 -1 来表示。

随后 N 行，每行按以下格式描述一个结点：

地址 键值 下一个结点
其中地址是该结点的地址，键值是绝对值不超过10
4
 的整数，下一个结点是下个结点的地址。

输出格式：
首先输出去重后的链表，然后输出被删除的链表。每个结点占一行，按输入的格式输出。
*/

//直接用数组存就行
#include <iostream>
using namespace std;
struct List {
	int key;
	int next;
}arr[100100];
int b[100100]; //保存重复节点地址
int main()
{
	int flag[100100] = { 0 };
	int first, n;
	cin >> first >> n;
	for (int i = 0; i < n; i++)
	{
		int add;
		cin >> add;
		cin >> arr[add].key >> arr[add].next;
	}
	int m = first;
	int value = abs(arr[m].key);
	printf("%05d %d ",m,arr[m].key);
	flag[value] = 1;
	int count = 0;
	while (1)
	{
		m = arr[m].next;
		if (m == -1)
		{
			cout << "-1" << endl;
			break;
		}
		value = abs(arr[m].key);    //实时输出，不需要双链表/数组，只需要判断是否重复，重复就不输出！
		if (flag[value] == 0)
		{
			printf("%05d\n%05d %d ",m,m,arr[m].key);//下一个地址可能会变，所以输出当前的地址，分开输出三个数据，而不是一下全部输出
			flag[value] = 1;
		}
		else
		{
			b[count] = m;
			count++;
		}
	}
	if (count)
	{
		for (int i = 0; i < count - 1; i++)
		{
			printf("%05d %d %05d\n",b[i],arr[b[i]].key,b[i+1]);
		}
		printf("%05d %d -1\n", b[count - 1], arr[b[count - 1]].key);
	}
}


/*#include <iostream>
#include <cmath>
#include <string>
using namespace std;
struct List
{
	int m;
	string address;
	string nexta;
	struct List* next;
};
List L[100000];
int main()
{
	int  N;
	string address1;
	List* head=NULL;
	cin >> address1 >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> L[i].address >> L[i].m >> L[i].nexta;
		//cout << L[i].address << L[i].m << L[i].nexta << endl;
	}
	for(int i = 0;i<N;i++)
		for (int j = 0; j < N; j++)
		{
			if (L[i].address == address1)
				head = &L[i];
			if (L[i].nexta == L[j].address)
				L[i].next = &L[j];
			if (L[j].nexta == "-1")
				L[j].next = NULL;
		}
	List* head2 = NULL;
	head2 = new List;
	head2->m = -1;
	head2->next = NULL;
	List* p1, * p2,*p3;
	p1 = head;
	p3 = head2;
	while (p1->next!= NULL)
	{
		p2 = p1;
		while (p2!=NULL&&p2->next!= NULL)
		{
			if (abs(p1->m) == abs(p2->next->m))
			{
				p3->next = p2->next;
				p2->nexta = p2->next->nexta;
				p2->next = p2->next->next;
				p3 = p3->next;
				p3->next = NULL;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	List* p = head;
	while (p != NULL)
	{
		cout << p->address<< " " << p->m<< " " << p->nexta << endl;
		p = p->next;
	}
	List* p4 = head2->next;
	while (p4 != NULL)
	{
		if (p4->next == NULL) p4->nexta = "-1";
		else
		p4->nexta = p4->next->address;
		//cout << p4->address << p4->m << p4->nexta << endl;
		p4 = p4->next;
	}
	p4 = head2->next;
	while (p4 != NULL)
	{
		cout << p4->address<<" " << p4->m << " " << p4->nexta << endl;
		p4 = p4->next;
	}
}     //错误思路，耗时且费力，会超时
*/