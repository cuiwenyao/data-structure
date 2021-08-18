
#define M 2

#include "BTree.c"

//一亿条数据
#define ITEM_NUM 10000000

//阶数增大但又不太大 则查询时间增大，其余时间减少

int main()
{
    printf("效率test 当前阶数为 %d \n", M);
    time_t start, end, t1, t2;

    start = time(NULL);
    BTree tree = BTree_Init();
    for (int i = 0; i <= ITEM_NUM; i++)
    {
        tree = insert(tree, i);
    }
    end = time(NULL);
    int time_=end-start;
    printf("插入 %d 个数用时 %d s\n", ITEM_NUM, time_);

    start = time(NULL);
    preorder(tree);
    inorder(tree);
    postorder(tree);
    end = time(NULL);
    printf("遍历 %d 个数用时 %d s\n", ITEM_NUM, end - start);

    start = time(NULL);
    for (int i = 0; i <= ITEM_NUM; i++)
    {
        int index = -1;
        BTree result = search(tree, i, &index); //4782968
        if (result != NULL)
        {
            //printf("\nsearch: %d index: %d\n", result->key[index], index);
        }
        else
        {
            printf("\n未找到 %d \n");
            exit(EXIT_FAILURE);
        }
    }
    end = time(NULL);
    printf("递归查询 %d 个数用时 %d s\n", ITEM_NUM, end - start);

    start = time(NULL);
    for (int i = 0; i <= ITEM_NUM; i++)
    {
        int index = -1;
        BTree result = search_iterative(tree, i, &index); //4782968
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
    printf("非递归查询 %d 个数用时 %d s\n", ITEM_NUM, end - start);

    printf("delete test\n");
    start = time(NULL);
    t1 = time(NULL);
    for (int i = 0; i <= ITEM_NUM; i++)
    {

        t2 = time(NULL);
        if (t2 - t1 == 1)
        {
            printf("已删除 %f \n", i * 1.0 / ITEM_NUM * 100.0);
            t1 = t2;
        }

        tree = delete_btree(tree, false, NULL, -1, i);
        int index = -1;
        BTree result=NULL ;//= search(tree, i, &index); //4782968
        if (result != NULL)
        {
            printf("\n 删除失败-----------search: %d index: %d\n", result->key[index], index);
            exit(EXIT_FAILURE);
        }
        else
        {
            //inorder(tree);
            //printf("\n");
        }
    }
    end = time(NULL);
    printf("删除 %d 个数用时 %d s\n", ITEM_NUM, end - start);
    printf("delete test finish\n");
}
