#include "linkstack.c"

void fun(Item item)
{
    printf("item: %d\n", item.value);
}
int main()
{
    LinkStack stack;
    InitStack(&stack);
    AutoFillStack(&stack);
    TraverseStack(&stack, (*fun));
    ClearStack(&stack);
    DestroyStack(&stack);
}