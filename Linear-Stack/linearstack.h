#include "../Linear-List/linearlist.c"

//stack 可以直接使用 list 作为基础构建不同的stack  其实list就是所有线性数据结构的基础。
//我觉得之前的list的实现很不优雅，所以决定再重新实现一遍
//要学会抓住事情的主要矛盾，学习栈就是要学习其后进先出的思想，现在不要管其他杂乱的东西。

typedef struct LinearStack
{
    //存储数据的区域   这里的block就相当于linearlist 中的List
    struct LinearList *block;
    Item *base;
    Item *top;
    //当前长度
    int length;
    //当前分配的存储容量
    int stacksize;
} * LinearStack;

bool InitStack(LinearStack *stack, int initsize);

bool DestroyStack(LinearStack *stack);

bool ClearStack(LinearStack *stack);

bool EmptyStack(LinearStack *stack);

bool GetTopStack(LinearStack *stack, Item *itemsave);

bool PushStack(LinearStack *stack, Item *item);

bool PopStack(LinearStack *stack);

void AutoFillStack(LinearStack *stack);

void TraverseStack(LinearStack *stack, void (*fun)(Item item));
