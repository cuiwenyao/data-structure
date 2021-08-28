#include "sort.h"

void printf_result(int *begin, int *end)
{
    for (; begin != end; begin++)
        printf("%d ", *begin);
    printf("%d\n", *begin);
}

//直接插入排序
void direct_insert_sort(int *begin, int *end)
{
    printf("direct_insert_sort\n");
    int num = end - begin + 1;
    int *a = begin;
    for (int i = 1; i <= num - 1; i++)
    {
        //将a[i]放在前面合适的地方
        int temp = a[i];
        int j = 0;
        for (j = i - 1; j >= 0 && a[j] > temp; j--)
            a[j + 1] = a[j];
        a[j + 1] = temp;
    }
    return;
}
//折半插入排序
void half_insert_sort(int *begin, int *end)
{
    printf("half_insert_sort\n");
    int num = end - begin + 1;
    int *a = begin;
    for (int i = 1; i <= num - 1; i++)
    {
        //折半查找插入的位置
        int temp = a[i];
        int low = 0;
        int high = i - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (a[mid] > temp)
                high = mid - 1;
            else
                low = mid + 1;
        }
        for (int j = i; j >= low + 1; j--)
            a[j] = a[j - 1];
        a[low] = temp;
    }
    return;
}
//希尔排序
void shell_sort(int *begin, int *end)
{
    printf("shell_sort\n");
    int num = end - begin + 1;
    int step = num;
    int *a = begin;
    do
    {
        step /= 2;
        //分段排序 直接插入排序
        for (int start = 0; start <= step - 1; start++)
        {
            //每一段的起始位start
            for (int i = start + step; i <= num - 1; i += step)
            {
                //将a[i]放在前面合适的地方
                int temp = a[i];
                int j = start;
                for (j = i - step; j >= start && a[j] > temp; j -= step)
                {
                    a[j + step] = a[j];
                }
                a[j + step] = temp;
            }
        }
    } while (step != 1);
    return;
}
//冒泡排序
void bubble_sort(int *begin, int *end)
{
    printf("bubble_sort\n");
    int num = end - begin + 1;
    int *a = begin;
    for (int i = 0; i <= num - 2; i++)
    {
        for (int j = 0; j <= num - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    return;
}
//快速排序
void quick_sort(int *begin, int *end)
{
    printf("quick_sort\n");
    //选择一个基准，不断地从后向前，从前向后进行交换
    int num = end - begin + 1;
    int *a = begin;
    if (num > 1)
    {
        int high = num - 1;
        int low = 0;
        int mid = a[0];
        while (low < high)
        {
            //从右向左找
            while (low < high && a[high] >= mid)
                high--;
            a[low] = a[high];
            while (low < high && a[low] <= mid)
                low++;
            a[high] = a[low];
        }
        a[low] = mid;
        quick_sort(begin, begin + low - 1);
        quick_sort(begin + low + 1, end);
    }
    return;
}

//简单选择排序
void simple_select_sort(int *begin, int *end)
{
    printf("simple_select_sort\n");
    //每一次从乱序的序列中选择一个最小的放在顺序序列的最后面。
    int num = end - begin + 1;
    int *a = begin;
    for (int i = 0; i <= num - 2; i++)
    {
        //从 i - num-i中选择一个最下的放在i
        int min_index = i;
        for (int j = i; j <= num - 1; j++)
            if (a[j] < a[min_index])
                min_index = j;
        int temp = a[i];
        a[i] = a[min_index];
        a[min_index] = temp;
    }
}
//堆排序
void heap_sort(int *begin, int *end)
{
    printf("heap_sort\n");
    int num = end - begin + 1;
    //首先建立大根堆，即对 n/2 - 1 为根的子树进行调整。
    for (int i = num / 2; i >= 0; i--)
        heap_adjust(begin, end, i, num);
    //循环输出最大值，并调整堆。
    for (int i = 0; i <= num - 1; i++)
    {
        int temp = begin[0];
        begin[0] = begin[num - i - 1];
        begin[num - i - 1] = temp;
        heap_adjust(begin, end, 0, num - i - 1);
    }
}
//调整heap的一个子树
void heap_adjust(int *begin, int *end, int seq, int len)
{
    //将树根与其最大的孩子进行交换，递归直到叶子。
    int temp = begin[seq];
    for (int i = seq * 2 + 1; i < len; i = i * 2 + 1)
    {
        //指向大的孩子
        if (i + 1 < len && begin[i] < begin[i + 1])
            i++;
        if (temp < begin[i])
        {
            begin[seq] = begin[i];
            seq = i;
        }
        else if (temp >= begin[i])
            break;
    }
    begin[seq] = temp;
}
//归并排序
void merge_sort(int *begin, int *end)
{
    int num = end - begin + 1;
    if (num > 1)
    {
        int mid = num / 2;
        merge_sort(begin, begin + mid - 1);
        merge_sort(begin + mid, end);
        merge(begin, end);
    }
}
//归并 归并low-mid mid+1-high
void merge(int *begin, int *end)
{
    //即将传进来的数组进行排序。
    int num = end - begin + 1;
    int mid = num / 2;
    // 0-mid-1 mid-end
    int num_a = mid;
    int num_b = num - mid;
    int *a = begin;
    int *b = begin + num_a;
    int *c = (int *)malloc(num * sizeof(int));
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < num_a && j < num_b)
        if (a[i] <= b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    //将剩下的全部放入c中
    if (i < num_a)
        while (i < num_a)
            c[k++] = a[i++];
    else
        while (j < num_b)
            c[k++] = b[j++];
    for (k = 0; k <= num - 1; k++)
        begin[k] = c[k];
}
//桶排序
void bucket_sort(int *begin, int *end)
{
    printf("bucket_sort\n");
    //建立一个桶数组，将元素放在对应的桶中，取出。
    //就好像统计每一个元素的个数并根据该信息创造出来一个一摸一样的元素序列。
    int num = end - begin + 1;
    int max = INT_MIN;
    for (int i = 0; i <= num - 1; i++)
        if (max < begin[i])
            max = begin[i];
    int *bucket = (int *)malloc((max + 1) * sizeof(int));
    memset(bucket, 0, (max + 1) * sizeof(int));
    for (int i = 0; i <= num - 1; i++)
        bucket[begin[i]]++;
    num = 0;
    for (int i = 0; i <= max; i++)
        for (int j = 0; j <= bucket[i] - 1; j++)
            begin[num++] = i;
}
//基数排序
void radix_sort(int *begin, int *end)
{
    printf("radix_sort\n");
    //对关键字的每一位进行依次桶排序，从低位到高位。
    int num = end - begin + 1;
    int max = INT_MIN;
    for (int i = 0; i <= num - 1; i++)
        if (max < begin[i])
            max = begin[i];
    int radix[10];
    int *output = (int *)malloc(num * sizeof(int));
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        memset(radix, 0, 10 * sizeof(int));
        memset(output, 0, num * sizeof(int));
        for (int i = 0; i <= num - 1; i++) //{2, 6, 4, 1, 3, 7, 9, 45, 4, 23, 0};
            radix[(begin[i] / exp) % 10]++;
        //重组radix,令其代表其数应该在的位置。
        for (int i = 1; i <= 9; i++)
            radix[i] += radix[i - 1];
        //将排序好的数输出
        for (int i = num - 1; i >= 0; i--)
        {
            output[(radix[(begin[i] / exp) % 10]--) - 1] = begin[i];
        }
        //保存输出
        memcpy(begin, output, num * sizeof(int));
    }
}