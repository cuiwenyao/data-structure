//无向图 邻接表

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <memory.h>
#include <stack>
#include <deque>

#define VERTEX_MAX 100

typedef struct _ENODE
{
    int seq;
    struct _ENODE *next;
} * Enode;

typedef struct _VERTEX
{
    int key;          //顶点数据
    Enode first_edge; //该顶点的第一个弧
} * Vertex;

typedef struct _GRAPH
{
    //邻接表 图中存放顶点 每一个顶点有一个链表将自己相连的顶点存储到链表中
    //顶点数目
    //边的数目
    //顶点
    int vertex_num;
    int edge_num;
    Vertex vertex[VERTEX_MAX];
} * Graph;

//图不可以是一个空图
//初始化一个图
Graph init(int vertex_num);
//自动随机填充图 vertex_num 个顶点
Graph random_fill_graph(Graph graph, int vertex_num);
void append_table(Graph graph, int source, int insert);
//图的遍历
//深度优先搜索 DFS
void DFS(Graph graph);
void DFS_Vertex(Graph graph, int v_seq, int is_scan[VERTEX_MAX]);
//广度优先搜索
void BFS(Graph graph);
void BFS_Vertex(Graph graph, int v_seq, int is_scan[VERTEX_MAX]);
#endif