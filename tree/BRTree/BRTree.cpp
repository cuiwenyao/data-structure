#include "BRTree.h"

BRTree init(BRTree tree)
{
    return NULL;
}

BRTree create_node(int key = -1, BRTree parent = NULL, BRTree left = NULL, BRTree right = NULL, enum COLOR color = RED)
{
    BRTree tree = (BRTree)malloc(sizeof(struct BRTREE));
    tree->color = color;
    tree->key = key;
    tree->left = left;
    tree->right = right;
    tree->parent = parent;
    return tree;
}

void preorder(BRTree tree)
{
    if (tree)
    {
        printf("%d ", tree->key);
        preorder(tree->left);
        preorder(tree->right);
    }
}
void inorder(BRTree tree)
{
    if (tree)
    {

        inorder(tree->left);
        //if (tree->left && tree->right && tree->left->color == RED && tree->right->color == RED && tree->color == RED)
        printf("%d, ", tree->key);
        inorder(tree->right);
    }
}
void postorder(BRTree tree)
{
    if (tree)
    {

        postorder(tree->left);
        postorder(tree->right);
        printf("%d ", tree->key);
    }
}

BRTree search(BRTree tree, int key)
{
    if (tree)
    {
        if (key == tree->key)
            return tree;
        if (key < tree->key)
            return search(tree->left, key);
        if (key > tree->key)
            return search(tree->right, key);
    }
    return tree;
}
//将树层序遍历打印出来
void print_brtree(BRTree tree, int dir, int last_key)
{
    if (!tree && dir == 0)
    {
        printf("树空\n");
    }
    if (tree)
    {
        //根节点
        if (dir == 0)
        {
            printf("%d root", tree->key);
            if (tree->color == RED)
                printf(" RED\n");
            else
                printf(" BLACK\n");
            print_brtree(tree->left, -1, tree->key);
            print_brtree(tree->right, 1, tree->key);
        }
        //左孩子
        if (dir == -1)
        {
            printf("%d is %d 's left", tree->key, last_key);
            if (tree->color == RED)
                printf(" RED\n");
            else
                printf(" BLACK\n");
            print_brtree(tree->left, -1, tree->key);
            print_brtree(tree->right, 1, tree->key);
        }
        //右孩子
        if (dir == 1)
        {
            printf("%d is %d 's right", tree->key, last_key);
            if (tree->color == RED)
                printf(" RED\n");
            else
                printf(" BLACK\n");
            print_brtree(tree->left, -1, tree->key);
            print_brtree(tree->right, 1, tree->key);
        }
    }
}

BRTree insert(BRTree tree, int key)
{
    //首先生成一个结点，染成红色并按照 BStree一样插入进去。
    BRTree pos = tree;
    BRTree tree_to_insert = create_node(key);
    //查找插入位置
    //空树
    if (tree == NULL)
    {
        //根节点的颜色为黑色
        tree_to_insert->color = BLACK;
        return tree_to_insert;
    }
    //非空树
    pos = tree;
    while (pos)
    {
        if (key == pos->key)
        {
            return tree;
        }
        //左
        if (key < pos->key)
        {
            if (pos->left == NULL)
            {
                pos->left = tree_to_insert;
                tree_to_insert->parent = pos;
                break;
            }
            else
                pos = pos->left;
        }
        //右
        if (key > pos->key)
        {
            if (pos->right == NULL)
            {
                pos->right = tree_to_insert;
                tree_to_insert->parent = pos;
                break;
            }
            else
                pos = pos->right;
        }
    }
    //插入成功，进行调整到合格的红黑树。
    return fix_up(tree, tree_to_insert);
}

BRTree fix_up(BRTree tree, BRTree tree_cur)
{
    //调整树直到符合红黑树的要求。
    if (!tree || !tree_cur)
        return tree;
    //cur为根节点将其颜色变为黑色直接返回
    if (tree_cur->parent == NULL)
    {
        tree_cur->color = BLACK;
        return tree;
    }
    //父节点是根节点则直接返回
    if (tree_cur->parent->parent == NULL)
        return tree;
    //1. 父节点是黑色 直接返回。
    if (tree_cur->parent->color == BLACK)
        return tree;
    //2. 父节点是红色
    if (tree_cur->parent->color == RED)
    {
        BRTree grandpa = tree_cur->parent->parent;

        //叔叔结点存在才可能是红色，否则为黑色
        if (grandpa->left && grandpa->right)
        {
            //1. 父节点和叔叔结点都是红色
            if (grandpa->left->color == RED && grandpa->right->color == RED)
            {
                //将父节点 叔叔 设为黑色 将祖父节点设为红色，递归继续处理祖父结点
                grandpa->left->color = BLACK;
                grandpa->right->color = BLACK;
                grandpa->color = RED;
                return fix_up(tree, grandpa);
            }
            //2. 父节点红 和叔叔结点黑
            else if (grandpa->left->color == BLACK || grandpa->right->color == BLACK)
            {
                // 当前结点的父节点是祖父节点的左孩子
                if (tree_cur->parent->parent->left == tree_cur->parent)
                {
                    // 当前结点是父节点的左孩子
                    if (tree_cur->parent->left == tree_cur)
                    {
                        // 父节点设为黑色 祖父节点设为红色 对祖父节点进行右旋
                        tree_cur->parent->color = BLACK;
                        tree_cur->parent->parent->color = RED;
                        tree = r_rotation(tree, tree_cur->parent->parent);
                        return tree;
                    }
                    // 当前结点是父节点的右孩子
                    if (tree_cur->parent->right == tree_cur)
                    {
                        // 将父节点设为当前节点并进行左旋。递归进行。
                        tree_cur = tree_cur->parent;
                        tree = l_rotation(tree, tree_cur);
                        return fix_up(tree, tree_cur);
                    }
                }
                // 当前结点的父节点是祖父节点的右孩子
                else if (tree_cur->parent->parent->right == tree_cur->parent)
                {
                    // 当前结点是父节点的左孩子
                    if (tree_cur->parent->left == tree_cur)
                    {
                        // 将父节点设为当前结点并进行右旋 递归
                        tree_cur = tree_cur->parent;
                        tree = r_rotation(tree, tree_cur);
                        return fix_up(tree, tree_cur);
                    }
                    // 当前结点是父节点的右孩子
                    if (tree_cur->parent->right == tree_cur)
                    {
                        // 父节点设为黑色 祖父设为红色 并对祖父进行左旋
                        tree_cur->parent->color = BLACK;
                        tree_cur->parent->parent->color = RED;
                        tree = l_rotation(tree, tree_cur->parent->parent);
                        return tree;
                    }
                }
            }
        }
        //叔叔结点不存在 为黑色
        else
        {
            // 当前结点的父节点是祖父节点的左孩子
            if (tree_cur->parent->parent->left == tree_cur->parent)
            {
                // 当前结点是父节点的左孩子
                if (tree_cur->parent->left == tree_cur)
                {
                    // 父节点设为黑色 祖父节点设为红色 对祖父节点进行右旋
                    tree_cur->parent->color = BLACK;
                    tree_cur->parent->parent->color = RED;
                    tree = r_rotation(tree, tree_cur->parent->parent);
                    return tree;
                }
                // 当前结点是父节点的右孩子
                if (tree_cur->parent->right == tree_cur)
                {
                    // 将父节点设为当前节点并进行左旋。递归进行。
                    tree_cur = tree_cur->parent;
                    tree = l_rotation(tree, tree_cur);
                    return fix_up(tree, tree_cur);
                }
            }
            // 当前结点的父节点是祖父节点的右孩子
            else if (tree_cur->parent->parent->right == tree_cur->parent)
            {
                // 当前结点是父节点的左孩子
                if (tree_cur->parent->left == tree_cur)
                {
                    // 将父节点设为当前结点并进行右旋 递归
                    tree_cur = tree_cur->parent;
                    tree = r_rotation(tree, tree_cur);
                    return fix_up(tree, tree_cur);
                }
                // 当前结点是父节点的右孩子
                if (tree_cur->parent->right == tree_cur)
                {
                    // 父节点设为黑色 祖父设为红色 并对祖父进行左旋
                    tree_cur->parent->color = BLACK;
                    tree_cur->parent->parent->color = RED;
                    tree = l_rotation(tree, tree_cur->parent->parent);
                    return tree;
                }
            }
        }
    }
    return tree;
}
//左旋
BRTree l_rotation(BRTree tree, BRTree cur)
{
    if (!tree || !cur)
        return tree;
    //设置傀儡头节点使根节点是其左孩子
    BRTree preroot = create_node(-1, NULL, tree);
    tree->parent = preroot;
    //左旋 将当前结点旋转为其右孩子的左孩子，并将其右孩子的左孩子设置为当前节点的右孩子。
    BRTree root = cur;
    BRTree right = root->right;
    if (!right)
        return tree;
    if (root->parent->left == root)
        root->parent->left = right;
    else if (root->parent->right == root)
        root->parent->right = right;
    right->parent = root->parent;

    root->parent = right;
    root->right = right->left;
    if (right->left)
        right->left->parent = root;
    right->left = root;

    tree = preroot->left;
    tree->parent = NULL;
    free(preroot);
    return tree;
}
//右旋
BRTree r_rotation(BRTree tree, BRTree cur)
{
    if (!tree || !cur)
        return tree;
    //设置傀儡头节点使根节点是其左孩子
    BRTree preroot = create_node(-1, NULL, tree);
    tree->parent = preroot;
    //右旋 将当前结点旋转为其左孩子的右孩子，并将其左孩子的右孩子设置为当前节点的左孩子。
    BRTree root = cur;
    BRTree left = root->left;
    if (!left)
        return tree;
    if (root->parent->left == root)
        root->parent->left = left;
    else if (root->parent->right == root)
        root->parent->right = left;
    left->parent = root->parent;

    root->parent = left;
    root->left = left->right;
    if (left->right)
        left->right->parent = root;
    left->right = root;

    tree = preroot->left;
    tree->parent = NULL;
    free(preroot);
    return tree;
}

//删除
BRTree delete_brtree(BRTree tree, int key)
{
    BRTree del_tree = search(tree, key);
    if (!del_tree)
    {
        printf("删除失败 没有找到 %d\n", key);
        return tree;
    }
    //找到真正要删除的结点
    del_tree = delete_node(tree, del_tree);
    //删除前修正 确保删除后树平衡
    tree = fix_up_del(tree, del_tree);
    //删除del_tree
    if (!del_tree->parent)
    {
        free(del_tree);
        return NULL;
    }
    if (del_tree->parent->left == del_tree)
        del_tree->parent->left = NULL;
    if (del_tree->parent->right == del_tree)
        del_tree->parent->right = NULL;
    free(del_tree);
    return tree;
}
//删除修正 这里负责旋转，即确保删除后树平衡 但是不删除树
BRTree fix_up_del(BRTree tree, BRTree cur_tree)
{
    if (!cur_tree->parent)
        return tree;
    BRTree pa = cur_tree->parent;
    BRTree bro = pa->left == cur_tree ? pa->right : pa->left;
    //1. 结点为红色 设为黑色 直接删除
    if (cur_tree->color == RED)
    {
        cur_tree->color = BLACK;
        return tree;
    }
    //兄弟结点为空
    else if (!bro)
    {
        if (cur_tree->parent->color == RED)
        {
            cur_tree->parent->color = BLACK;
            return tree;
        }
        else
        {
            return fix_up_del(tree, cur_tree->parent);
        }
    }
    //当前结点为黑色
    else if (cur_tree->color == BLACK)
    {
        //当前结点是左孩子
        if (pa->left == cur_tree)
        {
            //兄弟结点为红
            if (bro->color == RED)
            {
                bro->color = BLACK;
                pa->color = RED;
                tree = l_rotation(tree, pa);
                //return tree;
                return fix_up_del(tree, cur_tree);
            }
            //兄弟结点为黑
            else if (bro->color == BLACK)
            {
                //兄弟结点的右子结点是红结点，左子结点任意颜色
                if (bro->right && bro->right->color == RED)
                {
                    bro->color = pa->color;
                    pa->color = BLACK;
                    bro->right->color = BLACK;
                    tree = l_rotation(tree, pa);
                    return tree;
                }
                //兄弟结点的右子结点为黑结点，左子结点为红结点
                else if ((bro->left && bro->left->color == RED) && (!bro->right || (bro->right && bro->right->color == BLACK)))
                {
                    bro->color = RED;
                    bro->left->color = BLACK;
                    tree = r_rotation(tree, bro);
                    return fix_up_del(tree, cur_tree);
                }
                else
                {
                    bro->color = RED;
                    cur_tree = pa;
                    return fix_up_del(tree, cur_tree);
                }
            }
        }
        //当前结点是右孩子
        if (pa->right == cur_tree)
        {
            //兄弟结点为红
            if (bro->color == RED)
            {
                bro->color = BLACK;
                pa->color = RED;
                tree = r_rotation(tree, pa);
                //return tree;
                return fix_up_del(tree, cur_tree);
            }
            //兄弟结点为黑
            else if (bro->color == BLACK)
            {
                //兄弟结点的左子结点是红结点，右子结点任意颜色
                if (bro->left && bro->left->color == RED)
                {
                    bro->color = pa->color;
                    pa->color = BLACK;
                    bro->left->color = BLACK;
                    tree = r_rotation(tree, pa);
                    return tree;
                }
                //兄弟结点的左子结点为黑结点，右子结点为红结点
                else if (bro->right && bro->left && bro->left->color == BLACK && bro->right->color == RED)
                {
                    bro->color = RED;
                    bro->right->color = BLACK;
                    tree = l_rotation(tree, bro);
                    return fix_up_del(tree, cur_tree);
                }
                else
                {
                    bro->color = RED;
                    cur_tree = pa;
                    return fix_up_del(tree, cur_tree);
                }
            }
        }
    }
    return tree;
}
//删除结点 返回最后删除的结点
BRTree delete_node(BRTree tree, BRTree del_tree)
{

    //1. 叶节点 直接删除
    if (!del_tree->left && !del_tree->right)
    {
        return del_tree;
    }
    //若右左孩子 使用左子树中最大的
    else if (del_tree->left)
    {
        BRTree su = maximum(del_tree->left);
        del_tree->key = su->key;
        return delete_node(tree, su);
    }
    //若有右子树 使用右子树中最小的
    else if (del_tree->right)
    {
        BRTree su = minimum(del_tree->right);
        del_tree->key = su->key;
        return delete_node(tree, su);
    }
    return del_tree;
}
BRTree successor(BRTree tree)
{
    if (!tree)
        return NULL;
    //若有右孩子，则取右孩子的最小值
    return minimum(tree->right);
    //没有右孩子向上遍历直到为父节点的左孩子，返回父节点 若父节点为空则返回空
    while (tree && tree->parent->right == tree)
    {
        tree = tree->parent;
    }
    if (!tree)
        return tree;
    else
        return tree->parent;
}
BRTree maximum(BRTree tree)
{
    if (!tree)
        return tree;
    while (tree->right)
    {
        tree = tree->right;
    }
    return tree;
}

BRTree minimum(BRTree tree)
{
    if (!tree)
        return tree;
    while (tree->left)
    {
        tree = tree->left;
    }
    return tree;
}
//从 leaf 到 root 的路径上的black结点数量。
int black_num(BRTree root, BRTree leaf)
{
    if (!leaf || !root)
        return 0;
    int count = root->color == BLACK ? 1 : 0;
    while (leaf != root)
    {
        if (leaf->color == BLACK)
            count++;
        leaf = leaf->parent;
    }
    return count;
}
//保存一棵树到其所有叶子的黑色节点数量
void save_balck_num(BRTree root, BRTree leaf, std::vector<int> &balck)
{
    if (leaf)
    {
        save_balck_num(root, leaf->left, balck);
        if (!leaf->right && !leaf->left)
            balck.push_back(black_num(root, leaf));
        save_balck_num(root, leaf->right, balck);
    }
}

bool check_balck_num_valid(BRTree tree)
{
    if (tree)
    {
        std::vector<int> v;
        save_balck_num(tree, tree, v);
        for (int i = 0; i <= v.size() - 1; i++)
            if (v.at(i) != v.at(0))
                return false;
        return check_balck_num_valid(tree->left);

        return check_balck_num_valid(tree->right);
    }
    return true;
}

void destroy(BRTree tree);