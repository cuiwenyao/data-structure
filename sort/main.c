#include "sort.c"

int main()
{
    int num[] = {2, 6, 4, 1, 3, 7, 9, 45, 4, 23, 0};
    //direct_insert_sort(num, num + 10);
    //half_insert_sort(num, num + 10);
    //shell_sort(num,num+10);
    //bubble_sort(num,num+10);
    //quick_sort(num,num+10);
    //simple_select_sort(num,num+10);
    //heap_sort(num, num + 10);
    //merge_sort(num,num+10);
    //bucket_sort(num,num+10);
    radix_sort(num, num + 10);
    printf_result(num, num + 10);
}