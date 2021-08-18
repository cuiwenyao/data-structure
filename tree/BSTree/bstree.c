#include "bstree.h"

//初始化
bool InitBSTree(BSTree *tree)
{
    (*tree) = NULL;
    printf("初始化成功\n");
}

//销毁
bool DestroyBSTree(BSTree *tree)
{
    if ((*tree) != NULL)
    {
        if ((*tree)->left == NULL && (*tree)->right == NULL)
        {
            free(tree);
            return true;
        }
        DestroyBSTree(&((*tree)->left));
        DestroyBSTree(&((*tree)->right));
        if ((*tree) == NULL)
        {
            printf("销毁成功\n");
            return true;
        }
        else
        {
            printf("销毁失败\n");
            return false;
        }
    }
    if ((*tree) == NULL)
    {
        printf("销毁成功\n");
        return true;
    }
}

//空
bool EmptyBSTree(BSTree *tree)
{
    if ((*tree) == NULL)
    {
        printf("空\n");
        return true;
    }
    else
    {
        printf("不空\n");
        return false;
    }
}

//插入
bool InsertBSTree(BSTree *tree, int key)
{
    BSTree new = (BSTree)malloc(sizeof(struct BSTree));
    new->key = key;
    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;
    //左低右高
    if (EmptyBSTree(tree))
    {
        (*tree) = new;
        printf("插入成功 %d\n", key);
        return true;
    }
    else
    {
        //寻找位置进行插入；
        BSTree p = (*tree);
        while (p != NULL)
        {
            //小 往左走
            if (new->key < p->key)
            {
                if (p->left == NULL)
                {
                    //左边为空，则插入到左边即可
                    p->left = new;
                    new->parent = p;
                    printf("插入成功 %d 到 %d 的左边\n", key, p->key);
                    return true;
                }
                else
                {
                    //左边不空，继续寻找
                    p = p->left;
                }
            }
            //大 往右走
            else if (new->key > p->key)
            {
                if (p->right == NULL)
                {
                    //右边为空，则插入到右边即可
                    p->right = new;
                    new->parent = p;
                    printf("插入成功 %d 到 %d 的右边\n", key, p->key);
                    return true;
                }
                else
                {
                    //右边不空，继续寻找
                    p = p->right;
                }
            }
            else if (new->key == p->key)
            {
                printf("不允许相等的元素存在,插入失败\n");
                return false;
            }
        }
    }
    printf("插入失败\n");
    return false;
}

//删除
bool DeleteBSTree(BSTree *tree, int key)
{
    //删除的是根节点 删除叶子节点 删除的结点没有左子树或者右子树
    //空
    if (EmptyBSTree(tree))
    {
        printf("删除失败\n");
        return false;
    }
    BSTree p = (*tree);
    //p指向树的每一个结点（其实就是相应内存区域），改变 p->key，就是改变这块内存上key的值。所以才可以实现使用p遍历并更改结点。
    //其实，p->key==(*p).key  对(*p).key很自然就修改了其值，这点很容易理解。
    //假设这棵树在一个树的左边  解决删除的是根节点的问题
    BSTree fakeroot = (BSTree)malloc(sizeof(struct BSTree));
    fakeroot->left = p;
    fakeroot->right = NULL;
    fakeroot->parent = NULL;
    p->parent = fakeroot;
    if (p->key == (*p).key)
        printf("true\n");
    while (p != NULL)
    {
        //printf("1111111111111111111111\n");
        if (p->key < key)
        {
            //向右走
            //printf("向右走\n");
            p = p->right;
        }
        else if (p->key > key)
        {
            p = p->left;
            //printf("向左走\n");
        }
        else if (p->key == key)
        {
            //找到了，进行删除 p
            printf("找到了，进行删除 p %d\n", p->key);
            BSTree l = p->left;
            BSTree r = p->right;
            //p为左子树
            if (p->parent->left == p)
            {
                //p没有左子树
                if ((l == NULL) && (r != NULL))
                {
                    p->parent->left = r;
                    r->parent = p->parent;
                    free(p);
                    p = NULL;
                    (*tree) = fakeroot->left;
                    printf("删除成功\n");
                    return true;
                }
                //p没有右子树
                else if ((r == NULL) && (l != NULL))
                {
                    p->parent->left = l;
                    l->parent = p->parent;
                    free(p);
                    p = NULL;
                    (*tree) = fakeroot->left;
                    printf("删除成功\n");
                    return true;
                }
                //p左右子树都有
                else if ((r != NULL) && (l != NULL))
                {
                    //p为左节点，应为右侧的高 继位
                    p->parent->left = r;
                    //将l插入到r的最左下
                    while (r->left != NULL)
                    {
                        r = r->left;
                    }
                    //找到了右子树的最左边，插入左子树
                    r->left = l;
                    l->parent = r;
                    free(p);
                    p = NULL;
                    (*tree) = fakeroot->left;
                    printf("删除成功\n");
                    return true;
                }
                //左右子树都没有
                else
                {
                    p->parent->left = NULL;
                    free(p);
                    p = NULL;
                    (*tree) = fakeroot->left;
                    printf("删除成功\n");
                    return true;
                }
            }
            //p为右子树
            else
            {
                //将 右子树顶替p的位置，然后将左子树插入到右子树的最左下面即可，因为右边比左边大。
                //p为右节点，应为左侧的低 继位
                //p没有左子树
                if ((l == NULL) && (r != NULL))
                {
                    p->parent->right = r;
                    r->parent = p->parent;
                    free(p);
                    p = NULL;
                    (*tree) = fakeroot->left;
                    printf("删除成功\n");
                    return true;
                }
                //p没有右子树
                else if ((r == NULL) && (l != NULL))
                {
                    p->parent->right = l;
                    l->parent = p->parent;
                    free(p);
                    p = NULL;
                    (*tree) = fakeroot->left;
                    printf("删除成功\n");
                    return true;
                }
                //p左右子树都有
                else if ((r != NULL) && (l != NULL))
                {
                    p->parent->right = l;
                    while (l->right != NULL)
                    {
                        l = l->right;
                    }
                    //找到了右子树的最左边，插入左子树
                    l->right = r;
                    r->parent = l;
                    free(p);
                    p = NULL;
                    (*tree) = fakeroot->left;
                    printf("删除成功\n");
                    return true;
                }
                //左右子树都没有
                else
                {
                    p->parent->right = NULL;
                    free(p);
                    p = NULL;
                    (*tree) = fakeroot->left;
                    printf("删除成功\n");
                    return true;
                }
            }
        }
    }
    printf("没有找到这个元素，删除失败\n");
    return true;
}

//打印二叉树 0代表根节点 -1代表左边 1代表右
void Print_BSTree(BSTree *tree, int direction)
{
    BSTree p = *tree;
    if (p != NULL)
    {
        //根节点
        if (direction == 0)
        {
            printf("结点 %2d 为根节点\n", p->key);
        }
        //左
        else if (direction == -1)
        {
            printf("结点 %2d 为结点 %2d 的left\n", p->key, p->parent->key);
        }
        else
        {
            printf("结点 %2d 为结点 %2d right\n", p->key, p->parent->key);
        }
        Print_BSTree(&(p->left), -1);
        Print_BSTree(&(p->right), 1);
    }
}

// 前序遍历
void Preorder_BSTree(BSTree *tree)
{
    BSTree p = (*tree);
    if (p == NULL)
    {
        return;
    }
    else
    {
        printf("%d ", p->key);
        Preorder_BSTree(&(p->left));
        Preorder_BSTree(&(p->right));
    }
}
// 中序遍历
void Inorder_BSTree(BSTree *tree)
{
    BSTree p = (*tree);
    if (p == NULL)
    {
        return;
    }
    else
    {
        Inorder_BSTree(&(p->left));
        printf("%d ", p->key);
        Inorder_BSTree(&(p->right));
    }
}
// 后序遍历
void Postorder_BSTree(BSTree *tree)
{
    BSTree p = (*tree);
    if (p == NULL)
    {
        return;
    }
    else
    {
        Postorder_BSTree(&(p->left));
        Postorder_BSTree(&(p->right));
        printf("%d ", p->key);
    }
}

// (递归实现)查找"二叉树x"中键值为key的节点
bool Search_BSTree(BSTree *tree, int key, BSTree *tree_save)
{
    BSTree p = (*tree);
    if (p == NULL)
    {
        //*tree_save = NULL;
        //printf("没找到\n");
        return false;
    }
    if (p->key == key)
    {
        //找到了
        *tree_save = p;
        printf("找到了\n");
        return true;
    }
    Search_BSTree(&(p->left), key, tree_save);
    Search_BSTree(&(p->right), key, tree_save);
}
// (非递归实现)查找"二叉树x"中键值为key的节点
bool iterative_bstree_search(BSTree *tree, int key, BSTree *tree_save)
{
    BSTree p = (*tree);
    while (p != NULL)
    {
        if (p->key == key)
        {
            //找到了
            (*tree_save) = p;
            printf("找到了\n");
            return true;
        }
        else if (p->key < key)
        {
            //往右走
            p = p->right;
        }
        else if (p->key > key)
        {
            p = p->left;
        }
    }
    //没找到
    (*tree_save) = NULL;
    printf("没找到\n");
    return false;
}

// 查找最小结点：返回tree为根结点的二叉树的最小结点。
bool Min_BSTree(BSTree *tree, BSTree *tree_save)
{
    BSTree p = (*tree);
    if (p == NULL)
    {
        *tree_save = NULL;
        return false;
    }
    while (p->left != NULL)
    {
        p = p->left;
    }
    *tree_save = p;
    return true;
}
// 查找最大结点：返回tree为根结点的二叉树的最大结点。
bool Max_BSTree(BSTree *tree, BSTree *tree_save)
{
    BSTree p = (*tree);
    if (p == NULL)
    {
        *tree_save = NULL;
        return false;
    }
    while (p->right != NULL)
    {
        p = p->right;
    }
    *tree_save = p;
    return true;
}

//前驱节点：对一棵二叉树进行中序遍历，遍历后的顺序，当前节点的前一个节点为该节点的前驱节点；

//后继节点：对一棵二叉树进行中序遍历，遍历后的顺序，当前节点的后一个节点为该节点的后继节点；

// 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
bool Sucessor_BSTree(BSTree *tree, BSTree *x, BSTree *sucessor)
{
    //即其右子树的最左边
    if ((*x) == NULL)
    {
        printf("空结点，没有后继\n");
        (*sucessor) = NULL;
        return false;
    }
    //有右子树
    else if ((*x)->right != NULL)
    {
        Min_BSTree(&((*x)->right), sucessor);
        printf("找到了后继，%d 的后继为 %d \n", (*x)->key, (*sucessor)->key);
        return true;
    }
    //没有右子树 则从此开始向上找一个是左结点的结点
    else if ((*x)->right == NULL)
    {
        BSTree p = *x;
        //从x往上查，直到有一个结点是左节点  则该左节点的父节点为所求
        while (p->parent != NULL)
        {
            if (p->parent->left == p)
            {
                *sucessor = p->parent;
                printf("找到了后继，%d 的后继为 %d \n", (*x)->key, (*sucessor)->key);
                return true;
            }
            else
            {
                p = p->parent;
            }
        }
        //p此时已经是root了，还没有找到说明那个结点没有后继。
        printf("结点 %d 没有后继\n", (*x)->key);
        (*sucessor) = NULL;
        return false;
    }
}
// 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
bool Predecessor_BSTree(BSTree *tree, BSTree *x, BSTree *prede)
{
    if (*x == NULL)
    {
        printf("空结点，没有前驱\n");
        *prede = NULL;
        return false;
    }
    //左子树 则寻找其左子树的最大值
    if ((*x)->left != NULL)
    {
        Max_BSTree(&((*x)->left), prede);
        printf("找到了前驱，%d 的前驱为 %d \n", (*x)->key, (*prede)->key);
        return true;
    }
    //没有左子树，则向上寻找一个是其父节点的右子树的结点。
    else if ((*x)->left == NULL)
    {
        BSTree p = *x;
        while (p->parent != NULL)
        {
            if (p->parent->right == p)
            {
                *prede = p->parent;
                printf("找到了前驱，%d 的前驱为 %d \n", (*x)->key, (*prede)->key);
                return true;
            }
            else
            {
                p = p->parent;
            }
        }
        //p此时已经是root了，还没有找到说明那个结点没有前驱。
        printf("结点 %d 没有前驱\n", (*x)->key);
        (*prede) = NULL;
        return false;
    }
}

void AutoFillBSTree(BSTree *tree, int size)
{
    InsertBSTree(tree, 5);
    InsertBSTree(tree, 4);
    InsertBSTree(tree, 6);
    InsertBSTree(tree, 2);
    InsertBSTree(tree, 3);
    InsertBSTree(tree, 1);
    InsertBSTree(tree, 8);
    InsertBSTree(tree, 7);
    InsertBSTree(tree, 9);

    for (int i = 1; i <= 10; i++)
    {
        BSTree sucessor = NULL;
        BSTree x = NULL;
        Search_BSTree(tree, i, &x);
        Sucessor_BSTree(tree, &x, &sucessor);
        if (sucessor != NULL)
            printf("succor: %d\n", sucessor->key);
    }
    for (int i = 1; i <= 10; i++)
    {
        BSTree prede = NULL;
        BSTree x = NULL;
        Search_BSTree(tree, i, &x);
        Predecessor_BSTree(tree, &x, &prede);
        if (prede != NULL)
            printf("succor: %d\n", prede->key);
    }
}