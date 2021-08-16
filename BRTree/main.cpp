#include "BRTree.cpp"
#include <vector>
#define MAX_NUM 10000

#define RANGE 1000000

int test()
{
    std::vector<int> v; //= {91, 23, 74, 26, 15, 94, 13, 21, 10, 52, 60, 92, 73, 8, 47, 69, 80, 97, 48, 55};
    BRTree tree;
    tree = init(tree);

    srand(time(NULL));

    for (int i = 0; i <= MAX_NUM - 1; i += 1)
    {
        int key = rand() % RANGE;
        //int key = v.at(i);
        if (!search(tree, key))
        {
            v.push_back(key);
            tree = insert(tree, key);
        }
    }
    //printf("\n");
    //print_brtree(tree, 0, -1);
    //printf("\n");
    //inorder(tree);
    //printf("\n");

    for (int i = 0; i <= v.size() - 1; i += 1)
    {
        //printf("删除 %d \n", v.at(i));
        tree = delete_brtree(tree, v.at(i));
        //printf("\n");
        //print_brtree(tree, 0, -1);
        if (check_balck_num_valid(tree))
            ; //printf("-------------------------------------合法--------------------------------\n");
        else
        {
            printf("-------------------------------------不合法--------------------------------\n");
            for (int i = 0; i <= v.size() - 1; i++)
            {
                printf("%d, ", v.at(i));
            }

            exit(EXIT_FAILURE);
        }
    }
    //printf("\n");
    //print_brtree(tree, 0, -1);
    //printf("\n");
    //for (int i = 0; i <= v.size() - 1; i++)
    //{
    //printf("%d, ", v.at(i));
    //}
    return -1;
}

int main()
{
    while (1)
    {
        test();
        printf("text pass''''''''''''''''''''''''''''''''''''\n");
    }
}
