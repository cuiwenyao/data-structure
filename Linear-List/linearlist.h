//线性表 重新实现
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct Item
{
    int value;
} Item;

typedef struct LinearList
{
    //存放元素
    Item *items;
    //当前长度
    int length;
    //当前分配的存储容量
    int listsize;
} * LinearList;

//初始化
bool InitLinearList(LinearList(*List), int initsize);

//销毁
bool DestroyLinearList(LinearList(*List));

//清空
bool ClearLinearList(LinearList(*List));

//判断是否为空
bool EmptyLinearList(LinearList(*List));

//full
bool FullLinearList(LinearList(*List));

//获得元素
bool GetItemLinearList(LinearList(*List), int location, Item *itemsave);

//定位第一个满足条件的元素
int LocateLinearList(LinearList(*List), bool (*fun)(Item item));

//插入
bool InsertLinearList(LinearList(*List), int location, Item *item);

//删除
bool DeleteLinearList(LinearList(*List), int location);

void TraverseLinearList(LinearList(*List), void (*fun)(Item item));

void AutoFillLinearList(LinearList(*List));
