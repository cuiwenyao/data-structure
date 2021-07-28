#ifndef _BSTREE_H
#define _BSTREE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define ungigned long long  int

#ifndef M 
#define M 8
#endif

static const int MAX_KEY_NUM=2*M;
static const int MAX_CHILD_NUM=2*M+1;

typedef struct BTREE
{
    int key_num;//键的数量
    int child_num;//孩子数量 孩子数量永远等于key的数量加一
    int key[2*M+1];//键  冗余一位，child同理
    struct BTREE * child[2*M+2];//最多拥有 2M+1个孩子
    struct BTREE * parent;//父节点
    bool isleaf;
    //BTree在实际运用中还需要存储值，但是这里就不用了。
}Node,*BTree;


//初始化一个空树
BTree BTree_Init();
// 前序遍历
void preorder(BTree tree);
// 中序遍历
void inorder(BTree tree);
// 后序遍历
void postorder(BTree tree);
//打印Btree
void print_btree(BTree tree, int key, int direction);
// (递归实现)查找"b树x"中键值为key的节点
BTree search(BTree tree, int key,int * index);
// (非递归实现)查找"b树x"中键值为key的节点
BTree search_iterative(BTree tree, int key,int * index);
// 查找最小结点
BTree minimum(BTree tree,int *index);
// 查找最大结点
BTree maximum(BTree tree,int *index);
// 将结点插入
BTree insert(BTree tree, int key);
//将一个值插入一个结点，返回更新过后的树
BTree insert_into_node(BTree tree, BTree node_to_insert, int key,bool is_key_to_up,int index,BTree tree_left,BTree tree_right);
// 删除结点
BTree delete_btree(BTree tree, int key);
//后继
BTree success_btree(BTree tree, int key, int *index_success);
//孩子
int childindex(BTree pa,BTree son);
// 销毁b树
void destroy(BTree tree);

#endif