#include "BTree.h"

/*
typedef struct BTREE
{
    int key_num;//键的数量
    int key[2*M+1];//键,有一个冗余的键用来预插入
    BTREE * child[2*M+1];//最多拥有 2M+1个孩子
    bool isleaf;
    //BTree在实际运用中还需要存储值，但是这里就不用了。
}Node,*BTree;
*/

//初始化一个空树
BTree BTree_Init()
{
    return NULL;
}

// 前序遍历
void preorder(BTree tree)
{
    if (tree)
    {
        //printf("tree->key_num %d\n",tree->key_num);
        //打印结点内的第一个值，打印结点的第一个孩子结点，依次打印后面的值和结点
        for (int i = 0; i <= tree->key_num - 1; i++)
        {
            //printf(" %d", tree->key[i]);
            preorder(tree->child[i]);
        }
        preorder(tree->child[tree->key_num]);
    }
}
// 中序遍历
void inorder(BTree tree)
{
    if (tree)
    {
        //打印结点内的第一个值，打印结点的第一个孩子结点，依次打印后面的值和结点
        for (int i = 0; i <= tree->key_num - 1; i++)
        {
            inorder(tree->child[i]);
            //printf(" %d", tree->key[i]);
        }
        inorder(tree->child[tree->key_num]);
    }
}
// 后序遍历
void postorder(BTree tree)
{
    if (tree)
    {
        //后序遍历，
        postorder(tree->child[0]);
        for (int i = 0; i <= tree->key_num - 1; i++)
        {
            postorder(tree->child[i + 1]);
            //printf(" %d", tree->key[i]);
        }
    }
}

void print_btree(BTree tree, int key, int direction);

// (递归实现)查找"b树x"中键值为key的节点
BTree search(BTree tree, int key, int *index)
{
    *index = -1;
    if (tree)
    {
        int child_index = -1;
        if (tree->key[0] > key)
            child_index = 0;
        if (tree->key[tree->key_num - 1] < key)
            child_index = tree->key_num;
        //只有一个结点判断是否相等
        for (int i = 0; i <= tree->key_num - 1; i++)
        {
            if (tree->key[i] == key)
            {
                *index = i;
                return tree;
            }
        }
        //两个或以上结点判断出口
        for (int i = 0; i <= tree->key_num - 2; i++)
        {
            int left = tree->key[i];
            int right = tree->key[i + 1];
            //printf("key: %d left: %d right: %d \n",key,left,right);
            if (left == key)
            {
                *index = i;
                return tree;
            }
            if (right == key)
            {
                *index = i + 1;
                return tree;
            }
            if ((left < key) && (key < right))
            {
                child_index = i + 1;
            }
        }
        return search(tree->child[child_index], key, index);
    }
    *index = -1;
    return NULL;
}
// (非递归实现)查找"b树x"中键值为key的节点
BTree search_iterative(BTree tree, int key, int *index)
{
    while (tree)
    {
        int child_index = -1;
        if (tree->key[0] > key)
            child_index = 0;
        if (tree->key[tree->key_num - 1] < key)
            child_index = tree->key_num;
        //只有一个结点判断是否相等
        for (int i = 0; i <= tree->key_num - 1; i++)
        {
            if (tree->key[i] == key)
            {
                *index = i;
                return tree;
            }
        }
        for (int i = 0; i <= tree->key_num - 2; i++)
        {
            int left = tree->key[i];
            int right = tree->key[i + 1];
            if (left == key)
            {
                *index = i;
                return tree;
            }
            if (right == key)
            {
                *index = i + 1;
                return tree;
            }
            if ((left < key) && (key < right))
            {
                child_index = i + 1;
            }
        }
        tree = tree->child[child_index];
    }
    //没找到
    *index = -1;
    return tree;
}

// 查找最小结点
BTree minimum(BTree tree, int *index)
{
    if (tree == NULL)
    {
        *index = -1;
        return NULL;
    }
    if (tree->isleaf == false)
    {
        return minimum(tree->child[0], index);
    }
    *index = 0;
    return tree;
}
// 查找最大结点
BTree maximum(BTree tree, int *index)
{
    if (tree == NULL)
    {
        *index = -1;
        return NULL;
    }
    if (tree->isleaf == false)
    {
        return maximum(tree->child[tree->key_num], index);
    }
    *index = tree->key_num;
    return tree;
}

// 将结点插入
BTree insert(BTree tree, int key)
{
    //printf("insert %d \n", key);
    //首先找到应该插入的结点,若插入后超载了，则从中间将这个结点一分为二，将中间的结点插入到父节点上，父节点上的插入同理，直到插入成功。
    //空结点直接插入,
    if (tree == NULL)
    {
        tree = insert_into_node(tree, NULL, key, false, -1, NULL, NULL);
        return tree;
    }
    //tree不空 则寻找合适的插入点 遍历结点找到合适的插入子节点，重复，直到到达叶子  普通插入只能首选叶子进行插入。
    BTree node_to_insert = tree;
    while (node_to_insert->isleaf == false)
    {
        //判断插入到哪一个child
        int child_index = 0;
        //小于最左边的，则插入到 child0
        if (key < node_to_insert->key[0])
        {
            child_index = 0;
        }
        //大于最右边的
        else if (key > node_to_insert->key[node_to_insert->key_num - 1])
        {
            child_index = node_to_insert->key_num;
        }
        //从中间找合适的位置
        else
        {
            for (int i = 0; i <= node_to_insert->key_num - 2; i++)
            {
                int left = node_to_insert->key[i];
                int right = node_to_insert->key[i + 1];
                if ((left < key) && (key < right))
                {
                    child_index = i + 1;
                    break;
                }
            }
        }
        //找到合适的插入分支，进行插入
        node_to_insert = node_to_insert->child[child_index];
    }
    //经过数个分支，已经到达叶子结点，进行结点级别的插入。node_to_insert
    if (node_to_insert->isleaf == true)
    {
        tree = insert_into_node(tree, node_to_insert, key, false, 0, NULL, NULL);
    }
    return tree;
}
//将一个值插入一个结点，返回更新过后的树,这里还有插入的是上浮结点的情况。index指的是上浮结点之前所在的结点是要插入到的结点的第几个child
BTree insert_into_node(BTree tree, BTree node_to_insert, int key, bool is_key_to_up, int index, BTree tree_left, BTree tree_right)
{
    //记得每一次产生新的节点之后更新叶子信息。
    //若插入后超载了，则从中间将这个结点一分为二，将中间的结点插入到父节点上，父节点上的插入同理，直到插入成功。
    //若上浮结点且index为-1的话说明是头结点分裂
    //先插入这个结点，再判断是否满
    //node_to_insert==NULL 说明要产生一个新的父节点，当然第一次插入的时候也是如此
    //printf("insert_into_node %d \n", key);
    if (node_to_insert == NULL)
    {
        tree = (BTree)malloc(sizeof(struct BTREE));
        tree->key[0] = key;
        tree->key_num = 1;
        tree->child_num = 2;
        for (int i = 0; i <= 2 * M; i++)
            tree->child[i] = NULL;
        //若初始化根节点则都为空，若是后来分裂产生的根节点，则指向传来的参数。
        if (tree_left)
            tree_left->parent = tree;
        if (tree_right)
            tree_right->parent = tree;
        tree->child[0] = tree_left;
        tree->child[1] = tree_right;
        tree->parent = NULL;
        //如果不是上浮上来的则为叶子，否则不是叶子
        if (is_key_to_up)
            tree->isleaf = false;
        else
            tree->isleaf = true;
        return tree;
    }
    int key_index = -1; //插入的目标位置
    if (node_to_insert->key[0] > key)
    {
        key_index = 0;
    }
    else if (node_to_insert->key[node_to_insert->key_num - 1] < key)
    {
        key_index = node_to_insert->key_num;
    }
    //从中间找合适的位置
    else
    {
        for (int i = 0; i <= node_to_insert->key_num - 2; i++)
        {
            int left = node_to_insert->key[i];
            int right = node_to_insert->key[i + 1];
            if ((left < key) && (key < right))
            {
                key_index = i + 1;
                break;
            }
        }
    }
    //插入到key_index位置，因为有一个冗余的键用于预插入所以可以放心的插入
    node_to_insert->key_num++;
    for (int i = node_to_insert->key_num - 1; i >= key_index + 1; i--)
    {
        node_to_insert->key[i] = node_to_insert->key[i - 1];
    }
    node_to_insert->key[key_index] = key;
    //预载入child  只有上升节点才需要更新child
    if (is_key_to_up)
    {
        node_to_insert->child_num = node_to_insert->key_num + 1;

        //child[index]指向带上来的左节点，child[index+1]指向右节点，孩子的数量永远等于key的数量加一
        for (int i = node_to_insert->key_num; i >= index + 2; i--)
        {
            node_to_insert->child[i] = node_to_insert->child[i - 1];
        }
        node_to_insert->child[key_index] = tree_left;
        node_to_insert->child[key_index + 1] = tree_right;
        tree_left->parent = node_to_insert;
        tree_right->parent = node_to_insert;
        //return tree;
    }
    //预插入成功，判断是否超载
    //未超载
    if (node_to_insert->key_num <= MAX_KEY_NUM)
    {
        //未超载，去下面判断是否为上浮结点，否的话直接返回。
        if (!is_key_to_up)
        {
            return tree;
        }
        else
        {
            return tree;
        }
    }
    //超载,将中间的key上浮插入，两边节点各成一家
    else
    {
        int middle_position = M; //索引值小于M的为左节点，大于M的为右节点，M为中间节点，上移
        int key_to_up = node_to_insert->key[middle_position];
        //将分裂开的child线分别连接到key_to_up插入的地方的左右
        //这里要注意递归的插入，若当前节点是内部结点还需要进行他的子节点的分配。将中间的子节点分配给右侧的结点，因为不可缺少最左边的child
        //得到 index   指的是上浮结点之前所在的结点是要插入到的结点的第几个child
        int key_to_up_index = -1; //若结果是-1，说明没有父节点，这是一个根节点分裂
        //有父节点
        if (node_to_insert->parent != NULL)
        { //判断index
            int child_num = node_to_insert->parent->key_num + 1;
            for (int i = 0; i <= child_num; i++)
            {
                if (node_to_insert->parent->child[i] == node_to_insert)
                {
                    key_to_up_index = i;
                    break;
                }
            }
            //保留0 - M-1 个key在t_l 剩下的放在右边t_r
            BTree t_l = node_to_insert;
            BTree t_r = (BTree)malloc(sizeof(struct BTREE));
            if (!t_r)
            {
                printf("内存不足\n");
                exit(EXIT_FAILURE);
            }
            t_r->key_num = M; //error: 48344239 原因，电脑内存不够
            t_l->key_num = M;
            //如果这个结点是因为下层结点上升才分裂的，则为非叶子结点
            if (is_key_to_up)
            {
                t_r->isleaf = false;
                t_l->isleaf = false;
                t_r->child_num = M + 1;
                t_l->child_num = M + 1;
                t_r->parent = node_to_insert->parent;
                t_l->parent = node_to_insert->parent;
                //非叶子结点，说明其child为满的，并且还有上升结点带来的tree_left 和 tree_right
                //放置child
                for (int i = 0; i <= M; i++)
                {
                    t_l->child[i] = node_to_insert->child[i];
                    t_l->child[i]->parent = t_l;
                }
                for (int i = M + 1; i <= 2 * M + 1; i++)
                {
                    t_r->child[i - M - 1] = node_to_insert->child[i];
                    t_r->child[i - M - 1]->parent = t_r;
                }
                for (int i = M + 1; i <= 2 * M + 1; i++)
                {
                    t_l->child[i] = NULL;
                    t_r->child[i] = NULL;
                }
                //放置key
                for (int i = 0; i <= M - 1; i++)
                {
                    t_l->key[i] = node_to_insert->key[i];
                }
                for (int i = M + 1; i <= 2 * M; i++)
                {
                    t_r->key[i - M - 1] = node_to_insert->key[i];
                }
            }
            //叶子的分裂 不需要分配child
            else
            {
                t_r->isleaf = true;
                t_l->isleaf = true;
                t_r->child_num = 0;
                t_l->child_num = 0;
                t_r->parent = node_to_insert->parent;
                t_l->parent = node_to_insert->parent;
                for (int i = 0; i <= 2 * M + 1; i++)
                {
                    t_l->child[i] = NULL;
                    t_r->child[i] = NULL;
                }
                //放置key
                for (int i = 0; i <= M - 1; i++)
                {
                    t_l->key[i] = node_to_insert->key[i];
                }
                for (int i = M + 1; i <= 2 * M; i++)
                {
                    t_r->key[i - M - 1] = node_to_insert->key[i];
                }
            }
            return insert_into_node(tree, node_to_insert->parent, key_to_up, true, key_to_up_index, t_l, t_r);
        }
        //父节点为空，说明这是一次根节点分裂
        else
        {
            //
            //保留0 - M-1 个key在t_l 剩下的放在右边t_r
            BTree t_l = node_to_insert;
            BTree t_r = (BTree)malloc(sizeof(struct BTREE));
            t_r->key_num = M;
            t_l->key_num = M;
            //如果这个结点是因为下层结点上升才分裂的，则为非叶子结点
            if (is_key_to_up)
            {
                t_r->isleaf = false;
                t_l->isleaf = false;
                t_r->child_num = M + 1;
                t_l->child_num = M + 1;
                t_r->parent = node_to_insert->parent;
                t_l->parent = node_to_insert->parent;
                //非叶子结点，说明其child为满的，并且还有上升结点带来的tree_left 和 tree_right
                //放置child
                for (int i = 0; i <= M; i++)
                {
                    t_l->child[i] = node_to_insert->child[i];
                    t_l->child[i]->parent = t_l;
                }
                for (int i = M + 1; i <= 2 * M + 1; i++)
                {
                    t_r->child[i - M - 1] = node_to_insert->child[i];
                    t_r->child[i - M - 1]->parent = t_r;
                    t_l->child[i] = NULL;
                }
                for (int i = M + 1; i <= 2 * M + 1; i++)
                {
                    t_l->child[i] = NULL;
                    t_r->child[i] = NULL;
                }
                //放置key
                for (int i = 0; i <= M - 1; i++)
                {
                    t_l->key[i] = node_to_insert->key[i];
                }
                for (int i = M + 1; i <= 2 * M; i++)
                {
                    t_r->key[i - M - 1] = node_to_insert->key[i];
                }
            }
            //叶子的分裂 不需要分配child
            else
            {
                t_r->isleaf = true;
                t_l->isleaf = true;
                t_r->child_num = 0;
                t_l->child_num = 0;
                t_r->parent = node_to_insert->parent;
                t_l->parent = node_to_insert->parent;
                for (int i = 0; i <= 2 * M + 1; i++)
                {
                    t_l->child[i] = NULL;
                    t_r->child[i] = NULL;
                }
                //放置key
                for (int i = 0; i <= M - 1; i++)
                {
                    t_l->key[i] = node_to_insert->key[i];
                }
                for (int i = M + 1; i <= 2 * M; i++)
                {
                    t_r->key[i - M - 1] = node_to_insert->key[i];
                }
            }

            return insert_into_node(tree, NULL, key_to_up, true, -1, t_l, t_r);
        }
    }
}

// 删除数据
BTree delete_btree(BTree tree, bool useindex, BTree del_tree, int del_key_index, int key)
{
    //1. 删除叶子节点 且 删除之后key_num>=M , 直接删除
    //2. 删除叶子节点但是删除过后 keu_num<M ,则

    //寻找要删除的数据 不使用index
    if (useindex == false)
    {
        del_tree = search(tree, key, &del_key_index);
        if (del_tree)
            ; //printf("search %d\n", del_tree->key[del_key_index]);
        else
        {
            printf("删除失败 没找到 %d\n", key);
            return tree;
        }
    }
    else
    {
        key = del_tree->key[del_key_index];
        //printf("删除 %d 使用index\n",del_tree->key[del_key_index]);
    }
    //printf("delete_btree 删除 %d \n",del_tree->key[del_key_index]);
    //情况一 叶子结点且删除后key_num>=M 或者是根节点
    if (((del_tree->key_num >= M + 1) || (del_tree->parent == NULL)) && (del_tree->isleaf == true))
    {
        //printf("1 删除叶子结点 %d \n",del_tree->key[del_key_index]);
        for (int i = del_key_index; i <= del_tree->key_num - 2; i++)
        {
            del_tree->key[i] = del_tree->key[i + 1];
        }
        del_tree->key_num--;
        if (del_tree->parent == NULL)
        {
            //根节点
            if (del_tree->key_num == 0)
            {
                free(tree);
                tree = NULL;
            }
        }
        //printf("1 删除成功\n");
        return tree;
    }
    // 删除叶子(非根节点)，但是删除之后小于M
    else if ((del_tree->key_num < M + 1) && (del_tree->isleaf == true))
    {
        //printf("2 删除非叶子结点 %d \n",del_tree->key[del_key_index]);
        for (int i = del_key_index; i <= del_tree->key_num - 2; i++)
        {
            del_tree->key[i] = del_tree->key[i + 1];
        }
        del_tree->key_num--;
        //判断左右哪一侧可以借key
        //-1: 左侧是否可以借  1: 右    0：都不可借，只有合并
        int borrow = borrow_direction(del_tree);
        //左
        if (borrow == -1)
        {
            //printf("borrow -1\n");
            int index_child = childindex(del_tree->parent, del_tree);
            while (1)
            {
                index_child--;
                //将index_child左右两侧进行交换,返回交换过后的左侧结点剩余值
                if (l_exchange(del_tree->parent, index_child) >= M)
                {
                    break;
                }
            }
        }
        //右
        else if (borrow == 1)
        {
            //printf("borrow 1\n");
            //这里的叶子为非根节点
            int index_child = childindex(del_tree->parent, del_tree) - 1;
            while (1)
            {
                index_child++;
                //将index_child左右两侧进行交换,返回交换过后的左侧结点剩余值
                if (r_exchange(del_tree->parent, index_child) >= M)
                {
                    break;
                }
            }
        }
        //都不能借，进行合并
        else if (borrow == 0)
        {
            //先合并，合并完成之后判断是否符合标准 返回合并之后的parent,如果是根节点的话就直接返回根节点
            del_tree = merge(del_tree);
            //判断是否合格
            if (del_tree->key_num >= M || del_tree->parent == NULL)
            {
                if (del_tree->parent == NULL)
                {
                    //根节点
                    return del_tree;
                }
                else
                {
                    return tree;
                }
            }
            //不合格 这里的del肯定不指向根节点
            else
            {
                del_tree = borrow_from_parent(del_tree);
                //现在del_tree 指向借的最后一个结点，判断是否借成功  >=M 或者是根节点
                if (del_tree->key_num >= M || del_tree->parent == NULL)
                {
                    return tree;
                }
                //没有借成功，说明现在del为根节点的儿子且根节点只有一个key
                else
                {
                    return merge_root(tree);
                }
            }
        }

        //printf("2 删除成功\n");
        return tree;
    }
    //删除非叶子，递归使用后继元素进行替代并且删除后继元素。
    else if (del_tree->isleaf == false)
    {
        //printf("3 删除非叶子结点 %d \n",del_tree->key[del_key_index]);
        del_tree;
        del_key_index;
        int index_success = -1;
        while (del_tree->isleaf == false)
        {
            BTree successor = success_btree(tree, true, del_tree, &del_key_index, -1, &index_success);
            //替换
            del_tree->key[del_key_index] = successor->key[index_success];
            del_tree = successor;
            del_key_index = index_success;
        }
        //del_tree现在指向叶子结点，递归到上两层。
        return delete_btree(tree, true, del_tree, del_key_index, -1);
    }

    printf("删除失败\n");
    return tree;
}
//寻找后继 即中序遍历中的后面一位
BTree success_btree(BTree tree, bool useindex, BTree tree_source, int *index_source, int key, int *index_success)
{
    //不使用index来表示一个key，而是直接传入一个key值来自动寻找。这样即使树种存在两个相同的key也可以寻找到后继了。
    if (useindex == false)
    {
        index_source = (int *)malloc(sizeof(int));
        tree_source = search(tree, key, index_source);
    }
    BTree successor = NULL;
    if (tree_source == NULL)
    {
        *index_success = -1;
        return NULL;
    }
    //如果是叶子中非最后一个，则返回其后面的一个数据
    else if ((tree_source->isleaf == true) && ((*index_source) < tree_source->key_num - 1))
    {
        *index_success = *index_source + 1;
        return tree_source;
    }
    //是叶子中的最后一个
    else if ((tree_source->isleaf == true) && ((*index_source) == tree_source->key_num - 1))
    {
        //递归向上遍历，直到找到一个结点不是其父节点的最后一个孩子
        BTree t_up = tree_source;
        while (t_up)
        {
            int t_up_child_index = childindex(t_up->parent, t_up);
            if (t_up_child_index == -1)
            {
                //到达根节点,这里肯定是从最右边到达根节点了，所以返回空
                *index_success = -1;
                return NULL;
            }
            else if (t_up_child_index < t_up->parent->key_num)
            {
                //找到一个不是其父节点最后一个孩子的结点，返回父节点 key[t_up_child_index]
                *index_success = t_up_child_index;
                return t_up->parent;
            }
            else if (t_up_child_index == t_up->parent->key_num)
            {
                //仍然是其父节点的最后一个孩子，继续向上
                t_up = t_up->parent;
            }
        }
    }
    //非叶子
    else if (tree_source->isleaf == false)
    {
        //不是叶子的话总会有后继的。即以其右侧孩子为根节点的最小值
        return minimum(tree_source->child[*index_source + 1], index_success);
    }
}
//判断是第几个孩子
int childindex(BTree pa, BTree son)
{
    if ((pa == NULL) || (son == NULL))
    {
        return -1;
    }
    else
    {
        for (int i = 0; i <= pa->key_num; i++)
        {
            if (pa->child[i] == son)
                return i;
        }
    }
    return -1;
}
int borrow_direction(BTree tree)
{
    if (tree == NULL)
    {
        return 0;
    }
    int borrow_direction = 0;
    int index_child = childindex(tree->parent, tree);
    if (index_child == -1)
    {
        //不可借
        return 0;
    }
    int num_child = tree->parent->key_num + 1;
    for (int i = 0; i < index_child; i++)
    {
        if (tree->parent->child[i]->key_num >= M + 1)
        {
            //向左借
            return -1;
        }
    }
    for (int i = index_child + 1; i < num_child; i++)
    {
        if (tree->parent->child[i]->key_num >= M + 1)
        {
            //向右借
            return 1;
        }
    }
    return 0;
}
//将index_key左右两侧进行交换,返回交换过后的左侧结点剩余值
int l_exchange(BTree tree, int index_key)
{
    BTree left_bro = NULL;
    BTree right_bro = NULL;
    left_bro = tree->child[index_key];
    right_bro = tree->child[index_key + 1];
    int pa_key = tree->key[index_key];
    for (int i = right_bro->key_num; i >= 1; i--)
    {
        right_bro->key[i] = right_bro->key[i - 1];
    }
    right_bro->key[0] = pa_key;
    tree->key[index_key] = left_bro->key[left_bro->key_num - 1];
    left_bro->key_num--;
    return left_bro->key_num;
}
//交换左侧
int r_exchange(BTree tree, int index_key)
{
    BTree left_bro = NULL;
    BTree right_bro = NULL;
    left_bro = tree->child[index_key];
    right_bro = tree->child[index_key + 1];
    int pa_key = tree->key[index_key];
    left_bro->key[left_bro->key_num++] = pa_key;
    tree->key[index_key] = right_bro->key[0];
    for (int i = 0; i <= right_bro->key_num - 2; i++)
    {
        right_bro->key[i] = right_bro->key[i + 1];
    }
    right_bro->key_num--;
    return right_bro->key_num;
}
//合并一个结点及其孩子 用于节点只有一个key,所以只有两个孩子 这里的tree为父节点
BTree merge_onekey(BTree tree)
{
    BTree pa = tree;
    BTree left_bro = tree->child[0];
    BTree right_bro = tree->child[1];
    //right_bro上位 重新插入pa和left
    left_bro->parent = pa->parent;
    if (pa->parent)
        pa->parent->child[childindex(pa->parent, pa)] = right_bro;
    else
        tree = right_bro;
    //插入
    tree = insert(tree, pa->key[0]);
    for (int i = 0; i <= left_bro->key_num - 1; i++)
    {
        tree = insert(tree, left_bro->key[i]);
    }
}
//合并一个结点 这里的tree 是孩子结点
BTree merge(BTree tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    //如果不是最右边的那个孩子则和右兄弟合并
    int index_child = childindex(tree->parent, tree);
    int pa_key_index = -1;
    BTree left_bro = NULL;
    BTree right_bro = NULL;
    //最右边的孩子，和左兄弟在一起
    if (index_child == tree->parent->key_num)
    {
        left_bro = tree->parent->child[index_child - 1];
        right_bro = tree;
        pa_key_index = tree->parent->key_num - 1;
    }
    //不是最右边的孩子，则和右兄弟在一起
    else
    {
        right_bro = tree->parent->child[index_child + 1];
        left_bro = tree;
        pa_key_index = index_child;
    }
    int left_bro_key_num = left_bro->key_num;
    left_bro->key[left_bro_key_num++] = tree->parent->key[pa_key_index];
    for (int i = 0; i <= right_bro->key_num - 1; i++)
    {
        left_bro->key[left_bro_key_num++] = right_bro->key[i];
    }
    left_bro->key_num = left_bro_key_num;

    //将父节点key进行整合和
    for (int i = pa_key_index; i <= tree->parent->key_num - 2; i++)
    {
        tree->parent->key[i] = tree->parent->key[i + 1];
    }
    tree->parent->key_num--;
    //child
    for (int i = pa_key_index + 1; i <= tree->parent->key_num; i++)
    {
        tree->parent->child[i] = tree->parent->child[i + 1];
    }
    tree->parent->child[tree->parent->key_num + 1] = NULL;
    tree->parent->child_num = tree->parent->key_num + 1;
    free(right_bro);
    if (left_bro->parent->key_num == 0)
    {
        //说明 left_bro->parent 为根节点 此时根节点没有key了，只有一个child,所以此时返回 left_bro;
        free(left_bro->parent);
        left_bro->parent = NULL;
        left_bro->isleaf = true;
        return left_bro;
    }
    //返回合并后的 parent 以为此时的parent可能key_num<M
    else
        return left_bro->parent;
}
//向父节点借孩子 返回能借到结点的最后一个结点
//判断合并到一起的节点数是否超标，若超标则说明可借，则借一个，否则合并到一起
BTree borrow_from_parent(BTree tree)
{
    if (tree == NULL || tree->parent == NULL)
    {
        return tree;
    }
    //直到父节点是根节点且只有一个key
    if (tree->parent->parent == NULL && tree->parent->key_num == 1)
    {
        return tree;
    }
    //借到了富有结点的，不用继续了
    if (tree->key_num >= M)
    {
        return tree;
    }
    //是其最后一个孩子 跟左兄弟在一起
    if (childindex(tree->parent, tree) == tree->parent->key_num)
    {
        int index_child = childindex(tree->parent, tree);
        BTree left_bro = tree->parent->child[index_child - 1];
        BTree right_bro = tree->parent->child[index_child];
        int key_num_totle = left_bro->key_num + right_bro->key_num + tree->parent->key_num;
        if (key_num_totle <= 2 * M)
        {
            //可以合并
            merge_parent(tree->parent, index_child - 1);
        }
        else
        {
            balance_two_child(tree->parent, index_child - 1);
        }
        return borrow_from_parent(tree->parent);
    }
    //不是最后一个孩子
    else
    {
        int index_child = childindex(tree->parent, tree);
        BTree left_bro = tree->parent->child[index_child];
        BTree right_bro = tree->parent->child[index_child + 1];
        int key_num_totle = left_bro->key_num + right_bro->key_num + 1;
        if (key_num_totle <= 2 * M)
        {
            //可以合并
            merge_parent(tree->parent, index_child);
        }
        else
        {
            balance_two_child(tree->parent, index_child);
        }
        return borrow_from_parent(tree->parent);
    }
    return borrow_from_parent(tree->parent);
}
//tree 为根节点，合并其与其孩子 事情能到这一步说明tree只有两个孩子了
BTree merge_root(BTree tree)
{
    BTree left_bro = tree->child[0];
    BTree right_bro = tree->child[1];
    //判断总共的key个数
    int key_num_totle = left_bro->key_num + right_bro->key_num + tree->key_num;
    if (key_num_totle <= 2 * M)
    {
        //可以合并到一起
        int left_bro_key_num = left_bro->key_num;
        int left_bro_child_num = left_bro_key_num + 1;
        left_bro->key[left_bro_key_num++] = tree->key[0];
        for (int i = 0; i <= right_bro->key_num - 1; i++)
        {
            left_bro->key[left_bro_key_num++] = right_bro->key[i];
        }
        for (int i = 0; i <= right_bro->key_num; i++)
        {
            right_bro->child[i]->parent = left_bro;
            left_bro->child[left_bro_child_num++] = right_bro->child[i];
        }
        left_bro->key_num = left_bro_key_num;
        free(tree);
        free(right_bro);
        left_bro->parent = NULL;
        return left_bro;
    }
    else
    {
        //太多了合并不到一起
        //此时结点多的哪一个借一些结点给另一个
        int left_bro_key_num = left_bro->key_num;
        int right_bro_key_num = right_bro->key_num;
        if (left_bro_key_num > right_bro_key_num)
        {
            //左侧KEY多
            right_bro->key_num++;
            for (int i = right_bro->key_num - 1; i >= 1; i--)
            {
                right_bro->key[i] = right_bro->key[i - 1];
            }
            right_bro->key[0] = tree->key[0];
            tree->key[0] = left_bro->key[left_bro->key_num - 1];
            left_bro->key_num--;
            for (int i = right_bro->key_num; i >= 1; i--)
            {
                right_bro->child[i] = right_bro->child[i - 1];
            }
            right_bro->child[0] = left_bro->child[left_bro->key_num + 1];
            right_bro->child[0]->parent = right_bro;
            left_bro->child[left_bro->key_num + 1] = NULL;
            return tree;
        }
        else
        {
            //右侧key多 从右边向左边移动一个
            left_bro->key[left_bro->key_num++] = tree->key[0];
            tree->key[0] = right_bro->key[0];
            left_bro->child[left_bro->key_num] = right_bro->child[0];
            right_bro->child[0]->parent = left_bro;
            right_bro->key_num--;
            for (int i = 0; i <= right_bro->key_num; i++)
            {
                right_bro->child[i] = right_bro->child[i + 1];
            }
            for (int i = 0; i <= right_bro->key_num - 1; i++)
            {
                right_bro->key[i] = right_bro->key[i + 1];
            }
            right_bro->child[right_bro->key_num + 1] = NULL;
            return tree;
        }
    }
}
//协调两个孩子的节点数量 多的给少的一个，这其中当然也要通过parent->key进行交换
BTree balance_two_child(BTree tree, int index)
{
    //index为父节点的keyindex,协调其左右两侧的孩子
    BTree pa = tree;
    BTree left_bro = pa->child[index];
    BTree right_bro = pa->child[index + 1];
    if (left_bro->key_num > M && right_bro->key_num < M)
    {
        //左侧KEY多
        //更新右节点的key
        right_bro->key_num++;
        for (int i = right_bro->key_num - 1; i >= 1; i--)
        {
            right_bro->key[i] = right_bro->key[i - 1];
        }
        right_bro->key[0] = tree->key[0];
        //跟新父节点
        tree->key[0] = left_bro->key[left_bro->key_num - 1];
        //更新左节点的key_num
        left_bro->key_num--;
        //更新右节点的child
        for (int i = right_bro->key_num; i >= 1; i--)
        {
            right_bro->child[i] = right_bro->child[i - 1];
        }
        right_bro->child[0] = left_bro->child[left_bro->key_num + 1];
        right_bro->child[0]->parent = right_bro;
        left_bro->child[left_bro->key_num + 1] = NULL;
        return tree;
    }
    else if ((right_bro->key_num > M && left_bro->key_num < M))
    {
        //右孩子的key数量多，借给左孩子
        //父节点下移
        left_bro->key[left_bro->key_num++] = tree->key[0];
        //更新父节点
        tree->key[0] = right_bro->key[0];
        //更新左节点的孩子
        left_bro->child[left_bro->key_num] = right_bro->child[0];
        right_bro->child[0]->parent = left_bro;
        //更新右节点
        right_bro->key_num--;
        for (int i = 0; i <= right_bro->key_num; i++)
        {
            right_bro->child[i] = right_bro->child[i + 1];
        }
        for (int i = 0; i <= right_bro->key_num - 1; i++)
        {
            right_bro->key[i] = right_bro->key[i + 1];
        }
        right_bro->child[right_bro->key_num + 1] = NULL;
        return tree;
    }
    return tree;
}
//合并tree index 两边的孩子 前提是合并之后不超
BTree merge_parent(BTree tree, int index)
{
    //index为父节点的keyindex,合并其左右两侧的孩子
    BTree pa = tree;
    BTree left_bro = pa->child[index];
    BTree right_bro = pa->child[index + 1];

    left_bro->child_num = left_bro->key_num + 1;
    //整合left
    left_bro->key[left_bro->key_num++] = pa->key[index];
    for (int i = 0; i <= right_bro->key_num - 1; i++)
    {
        left_bro->key[left_bro->key_num++] = right_bro->key[i];
    }
    for (int i = 0; i <= right_bro->key_num; i++)
    {
        left_bro->child[left_bro->child_num++] = right_bro->child[i];
        right_bro->child[i]->parent = left_bro;
    }
    //整合pa
    for (int i = index; i <= pa->key_num - 2; i++)
    {
        pa->key[i] = pa->key[i + 1];
    }
    for (int i = index + 1; i <= pa->key_num - 1; i++)
    {
        pa->child[i] = pa->child[i + 1];
    }
    pa->child[pa->key_num--] = NULL;
}
// 销毁b树
void destroy(BTree tree)
{
    ;
}
