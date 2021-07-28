#include "linearlist.h"

bool InitLinearList(LinearList(*List), int initsize)
{
    //根据下面的论断更正后 List 是指向 LinearList 的指针。
    //malloc (*List)    因为这里重新给 (*List) 分配内存了，所以 现在的List 不指向传进来的参数的List的指向，所以相当于这一切的初始化白做了。
    //这就是为什么书上的函数都是直接取变量的地址了，这样在函数中再反取地址就可以直接更改源数据了。
    //也可以在函数中自己重新定义一个一样的数据，完成之后赋值给传进来的参数，但是这样在有些情况写太费了，不好。
    (*List) = (struct LinearList *)malloc(sizeof(struct LinearList));
    //malloc items
    (*List)->items = (Item *)malloc(initsize * sizeof(Item));
    if (!(*List)->items)
    {
        printf("你要的空间太大了，分配不了\n");
        return false;
    }
    else
    {
        (*List)->length = 0;
        (*List)->listsize = initsize;
        printf("初始化成功,容量为%d\n", (*List)->listsize);
        return true;
    }
}

//销毁
bool DestroyLinearList(LinearList(*List))
{
    free((*List)->items);
    (*List)->items = NULL;
    free((*List));
    (*List) = NULL;
    if ((*List) == NULL)
    {
        printf("销毁成功\n");
        return true;
    }
    else
    {
        printf("销毁失败\n");
        return false;
    }
}

//清空
bool ClearLinearList(LinearList(*List))
{
    (*List)->length = 0;
    printf("清空成功\n");
    return true;
}

//判断是否为空
bool EmptyLinearList(LinearList(*List))
{
    if ((*List)->length == 0)
    {
        printf("空\n");
        return true;
    }
    else
    {
        printf("不空\n");
        return false;
    }
}

bool FullLinearList(LinearList(*List))
{
    if ((*List)->length == (*List)->listsize)
    {
        printf("满了\n");
        return true;
    }
    else
    {
        printf("没有满\n");
        return false;
    }
}
//获得元素
bool GetItemLinearList(LinearList(*List), int location, Item *itemsave)
{
    if (location < 0 || location >= (*List)->length)
    {
        printf("范围超限\n");
        return false;
    }
    else
    {
        *itemsave = (*List)->items[location];
    }
}

//定位第一个满足条件的元素
int LocateLinearList(LinearList(*List), bool (*fun)(Item item))
{
    for (int i = 0; i <= (*List)->length; i++)
    {
        if (fun((*List)->items[i]))
        {
            printf("第一个满足条件的元素在%d\n", i);
            return i;
        }
    }
    printf("没有元素满足条件\n");
    return -1;
}

//插入  这个函数有问题 内存
bool InsertLinearList(LinearList(*List), int location, Item *item)
{
    printf("InsertLinearList\n");
    if (FullLinearList(List))
    {
        //自动申请扩容
        printf("满了，自动申请扩容.\n");

        if (List == NULL)
        {
            printf("List is NULL\n");
        }
        if (*List == NULL)
        {
            printf("*List is NULL\n");
        }
        if ((*List)->items == NULL)
        {
            printf("(*List)->items is NULL\n");
        }

        (*List)->items = (Item *)realloc((*List)->items, ((*List)->listsize + 1) * sizeof(Item));
        if ((*List)->items)
        {
            (*List)->listsize++;
            printf("自动申请扩容, 成功,当前容量为%d\n", (*List)->listsize);
        }
        else
        {
            printf("自动申请扩容, 失败，插入失败\n");
            (*List)->items = NULL;
            return false;
        }
    }
    (*List)->length++;
    if (location < 0)
    {
        location = 0;
    }
    else if (location >= (*List)->length)
    {
        location = (*List)->length - 1;
    }
    for (int i = (*List)->length - 1; i >= location + 1; i--)
    {
        (*List)->items[i] = (*List)->items[i - 1];
    }
    (*List)->items[location] = *item;
    printf("插入成功,当前容量为%d,可用容量为%d\n", (*List)->listsize, (*List)->listsize - (*List)->length);
    return true;
}

//删除
bool DeleteLinearList(LinearList(*List), int location)
{
    if (location < 0 || location >= (*List)->length)
    {
        printf("删除的范围错误\n");
        return false;
    }
    else
    {
        for (int i = location; i <= (*List)->length - 2; i++)
        {
            (*List)->items[i] = (*List)->items[i + 1];
        }
        (*List)->length--;
    }
    printf("删除成功\n");
    return true;
}

void TraverseLinearList(LinearList(*List), void (*fun)(Item item))
{
    for (int i = 0; i <= (*List)->length - 1; i++)
    {
        fun((*List)->items[i]);
    }
}

void AutoFillLinearList(LinearList(*List))
{
    int listsize = (*List)->listsize;
    for (int i = 1; i <= listsize * 2; i++)
    {
        srand((double)time(NULL) * i);
        Item item;
        item.value = rand() % ((*List)->listsize);
        item.value = i;
        InsertLinearList(List, i, &item);
    }
}

bool KuoRong(LinearList *List)
{
    if (FullLinearList(List))
    {
        (*List)->items = (Item *)realloc((*List)->items, (*List)->listsize + 1);
        if ((*List)->items)
        {
            (*List)->listsize++;
            printf("自动申请扩容, 成功,当前容量为%d\n", (*List)->listsize);
        }
        else
        {
            printf("自动申请扩容, 失败，插入失败\n");
            return false;
        }
    }
    (*List)->length++;
    return true;
}