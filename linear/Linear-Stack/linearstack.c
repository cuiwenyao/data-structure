#include "linearstack.h"

bool InitStack(LinearStack *stack, int initsize)
{
    (*stack) = (struct LinearStack *)malloc(sizeof(struct LinearStack));
    InitLinearList(&((*stack)->block), initsize);
    (*stack)->base = (Item *)malloc(sizeof(Item));
    (*stack)->top = (Item *)malloc(sizeof(Item));
    //由于这了的base和top只是item*类型的，所以指向特定的item有点累赘，不如直接存储特定的元素值，除非改变其类型为指向一个结点的指针，这样只更更改其指向会更加由必要。
    (*stack)->length = 0;
    (*stack)->stacksize = initsize;
    printf("初始化成功\n");
    return true;
}

bool DestroyStack(LinearStack *stack)
{
    DestroyLinearList(&((*stack)->block));
    free((*stack)->base);
    free((*stack)->top);
    (*stack)->base = NULL;
    (*stack)->top = NULL;
    (*stack)->block = NULL;
    free(stack);
    *stack = NULL;
    if (*stack == NULL)
    {
        printf("销毁成功\n");
    }
    else
    {
        printf("销毁失败\n");
    }
}

bool ClearStack(LinearStack *stack)
{
    free((*stack)->base);
    free((*stack)->top);
    (*stack)->base = (Item *)malloc(sizeof(Item));
    (*stack)->top = (Item *)malloc(sizeof(Item));
    (*stack)->length = 0;
    ClearLinearList(&((*stack)->block));
    printf("清空栈成功\n");
    return true;
}

bool EmptyStack(LinearStack *stack)
{
    if ((*stack)->length == 0)
    {
        printf("栈空\n");
        return true;
    }
    else
    {
        printf("栈不空\n");
        return false;
    }
}

bool GetTopStack(LinearStack *stack, Item *itemsave)
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

bool PushStack(LinearStack *stack, Item *item)
{
    printf("当前容量为：%d, 可用容量为：%d\n", (*stack)->stacksize, (*stack)->stacksize - (*stack)->length);
    InsertLinearList(&((*stack)->block), (*stack)->length, item);
    (*stack)->length++;
    (*stack)->stacksize = (*stack)->block->listsize;
    if ((*stack)->length == 1)
    {
        //base只是指针不需要分配内存，也没有内存，所以只能通过改变指向的方式改变base,top也一样。
        *((*stack)->base) = ((*stack)->block->items[0]);
    }
    *((*stack)->top) = ((*stack)->block->items[(*stack)->length - 1]);
    return true;
}

bool PopStack(LinearStack *stack)
{
    if ((*stack)->length == 0)
    {
        printf("已经空了，不能pop\n");
        return false;
    }
    //删除最后一个元素。
    DeleteLinearList(&((*stack)->block), (*stack)->length - 1);
    (*stack)->length--;
    //更改 top
    *((*stack)->top) = (*stack)->block->items[(*stack)->length - 1];

    return true;
}

void AutoFillStack(LinearStack *stack)
{
    for (int i = 1; i <= 10; i++)
    {
        Item item;
        item.value = i;
        PushStack(stack, &item);
    }
}

void TraverseStack(LinearStack *stack, void (*fun)(Item item))
{
    Item item;
    while (!EmptyStack(stack))
    {
        GetTopStack(stack, &item);
        PopStack(stack);
        fun(item);
    }
}
