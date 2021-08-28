//无向图 邻接矩阵

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stack>
#include <deque>

#define VERTEX_MAX 100

typedef struct _VERTEX
{
    int key;
} * Vertex;

typedef struct _GRAPH
{
    //顶点集合
    //顶点数量
    //边的数量
    //边的集合 使用邻接矩阵或者邻接表进行表示
    Vertex vertex[VERTEX_MAX];
    int vertex_num;
    int edge_num;
    int matrix[VERTEX_MAX][VERTEX_MAX];
} * Graph;

//图不可以是一个空图
//初始化一个图
Graph init(int vertex_num);
//自动随机填充图 vertex_num 个顶点
Graph random_fill_graph(Graph graph, int vertex_num);

//图的遍历
//深度优先搜索 DFS
void DFS(Graph graph);
void DFS_Vertex(Graph graph, int v_seq, int is_sacn[VERTEX_MAX]);
//广度优先搜索
void BFS(Graph graph);

#endif