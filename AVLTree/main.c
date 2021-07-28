#include "avltree.c"


int main()
{
    AVLTree tree=AVLTree_Init();
    tree=avltree_insert(tree,10);
    tree=avltree_insert(tree,15);
    tree=avltree_insert(tree,8);
    tree=avltree_insert(tree,7);
    tree=avltree_insert(tree,9);
    //tree=avltree_delete(tree,15);
    inorder_avltree(tree);
    print_avltree(tree,tree->Key,0);
    tree=balance(tree);
    print_avltree(tree,tree->Key,0);

    printf("search %d \n",avltree_search(tree,10)?avltree_search(tree,10)->Key:-1);
    printf("search %d \n",iterative_avltree_search(tree,7)?iterative_avltree_search(tree,7)->Key:-1);
    printf("min: %d \n",avltree_minimum(tree)->Key);
    printf("min: %d \n",avltree_maximum(tree)->Key);
    destroy_avltree(tree);
    //printf("min: %d \n",avltree_maximum(tree)->Key);
}