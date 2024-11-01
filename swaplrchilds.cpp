#include <iostream>
#include <cstring>
using namespace std;
typedef struct TreeNode
{
    char data;
    TreeNode* lchild;
    TreeNode* rchild;
} TreeNode,*Tree;     //创建二叉树结构体
TreeNode* CreateTree(string& pre,int& index)    //通过给定的先序(字符串)序列创建二叉树
{ 
    if(index>pre.size())      
    {
        return nullptr;       //如果index大于字符串长度，则返回空
    }
    if(pre[index]=='#')        //如果当前字符为'#',返回空,index++
    {
        index++;
        return nullptr;
    }
    TreeNode* root=new TreeNode;    //创建新结点并给节点赋值
    root->data=pre[index];          
    index++;                        
    root->lchild=CreateTree(pre,index);    //递归创建左子树
    root->rchild=CreateTree(pre,index);    //递归创建右子树
    return root;           //返回结点
}
void Inorder(TreeNode* root)        //中序遍历
{
    if(!root)        //根节点为空则返回
        return;
    Inorder(root->lchild);  //先左子树递归
    cout<<root->data;  //输出根节点
    Inorder(root->rchild);  //最后右子树递归
}
void SwapInorder(Tree root)      //递推交换左右子树
{
    if(root==nullptr)
    return;
    
    Tree temp = root->lchild;
    root->lchild = root->rchild;    //先交换左右子树,然后再递归
    root->rchild = temp;
    SwapInorder(root->lchild);
    SwapInorder(root->rchild);
}
/*
void SwapInorder(Tree root)      //递推交换左右子树
{
    if(root==nullptr)
    return;
    SwapInorder(root->lchild);
    Tree temp = root->lchild;
    root->lchild = root->rchild;    //中序实测可行
    root->rchild = temp;
    
    SwapInorder(root->lchild);
}*/
int main()
{
    string pre;
    Tree root;
    cin>>pre;
    int index = 0;
    root = CreateTree(pre,index);  //使用引用index的形式,不能使用数值传递,因为函数有两次递归
    Inorder(root);              //中序输出
    cout<<endl;
    SwapInorder(root);       //交换
    Inorder(root);             //中序输出
}