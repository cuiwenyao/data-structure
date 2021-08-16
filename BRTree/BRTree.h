// 红黑树

#ifndef BRTREE_H
#define BRTREE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <deque>
#include <vector>
#include <iostream>

enum COLOR
{
    RED,
    BLACK
};

typedef struct BRTREE
{
    int key;
    struct BRTREE *parent;
    struct BRTREE *left;
    struct BRTREE *right;
    enum COLOR color;
} * BRTree, BRTree_Node;

BRTree init(BRTree tree);

BRTree create_node(int key, BRTree parent, BRTree left, BRTree right, enum COLOR color);

void preorder(BRTree tree);
void inorder(BRTree tree);
void postorder(BRTree tree);

BRTree search(BRTree tree, int key);

//将树层序遍历打印出来
void print_brtree(BRTree tree, int dir, int last_key);

BRTree insert(BRTree tree, int key);

BRTree fix_up(BRTree tree, BRTree tree_cur);

//左旋
BRTree l_rotation(BRTree tree, BRTree cur);
//右旋
BRTree r_rotation(BRTree tree, BRTree cur);

BRTree delete_brtree(BRTree tree, int key);

BRTree fix_up_del(BRTree tree, BRTree cur_tree);
BRTree delete_node(BRTree tree, BRTree del_tree);
BRTree successor(BRTree tree);
BRTree maximum(BRTree tree);
BRTree minimum(BRTree tree);
//从 leaf 到 root 的路径上的black结点数量。
int black_num(BRTree root, BRTree leaf);
void save_balck_num(BRTree root, BRTree leaf, std::vector<int> &balck);
bool check_balck_num_valid(BRTree tree);
void destroy(BRTree tree);

#endif