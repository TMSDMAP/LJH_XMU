#include <iostream>
#include <cstring>
using namespace std;
typedef struct TreeNode
{
    char data;
    TreeNode* lchild;
    TreeNode* rchild;
} TreeNode,*Tree;
TreeNode* CreateTree(string& pre,int& index)
{
    if(index>pre.size())
    {
        return nullptr;
    }
    if(pre[index]=='#')
    {
        index++;
        return nullptr;
    }
    TreeNode* root=new TreeNode;
    root->data=pre[index];
    index++;
    root->lchild=CreateTree(pre,index);
    root->rchild=CreateTree(pre,index);
    return root;
}
void Inorder(TreeNode* root)
{
    if(!root)
        return;
    Inorder(root->lchild);
    cout<<root->data;
    Inorder(root->rchild);
}
void SwapInorder(Tree root)
{
    if(root==nullptr)
    return;
    Tree temp = root->lchild;
    root->lchild = root->rchild;
    root->rchild = temp;
    SwapInorder(root->lchild);
    SwapInorder(root->rchild);
}
int main()
{
    string pre;
    Tree root;
    cin>>pre;
    cout<<pre<<endl;
    int index = 0;
    root = CreateTree(pre,index);
    Inorder(root);
    cout<<endl;
    SwapInorder(root);
    Inorder(root);
}