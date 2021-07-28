#include "bstree.c"

int main()
{
    BSTree tree;
    InitBSTree(&tree);
    //DestroyBSTree(&tree);
    AutoFillBSTree(&tree, 10);
    printf("\n前序遍历: ");
    Preorder_BSTree(&tree);
    printf("\n中序遍历: ");
    Inorder_BSTree(&tree);
    printf("\n后序遍历: ");
    Postorder_BSTree(&tree);
    printf("\n");
    Print_BSTree(&tree, 0);
}