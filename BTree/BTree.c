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
BTree delete_btree(BTree tree, int key)
{
    //1. 删除叶子节点 且 删除之后key_num>=M , 直接删除
    //2. 删除叶子节点但是删除过后 keu_num<M ,则

    //寻找要删除的数据
    int del_key_index = -1;
    BTree del_tree = search(tree, key, &del_key_index);
    if (del_tree)
        printf("search %d\n", del_tree->key[del_key_index]);
    else
    {
        printf("没找到\n");
        return tree;
    }
    //情况一
    if ((del_tree->key_num >= M + 1) && (del_tree->isleaf == true))
    {
        for (int i = del_key_index; i <= del_tree->key_num - 2; i++)
        {
            del_tree->key[i] = del_tree->key[i + 1];
        }
        del_tree->key_num--;
        printf("删除成功 %d\n", key);
        return tree;
    }
    // 删除叶子，但是删除之后小于M
    else if ((del_tree->key_num < M + 1) && (del_tree->isleaf == true))
    {
    }
    //删除非叶子，递归使用后继元素进行替代并且删除后继元素。
    else if (del_tree->isleaf == false)
    {
        int success_index = -1;
        BTree successor = success_btree(tree, del_tree->key[del_key_index], &success_index);
        while (successor)
        {
            int temp_success_index=-1;
            int temp_del_key=successor->key[success_index];
            BTree temp_successor=success_btree(tree, temp_del_key, &temp_success_index);
            //替代
            del_tree->key[del_key_index] = successor->key[success_index];
            del_tree=successor;
            successor=temp_successor;
            
        }
    }

    printf("删除失败\n");
    return tree;
}
//寻找后继 即中序遍历中的后面一位
BTree success_btree(BTree tree, int key, int *index_success)
{
    int *index_source = (int *)malloc(sizeof(int));
    BTree tree_source = search(tree, key, index_source);
    BTree successor = NULL;
    if(tree_source==NULL)
    {
        *index_success=-1;
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
        //递归向上遍历，直到找到一个结点不是其父节点的额最后一个孩子
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
// 销毁b树
void destroy(BTree tree);
