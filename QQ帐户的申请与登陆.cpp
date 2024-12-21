/*
8.1 QQ帐户的申请与登陆
分数 15
作者 DS课程组
单位 浙江大学
实现QQ新帐户申请和老帐户登陆的简化版功能。最大挑战是：据说现在的QQ号码已经有10位数了。

输入格式:
输入首先给出一个正整数N（≤10
5
 ），随后给出N行指令。每行指令的格式为：“命令符（空格）QQ号码（空格）密码”。其中命令符为“N”（代表New）时表示要新申请一个QQ号，后面是新帐户的号码和密码；命令符为“L”（代表Login）时表示是老帐户登陆，后面是登陆信息。QQ号码为一个不超过10位、但大于1000（据说QQ老总的号码是1001）的整数。密码为不小于6位、不超过16位、且不包含空格的字符串。

输出格式:
针对每条指令，给出相应的信息：

1）若新申请帐户成功，则输出“New: OK”；

2）若新申请的号码已经存在，则输出“ERROR: Exist”；

3）若老帐户登陆成功，则输出“Login: OK”；

4）若老帐户QQ号码不存在，则输出“ERROR: Not Exist”；

5）若老帐户密码错误，则输出“ERROR: Wrong PW”。
*/

//由于题目没有给出具体的哈希函数，所以我们可以借助容器中的map（键值对）来实现哈希表的创建
#include <iostream>
#include <string>
#include <map>  //引入map容器库，用于存储用户名和密码的键值对
#include <utility>   //引入utility库，使用make_pair函数
using namespace std;
map<string, string> myMap;   //创建一个map哈希表
int main()
{
	int N;
	string s0("1000");   //初始化初始用户名s0
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		char c;
		string s1, s2;
		cin >> c;
		cin >> s1;
		cin >> s2;
		if (c == 'N')    //如果是新用户注册
		{
			if (s1 > s0 && s1.length() <= 10)  //用户名长度符合要求
			{
				map<string, string>::iterator it = myMap.find(s1);   //用迭代器查找是否已经存在
				if (it != myMap.end())   //如果用户名已经存在（此时不会指向myMap.end()）
					cout << "ERROR: Exist" << endl;
				else
				{
					if (s2.length() >= 6 && s2.length() <= 16 && s2.find(' ') == string::npos)  //判断密码是否符合要求，并且不含空格。npos 是 C++ 中 std::string 类的一个常量值，用来表示 "未找到" 或 "无效的位置"。
					{
						myMap.insert(make_pair(s1, s2));  //把用户名和密码用make_piar函数绑定后才能插入
						cout << "New: OK" << endl;
					}
				}
			}
		}
		else    //登录同理
		{
			map<string, string>::iterator it = myMap.find(s1);
			if (it != myMap.end())
			{
				if (s2 == myMap[s1])    //如果密码正确
					cout << "Login: OK" << endl;
				else cout << "ERROR: Wrong PW" << endl;
			}
			else cout << "ERROR: Not Exist" << endl;
		}
	}
	return 0;
}