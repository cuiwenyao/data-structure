#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*
1. 内部排序
    1. 插入排序
        1. 直接插入排序
        2. 折半插入排序
        3. 希尔排序
    2. 交换排序
        1. 冒泡排序
        2. 快速排序
    3. 选择排序
        1. 简单选择排序
        2. 堆排序
    4. 归并排序
    5. 基数排序
2. 外部排序
    1. 
*/

void printf_result(int *begin, int *end);
//直接插入排序
void direct_insert_sort(int *begin, int *end);
//折半插入排序
void half_insert_sort(int *begin, int *end);
//希尔排序
void shell_sort(int *begin, int *end);

//冒泡排序
void bubble_sort(int *begin, int *end);
//快速排序
void quick_sort(int *begin, int *end);

//简单选择排序
void simple_select_sort(int *begin, int *end);
//堆排序
void heap_sort(int *begin, int *end);
//调整heap的一个子树
void heap_adjust(int *begin, int *end, int seq, int len);

//归并排序
void merge_sort(int *begin, int *end);
//归并 归并low-mid mid+1-high
void merge(int *begin, int *end);

//桶排序
void bucket_sort(int *begin, int *end);
//基数排序
void radix_sort(int *begin, int *end);

#endif