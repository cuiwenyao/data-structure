#include "linklist.h"

//初始化
bool InitLinkList(LinkList(*list))
{
    (*list) = NULL;
    printf("初始化LinkList成功\n");
    return true;
}

//销毁
bool DestroyLinkList(LinkList(*list))
{
    LinkList p = (*list);
    while (p != NULL)
    {
        LinkList q = p->next;
        free(p);
        p = q;
    }
    (*list) = NULL;
    printf("销毁LinkList成功\n");
    return true;
}

//清空
bool ClearLinkList(LinkList(*list))
{
    DestroyLinkList(list);
}

//判断是否为空
bool EmptyLinkList(LinkList(*list))
{
    if ((*list) == NULL)
    {
        printf("链表空\n");
        return true;
    }
    else
    {
        printf("链表不空\n");
        return false;
    }
}

//full
bool FullLinkList(LinkList(*list))
{
    LinkList p = (LinkList)malloc(sizeof(Node));
    if (p == NULL)
    {
        printf("满了\n");
        return true;
    }
    else
    {
        printf("不满\n");
        return false;
    }
}

//获得元素
bool GetItemLinkList(LinkList(*list), int location, Item *itemsave)
{
    LinkList p = (*list);
    for (int i = 0; i <= location - 1; i++)
    {
        if (p == NULL)
        {
            printf("没有找到这个元素\n");
            itemsave = NULL;
        }
        else
        {
            p = p->next;
        }
    }
    //现在p指向location元素
    if (p == NULL)
    {
        printf("没有找到这个元素\n");
        //直接改变itemsave时改变形参，对外面的实参没有任何影响。
        //itemsave = NULL;
        return false;
    }
    else
    {
        //这里itemsave肯定要提前申请好内存
        //为了兼容性，直接改变itemsave的指向即可，不需要其事先拥有内存。
        //直接改变itemsave时改变形参，对外面的实参没有任何影响。  只有 *itemsave=    才会有作用。
        //假如要不申请内存 直接改变传入的实参的指针指向的话需要使用二重指针。不过这样有点麻烦了。不如申请内存了事
        *itemsave = p->item;
        printf("找到了，第%d元素的值为%d\n", location, p->item.value);
        return true;
    }
}

//定位第一个满足条件的元素
int LocateLinkList(LinkList(*list), bool (*fun)(Item item))
{
    LinkList p = (*list);
    int location = 0;
    while (p != NULL)
    {
        if (fun(p->item))
        {
            printf("第一个满足条件的元素为第%d\n", location);
            return location;
        }
        else
        {
            p = p->next;
        }
    }
    printf("没有满足条件的元素\n");
}

//获得元素个数
int CountLinkList(LinkList(*list))
{
    LinkList p = (*list);
    int count = 0;
    while (p != NULL)
    {
        p = p->next;
        count++;
    }
    return count;
}

//插入
bool InsertLinkList(LinkList(*list), int location, Item *item)
{
    if (FullLinkList(list))
    {
        printf("满了，无法插入\n");
        return false;
    }
    LinkList new = (LinkList)malloc(sizeof(Node));
    new->item = *item;
    new->next = NULL;
    LinkList p = (*list);
    //本为空
    if (EmptyLinkList(list))
    {
        (*list) = new;
        printf("插入成功\n");
        return true;
    }
    //头插 要移动头节点
    else if (location <= 0)
    {
        location = 0;
        //new->next=p;
        //p=new;
        new->next = (*list);
        (*list) = new;
        printf("插入成功\n");
        return true;
    }
    //尾插
    else if (location >= CountLinkList(list))
    {
        location = CountLinkList(list);
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = new;
        printf("插入成功\n");
        return true;
    }
    //中间插
    else
    {
        while (location != 1)
        {
            location--;
            p = p->next;
        }
        //插到p后面
        new->next = p->next;
        p->next = new;
        printf("插入成功\n");
        return true;
    }
    printf("插入失败\n");
    return false;
}

//删除
bool DeleteLinkList(LinkList(*list), int location)
{
    if (EmptyLinkList(list))
    {
        printf("空，无法删除\n");
        return false;
    }

    if (location < 0)
    {
        location = 0;
    }
    else if (location >= CountLinkList(list) - 1)
    {
        location = CountLinkList(list) - 1;
    }

    //删除第零个元素
    if (location == 0)
    {
        location = 0;
        LinkList p = (*list);
        (*list) = (*list)->next;
        free(p);
        printf("删除成功\n");
        return true;
    }
    else if (location <= CountLinkList(list) - 1)
    {
        LinkList p = (*list);
        while (location != 1)
        {
            location--;
            p = p->next;
        }
        //删除p->next
        LinkList del = p->next;
        p->next = p->next->next;
        free(del);
        printf("删除成功\n");
        return true;
    }
}

void TraverseLinkList(LinkList(*list), void (*fun)(Item item))
{
    LinkList p = (*list);
    while (p != NULL)
    {
        fun(p->item);
        p = p->next;
    }
}

void AutoFillLinkList(LinkList(*list))
{
    for (int i = 0; i <= AUTOFILLSIZE; i++)
    {
        Item item;
        item.value = i;
        InsertLinkList(list, i, &item);
    }
}

//反转链表
LinkList ReverseLinkList(LinkList(*list))
{
    printf("反转链表\n");
    if((*list)->next!=NULL)
    {
        ReverseLinkList(&((*list)->next));
    }
    //LinkList p=*list;
    if(*list==NULL)
    {
        //空，不用反转
        printf("空，不用反转\n");
        return NULL;
    }
    else if((*list)->next==NULL)
    {
        //只有一个元素，也不用反转
        printf("只有一个元素，也不用反转\n");
        return *list;
    }
    else if((*list)->next->next==NULL)
    {
        //两个元素 进行反转
        //*list=p->next;
        printf("反转 %d %d \n",(*list)->item.value,(*list)->next->item.value);
        (*list)->next->next=(*list);
        (*list)->next=NULL;
    }
}