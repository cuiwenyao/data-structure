#include "linearstack.c"

void fun2(Item item)
{
    printf("item: %d\n", item.value);
}
int main()
{
    LinearStack stack;
    InitStack(&stack, 5);
    AutoFillStack(&stack);
    TraverseStack(&stack, (*fun2));
    ClearStack(&stack);
    DestroyStack(&stack);
}