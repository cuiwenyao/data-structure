#include "linearlist.c"

bool fun1(Item item)
{
    if (item.value >= 100)
        return true;
    return false;
}
void fun2(Item item)
{
    printf("item: %d\n", item.value);
}
int main()
{
    LinearList List = NULL;
    Item itemsave;
    InitLinearList(&List, 10);
    AutoFillLinearList(&List);
    GetItemLinearList(&List, 1, &itemsave);
    printf("item: %d\n", itemsave.value);
    TraverseLinearList(&List, (*fun2));
    DestroyLinearList(&List);
}