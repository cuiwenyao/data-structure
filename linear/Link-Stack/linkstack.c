#include "linkstack.h"

bool InitStack(LinkStack *stack)
{
    (*stack) = (LinkStack)malloc(sizeof(struct LinkStack));
    InitLinkList(&((*stack)->block));
    (*stack)->length = 0;
    (*stack)->base = (Item *)malloc(sizeof(Item));
    (*stack)->top = (Item *)malloc(sizeof(Item));
    printf("初始化LinkStack成功\n");
    return true;
}

bool DestroyStack(LinkStack *stack)
{
    DestroyLinkList(&((*stack)->block));
    free((*stack));
    (*stack) = NULL;
    printf("销毁LinkStack成功\n");
    return true;
}

bool ClearStack(LinkStack *stack)
{
    ClearLinkList(&((*stack)->block));
    (*stack)->length = 0;
    (*stack)->base = NULL;
    (*stack)->top = NULL;
    printf("清空LinkStack成功\n");
    return true;
}

bool EmptyStack(LinkStack *stack)
{
    if ((*stack)->length == 0)
    {
        printf("LinkStack空\n");
        return true;
    }
    else
    {
        printf("LinkStack不空\n");
        return false;
    }
}

bool GetTopStack(LinkStack *stack, Item *itemsave)
{
    if ((*stack)->length == 0)
    {
        printf("错误，栈中没有元素\n");
        return false;
    }
    else
    {
        *itemsave = *((*stack)->top);
        return true;
    }
}

bool PushStack(LinkStack *stack, Item *item)
{
    InsertLinkList(&((*stack)->block), (*stack)->length, item);
    (*stack)->length++;
    if ((*stack)->length == 1)
    {
        GetItemLinkList(&((*stack)->block), 0, (*stack)->base);
    }
    GetItemLinkList(&((*stack)->block), (*stack)->length - 1, (*stack)->top);
    return true;
}

bool PopStack(LinkStack *stack)
{
    if ((*stack)->length == 0)
    {
        printf("已经空了，不能pop\n");
        return false;
    }
    //删除top
    DeleteLinkList(&((*stack)->block), (*stack)->length - 1);
    (*stack)->length--;
    //更改top
    GetItemLinkList(&((*stack)->block), (*stack)->length - 1, (*stack)->top);
    return true;
}

void AutoFillStack(LinkStack *stack)
{
    for (int i = 0; i <= AUTOFILLSIZE; i++)
    {
        Item item;
        item.value = i;
        PushStack(stack, &item);
    }
}

void TraverseStack(LinkStack *stack, void (*fun)(Item item))
{
    printf("TraverseStack\n");
    Item item;
    while (!EmptyStack(stack))
    {
        GetTopStack(stack, &item);
        fun(item);
        PopStack(stack);
    }
}