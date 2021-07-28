
#define M 4

#include "BTree.c"

//一亿条数据  
#define ITEM_NUM 100

//阶数增大但又不太大 则查询时间增大，其余时间减少

int main()
{
    printf("效率test 当前阶数为 %d \n",M);
    time_t start, end;

    start = time(NULL);
    BTree tree = BTree_Init();
    for (int i = 0; i <= ITEM_NUM; i++)
    {
        tree = insert(tree, i);
    }
    end = time(NULL);
    printf("插入 %d 个数用时 %d s\n",ITEM_NUM,end-start);


    start = time(NULL);
    preorder(tree);
    inorder(tree);
    postorder(tree);
    end = time(NULL);
    printf("遍历 %d 个数用时 %d s\n",ITEM_NUM,end-start);


    for(int i=0;i<=ITEM_NUM;i++)
    {
        //tree=delete_btree(tree,i);
        int index_success=-1;
        BTree su=success_btree( tree, i, &index_success);
        if(index_success!=-1)
        {
            printf("%d 的后继为 %d \n",i,su->key[index_success]);
        }
    }


/*
    start = time(NULL);
    for (int i = 0;i<=ITEM_NUM; i++)
    {
        int index = -1;
        BTree result = search(tree, i, &index);  //4782968
        if (result != NULL)
        {
            //printf("\nsearch: %d index: %d\n", result->key[index],index);
        }
        else
        {
            printf("\n未找到 %d \n");
            exit(EXIT_FAILURE);
        }
    }
    end = time(NULL);
    printf("递归查询 %d 个数用时 %d s\n",ITEM_NUM,end-start);

    start = time(NULL);
    for (int i = 0;i<=ITEM_NUM; i++)
    {
        int index = -1;
        BTree result = search_iterative(tree, i, &index);  //4782968
        if (result != NULL)
        {
            //printf("\nsearch: %d index: %d\n", result->key[index],index);
        }
        else
        {
            printf("\n未找到 %d \n");
            exit(EXIT_FAILURE);
        }
    }
    end = time(NULL);
    printf("非递归查询 %d 个数用时 %d s\n",ITEM_NUM,end-start);
*/
}

//目前问题  将8插入到了根节点  这是由于插入 11的时候 isleaf 错误,已纠正，原来是参数调用顺序错了，眼瞎。
//插入 6 后丢失树的信息，只剩下以8为根的结点  node_to_insert 的 parent 为 null
