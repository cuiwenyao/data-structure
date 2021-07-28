#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX(a,b) (a>b)?a:b

//AVL TREE
//AVL 树中的任意两个节点的两个子树的高度差最大为1

typedef struct AVLTREE
{
    int Key;
    //树的高度，即一颗树的最大层次。 par.height=max(left.height,right.height),若一个节点的左右高度差达到了-2或者2，则这棵树不平衡。
    int Heigth;
    struct AVLTREE *Left;
    struct AVLTREE *Right;
    struct AVLTREE *Parent;
} * AVLTree, *Node;

typedef enum
{
    LL,
    LR,
    RL,
    RR,
    BALANCED    //已平衡
}UNBALANCED_STATUS;


//初始化一个空树
AVLTree AVLTree_Init();

//根据 key 生成一个树结点
AVLTree AVLTree_Create(int key);

//判断一棵树不平衡的状态
UNBALANCED_STATUS AVLTree_judge_unbalance_status(AVLTree unbalanced_tree);

//判断是否是祖宗 自己也是自己的祖宗。
bool isancestor(AVLTree ancestor,AVLTree son);
//使树平衡。
AVLTree AVLTree_make_it_balance(AVLTree tree);

// 获取AVL树的高度
int avltree_height(AVLTree tree);

// 前序遍历"AVL树"
void preorder_avltree(AVLTree tree);
// 中序遍历"AVL树"
void inorder_avltree(AVLTree tree);
// 后序遍历"AVL树"
void postorder_avltree(AVLTree tree);

//更新树的高度
int update_avltree_heigth(AVLTree tree);
//寻找不平衡的结点
AVLTree search_unbalanced_tree(AVLTree tree);
//balance
AVLTree balance(AVLTree tree);
//height
int height_avltree(AVLTree tree);
void ll_rotation(AVLTree k2);
void rr_rotation(AVLTree k2);

void print_avltree(AVLTree tree, int key, int direction);

// (递归实现)查找"AVL树x"中键值为key的节点
AVLTree avltree_search(AVLTree tree, int key);
// (非递归实现)查找"AVL树x"中键值为key的节点
AVLTree iterative_avltree_search(AVLTree tree, int key);

// 查找最小结点：返回tree为根结点的AVL树的最小结点。
AVLTree avltree_minimum(AVLTree tree);
// 查找最大结点：返回tree为根结点的AVL树的最大结点。
AVLTree avltree_maximum(AVLTree tree);

// 将结点插入到AVL树中，返回根节点
AVLTree avltree_insert(AVLTree tree, int key);

// 删除结点(key是节点值)，返回根节点
AVLTree avltree_delete(AVLTree tree, int key);

// 销毁AVL树
void destroy_avltree(AVLTree tree);

#endif