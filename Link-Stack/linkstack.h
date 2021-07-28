#include "../Link-List/linklist.c"

typedef struct LinkStack
{
    //存储数据的区域   这里的block就相当于LinkList 中的List
    LinkList block;
    Item *base;
    Item *top;
    //当前长度
    int length;
} * LinkStack;

bool InitStack(LinkStack *stack);

bool DestroyStack(LinkStack *stack);

bool ClearStack(LinkStack *stack);

bool EmptyStack(LinkStack *stack);

bool GetTopStack(LinkStack *stack, Item *itemsave);

bool PushStack(LinkStack *stack, Item *item);

bool PopStack(LinkStack *stack);

void AutoFillStack(LinkStack *stack);

void TraverseStack(LinkStack *stack, void (*fun)(Item item));
