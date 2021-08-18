//链表
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define AUTOFILLSIZE 10

typedef struct Item
{
    int value;
} Item;

typedef struct Node
{
    Item item;
    struct Node *next;
    //先实现单向链表
    //struct Node * prev;
} Node, *LinkList;

//初始化
bool InitLinkList(LinkList(*list));

//销毁
bool DestroyLinkList(LinkList(*list));

//清空
bool ClearLinkList(LinkList(*list));

//判断是否为空
bool EmptyLinkList(LinkList(*list));

//full
bool FullLinkList(LinkList(*list));

//获得元素
bool GetItemLinkList(LinkList(*list), int location, Item *itemsave);

//定位第一个满足条件的元素
int LocateLinkList(LinkList(*list), bool (*fun)(Item item));

//插入
bool InsertLinkList(LinkList(*list), int location, Item *item);

//删除
bool DeleteLinkList(LinkList(*list), int location);

void TraverseLinkList(LinkList(*list), void (*fun)(Item item));

void AutoFillLinkList(LinkList(*list));

//反转链表
LinkList ReverseLinkList(LinkList(*list));
