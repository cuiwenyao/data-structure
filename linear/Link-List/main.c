#include "linklist.c"

void fun(Item item)
{
    //printf("item: %d\n", item.value);
    printf("%d ", item.value);
}

int main()
{
    LinkList list;
    Item itemsave; //= (Item *)malloc(sizeof(Item));
    InitLinkList(&list);
    AutoFillLinkList(&list);

    //由于是值传递，所以传入指针的值，在函数中进行更改不会改变实参的数据。
    //GetItemLinkList(&list, 2, &itemsave);
    //printf("item: %d\n", itemsave.value);

    TraverseLinkList(&list,(*fun));
    ReverseLinkList(&list);
    TraverseLinkList(&list,(*fun));
}