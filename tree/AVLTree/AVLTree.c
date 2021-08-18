#include "AVLTree.h"

AVLTree AVLTree_Init()
{
    return NULL;
}

AVLTree AVLTree_Create(int key)
{
    AVLTree tree=(AVLTree)malloc(sizeof(struct AVLTREE));
    tree->Key=key;
    tree->Heigth=0;
    tree->Left=NULL;
    tree->Right=NULL;
    tree->Parent=NULL;
    return tree;
}

// 获取AVL树的高度
int avltree_height(AVLTree tree)
{
    return tree->Heigth;
}

// 前序遍历"AVL树"
void preorder_avltree(AVLTree tree)
{
    if(!tree)
        return;
    printf("%d ",tree->Key);
    preorder_avltree(tree->Left);
    preorder_avltree(tree->Right);
}
// 中序遍历"AVL树"
void inorder_avltree(AVLTree tree)
{
    if(!tree)
        return;
    inorder_avltree(tree->Left);
    printf("key: %d height: %d\n",tree->Key,tree->Heigth);
    inorder_avltree(tree->Right);
}
// 后序遍历"AVL树"
void postorder_avltree(AVLTree tree)
{
    if(!tree)
        return;
    postorder_avltree(tree->Left);
    postorder_avltree(tree->Right);
    printf("%d ",tree->Key);
}

//更新树的高度
int update_avltree_heigth(AVLTree tree)
{
    if(tree==NULL)
    {
        return 0;
    }
    else
    {
        int hei_left=update_avltree_heigth(tree->Left);
        int hei_right=update_avltree_heigth(tree->Right);
        tree->Heigth=(MAX(hei_left,hei_right))+1;
        //printf("hei_left: %d hei_right: %d height: %d\n",hei_left,hei_right,tree->Heigth);
        return tree->Heigth;
    }
}
//寻找不平衡的结点
AVLTree search_unbalanced_tree(AVLTree tree)
{
    //找到引起失衡的节点 自己失衡，但是孩子不失衡。
    if(tree==NULL)
    {
        return NULL;
    }
    update_avltree_heigth(tree);
    //记得在这之前更新树的高度
    int hei_left=(tree->Left)?tree->Left->Heigth:0;
    int hei_right=(tree->Right)?tree->Right->Heigth:0;
    int hei_sub=abs(hei_left-hei_right);
    if(hei_sub<=1)
    {
        //平衡
        return NULL;
    }
    if(search_unbalanced_tree(tree->Left)!=NULL)
    {
        return search_unbalanced_tree(tree->Left);
    }
    if(search_unbalanced_tree(tree->Right)!=NULL)
    {
        return search_unbalanced_tree(tree->Right);
    }
    if(hei_sub>=2)
    {
        return tree;
    }
}

// 将结点插入到AVL树中，返回根节点
AVLTree avltree_insert(AVLTree tree, int key)
{
    //插入之后分为四种平衡破坏的状态
    AVLTree result=NULL;
    AVLTree tree_to_insert=AVLTree_Create(key);
    AVLTree p=tree;
    while(p)
    {
        if(p->Key<=key)
        {
            //如果p的右孩子为空则插入到右
            if(!p->Right)
            {
                p->Right=tree_to_insert;
                tree_to_insert->Parent=p;
                break;
            }
            else
                p=p->Right;
        }
        else if(p->Key>=key)
        {
            if(!p->Left)
            {
                //插入为左孩子
                p->Left=tree_to_insert;
                tree_to_insert->Parent=p;
                break;
            }
            p=p->Left;
        }
    }
    if(!tree)
    {
        //说明树本为空
        tree=tree_to_insert;
    }
    //result= AVLTree_make_it_balance(tree);
    return tree;
}

// 删除结点(key是节点值)，返回根节点
AVLTree avltree_delete(AVLTree tree, int key)
{
    AVLTree p=tree;
    AVLTree result=tree;
    while(p!=NULL)
    {
        if(p->Key<key)
        {
            p=p->Right;
        }
        else if(p->Key>key)
        {
            p=p->Left;
        }
        else
        {
            //找到了 
            break;
        }
    }
    if(p==NULL)
    {
        printf("没有找到这个结点 %d \n",key);
        return NULL;
    }
    else
    {
        //找到了结点进行删除并再次平衡。
        //1. 删除的是头节点按 3 4 行事
        //2. 删除的是叶子则直接free
        //3. 删除的结点只有一个孩子则继承其位置
        //4. 删除的结点两个孩子都有，则若其为左孩子，则将其右孩子插入其左孩子的最右边。若其为右孩子，则将其左孩子插入其右孩子的最左边
        AVLTree tree_to_del=p;
        AVLTree pre_root=AVLTree_Create(0);
        pre_root->Left=tree;
        tree->Parent=pre_root;
        //现在设一个傀儡 pre_root 这样头节点和其他结点都一样了
        //1. 叶子没有孩子
        if((!tree_to_del->Left)&&(!tree_to_del->Right))
        {
            if(tree_to_del->Parent->Left==tree_to_del)
                tree_to_del->Parent->Left=NULL;
            if(tree_to_del->Parent->Right==tree_to_del)
                tree_to_del->Parent->Right=NULL;    
            free(tree_to_del);
        }
        else if((tree_to_del->Left!=NULL)&&(tree_to_del->Right==NULL))
        {
            //只有左孩子

            if(tree_to_del->Parent->Left==tree_to_del)
                tree_to_del->Parent->Left=tree_to_del->Left;
            if(tree_to_del->Parent->Right==tree_to_del)
                tree_to_del->Parent->Right=tree_to_del->Left;
                
            tree_to_del->Left->Parent=tree_to_del->Parent; 
            tree_to_del->Left->Heigth--;
            free(tree_to_del);
        }
        else if((tree_to_del->Left==NULL)&&(tree_to_del->Right!=NULL))
        {
            //只有右孩子

            if(tree_to_del->Parent->Left==tree_to_del)
                tree_to_del->Parent->Left=tree_to_del->Right;
            if(tree_to_del->Parent->Right==tree_to_del)
                tree_to_del->Parent->Right=tree_to_del->Right;
            
            tree_to_del->Right->Parent=tree_to_del->Parent; 
            tree_to_del->Right->Heigth--;
            free(tree_to_del);
        }
        else
        {
            //两个孩子都有
            //若其为左孩子，则将其右孩子插入其左孩子的最右边。若其为右孩子，则将其左孩子插入其右孩子的最左边
            if(tree_to_del->Parent->Left==tree_to_del)
            {
                //我觉得不管删除的结点时左孩子还是右孩子，都让其左孩子替代其位置，其右孩子插入到左孩子的最右边

                //寻找左孩子的最右边
                AVLTree MAX_Right=tree_to_del->Left;
                while(MAX_Right->Right)
                {
                    MAX_Right=MAX_Right->Right;
                }
                //将右孩子插入进去
                MAX_Right->Right=tree_to_del->Right;
                tree_to_del->Right->Parent=MAX_Right;
                //更新其深度信息。 略

                //放置左孩子
                if(tree_to_del->Parent->Left==tree_to_del)
                    tree_to_del->Parent->Left=tree_to_del->Left;
                if(tree_to_del->Parent->Right==tree_to_del)
                    tree_to_del->Parent->Right=tree_to_del->Left;
                tree_to_del->Left->Parent=tree_to_del->Parent; 
                tree_to_del->Left->Heigth--;
                //现在其左孩子已经坐上了他的位置。
                free(tree_to_del);
            }
        }
        //头归原主
        tree=pre_root->Left;
    }
    //删除完成，需要判断不平衡的状态并进行修正。
    //result=AVLTree_make_it_balance(tree);
    return tree;
}

//判断一棵树不平衡的状态
UNBALANCED_STATUS AVLTree_judge_unbalance_status(AVLTree unbalanced_tree)
{
    // LL, LR, RL, RR, balanceD  
    AVLTree tree=unbalanced_tree;
    //B1: 失衡结点
    //B2：失衡因节点，因为这个结点才失衡的。
    //B3：失衡因节点的一个祖宗&&失衡结点的一个孙子。
    //即寻找B3，既是B2的祖宗（自己可以是自己的祖宗），也是B1的孙子。
    //然后判断B3是B1的哪一个孙子即可得知是哪种情况。
    //向下找两层高度最大的子树，其方向就是不平衡的状态。
    //加等于号为了防止判断不出来 不如这种情况 10 5 1 7 
    //L
    //height_avltree
    if(height_avltree(tree->Left)>=height_avltree(tree->Right))
    {
        //L
        AVLTree tree_l=tree->Left;
        if(height_avltree(tree_l->Left)>=height_avltree(tree_l->Right))
        {
            return LL;
        }
        else if(height_avltree(tree_l->Left)<height_avltree(tree_l->Right))
        {
            return LR;
        }
    }
    //R
    else if(height_avltree(tree->Left)<height_avltree(tree->Right))
    {
        //L
        AVLTree tree_r=tree->Right;
        if(height_avltree(tree_r->Left)>height_avltree(tree_r->Right))
        {
            return RL;
        }
        else if(height_avltree(tree_r->Left)<=height_avltree(tree_r->Right))
        {
            return RR;
        } 
    }
    return BALANCED;
}

//使树平衡。
AVLTree AVLTree_make_it_balance(AVLTree tree)
{
    AVLTree result=tree;
    //设一个傀儡头节点
    AVLTree preroot=AVLTree_Create(0);
    preroot->Left=tree;
    tree->Parent=preroot;
    //更新高度
    update_avltree_heigth(tree);
    //寻找不平衡的结点
    if(search_unbalanced_tree(tree))
    {
        AVLTree unbalanced_tree=search_unbalanced_tree(tree);
        printf("结点：%d 不平衡\n",unbalanced_tree->Key);
        //更新高度成功，现在肯可能造成不平衡的只有tree_to_insert,所以判断其父节点的高度信息即可。
        //插入完成，需要判断不平衡的状态并进行修正。
        UNBALANCED_STATUS status=AVLTree_judge_unbalance_status(unbalanced_tree);
        
        //status=LR;
        if(status==LL)
        {   
            printf("ll\n");
            ll_rotation(unbalanced_tree);
        }
        else if(status==LR)
        {
            printf("lr\n");
            //绕两次，
            AVLTree k1=unbalanced_tree->Left;
            AVLTree k2=unbalanced_tree;
            rr_rotation(k1);
            ll_rotation(k2);
        }
        else if(status==RR)
        {
            printf("rr\n");
            rr_rotation(unbalanced_tree);
        }
        else if(status==RL)
        {
            printf("rl\n");
            //绕两次
            AVLTree k1=unbalanced_tree->Right;
            AVLTree k2=unbalanced_tree;
            ll_rotation(k1);
            rr_rotation(k2);
        }
        else
        {
            printf("balance\n");
        }
    }
    else
        printf("树平衡\n");
    result=preroot->Left;
    return result;
}
AVLTree balance(AVLTree tree)
{
    while(search_unbalanced_tree(tree))
    {
        //update_avltree_heigth(tree);
        tree=AVLTree_make_it_balance(tree);
        //print_avltree(tree,tree->Key,0);
    }
    return tree;
}
//height
int height_avltree(AVLTree tree)
{
    if(tree==NULL)
    {
        return 0;
    }
    else
        return tree->Heigth;
}
void ll_rotation(AVLTree k2)
{
    //k1替代k2,k1的右孩子变成k2的左孩子,k2变成k1的右孩子，。
    AVLTree k1 = k2->Left;
    if (k2->Parent->Left == k2)
    {
        //k2是左孩子
        k2->Parent->Left = k1;
    }
    else
    {
        k2->Parent->Right = k1;
    }
    k1->Parent=k2->Parent;
    k2->Left = k1->Right;
    if (k1->Right)
        k1->Right->Parent = k2;
    k2->Left=k1->Right;
    k2->Parent = k1;
    k1->Right = k2;
    //return k1;   
} 
void rr_rotation(AVLTree k2)
{
    //k1替代k2 k1的左孩子变成k2的右孩子，k2变为k1的左孩子。
    AVLTree k1=k2->Right;
    if(k2->Parent->Left==k2)
    {
        k2->Parent->Left=k1;
    }
    else
    {
        k2->Parent->Right=k1;
    }
    k1->Parent=k2->Parent;
    if(k1->Left)
        k1->Left->Parent=k2;
    k2->Right=k1->Left;
    k2->Parent=k1;
    k1->Left=k2;
}
// (递归实现)查找"AVL树x"中键值为key的节点
AVLTree avltree_search(AVLTree tree, int key)
{
    if(tree==NULL)
    {
        return NULL;
    }
    else if(tree->Key==key)
    {
        printf("找到了 %d \n",key);
        return tree;
    }
    else if(key<tree->Key)
    {
        return avltree_search(tree->Left,key);
    }
    else if(key>tree->Key)
    {
        return avltree_search(tree->Right,key);
    }
}
// (非递归实现)查找"AVL树x"中键值为key的节点
AVLTree iterative_avltree_search(AVLTree tree, int key)
{
    while(tree)
    {
        if(tree->Key==key)
        {
            printf("找到了 %d \n",tree->Key);
            return tree;
        }
        else if(tree->Key>key)
        {
            tree=tree->Left;
        }
        else if(tree->Key<key)
        {
            tree=tree->Right;
        }
    }
}

// 查找最小结点：返回tree为根结点的AVL树的最小结点。
AVLTree avltree_minimum(AVLTree tree)
{
    AVLTree min=tree;
    if(min==NULL)
    {
        return NULL;
    }
    else
    {
        while(min->Left)
        {
            min=min->Left;
        }
    }
    return min;
}
// 查找最大结点：返回tree为根结点的AVL树的最大结点。
AVLTree avltree_maximum(AVLTree tree)
{
    AVLTree max=tree;
    if(max==NULL)
    {
        return NULL;
    }
    else
    {
        while(max->Right)
        {
            max=max->Right;
        }
    }
    return max;
}

//打印树
void print_avltree(AVLTree tree, int key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            printf("%2d is root\n", tree->Key, key);
        else                // tree是分支节点
            printf("%2d is %2d's %6s child\n", tree->Key, key, direction==1?"right" : "left");

        print_avltree(tree->Left, tree->Key, -1);
        print_avltree(tree->Right,tree->Key,  1);
    }
}

// 销毁AVL树
void destroy_avltree(AVLTree tree)
{
    if(tree==NULL)
    {
        return;
    }
    destroy_avltree(tree->Left);
    destroy_avltree(tree->Right);
    tree->Parent=NULL;
    tree->Left=NULL;
    tree->Right=NULL;
    free(tree);
    return;
}