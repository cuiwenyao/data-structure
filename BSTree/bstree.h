//二叉查找树
// binary search tree

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct BSTree
{
    int key; //可以用Item代替，不过为了方便学习，就不这样了。
    struct BSTree *parent;
    struct BSTree *left;
    struct BSTree *right;
} * BSTree;

//初始化
bool InitBSTree(BSTree *tree);

//销毁
bool DestroyBSTree(BSTree *tree);

//空
bool EmptyBSTree(BSTree *tree);

//插入
bool InsertBSTree(BSTree *tree, int key);

//删除
bool DeleteBSTree(BSTree *tree, int key);

//打印二叉树 0代表根节点 1代表左边 -1代表右
void Print_BSTree(BSTree *tree, int direction);

// 前序遍历
void Preorder_BSTree(BSTree *tree);
// 中序遍历
void Inorder_BSTree(BSTree *tree);
// 后序遍历
void Postorder_BSTree(BSTree *tree);

// (递归实现)查找"二叉树x"中键值为key的节点
bool Search_BSTree(BSTree *tree, int key, BSTree *tree_save);
// (非递归实现)查找"二叉树x"中键值为key的节点
bool iterative_bstree_search(BSTree *tree, int key, BSTree *tree_save);

// 查找最小结点：返回tree为根结点的二叉树的最小结点。
bool Min_BSTree(BSTree *tree, BSTree *tree_save);
// 查找最大结点：返回tree为根结点的二叉树的最大结点。
bool Max_BSTree(BSTree *tree, BSTree *tree_save);

// 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
bool Sucessor_BSTree(BSTree *tree, BSTree *x, BSTree *sucessor);
// 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
bool Predecessor_BSTree(BSTree *tree, BSTree *x, BSTree *prede);

void AutoFillBSTree(BSTree *tree, int size);