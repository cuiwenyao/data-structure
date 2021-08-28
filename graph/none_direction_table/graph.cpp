#include "graph.h"

//图不可以是一个空图
//初始化一个图
Graph init(int vertex_num)
{
    Graph graph = (Graph)malloc(sizeof(struct _GRAPH));
    graph->edge_num = 0;
    graph->vertex_num = 0;
    memset(graph->vertex, 0, sizeof(graph->vertex));
    graph = random_fill_graph(graph, vertex_num);
    return graph;
}
Graph random_fill_graph(Graph graph, int vertex_num)
{
    srand(time(NULL));
    //int totle_vertex_num = vertex_num + graph->vertex_num;
    //随机产生一个顶点 随机产生一个度 随机产生每一个度连接的顶点 更新顶点的邻接表
    for (int i = 1; i <= vertex_num; i++)
    {
        int source = graph->vertex_num++;
        graph->vertex[source] = (Vertex)malloc(sizeof(struct _VERTEX));
        graph->vertex[source]->first_edge = NULL;
        int destination = 0;
        int key = rand() % VERTEX_MAX;
        graph->vertex[source]->key = key;
        int degree = 0;
        if (source != 0)
            degree = rand() % (source) + 1; //1 - source-1
        else
            continue;
        for (int i = 1; i <= degree; i++)
        {
            destination = rand() % (source);
            //更新source的邻接表
            append_table(graph, source, destination);
            //更新destination的邻接表
            append_table(graph, destination, source);
        }
    }
    return graph;
}
void append_table(Graph graph, int source, int insert)
{
    //将 source 的邻接表插入一位 insert
    Enode p = graph->vertex[source]->first_edge;
    if (!p)
    {
        Enode e = (Enode)malloc(sizeof(struct _ENODE));
        e->next = NULL;
        e->seq = insert;
        graph->vertex[source]->first_edge = e;
        return;
    }
    //p不空，append
    if (p->seq == insert)
        return;
    while (p->next)
    {
        p = p->next;
        //邻接表中已经存在 insert 了，不需要存入
        if (p->seq == insert)
            return;
    }
    Enode e = (Enode)malloc(sizeof(struct _ENODE));
    e->next = NULL;
    e->seq = insert;
    p->next = e;
    return;
}
//图的遍历
//深度优先搜索 DFS 递归
void DFS(Graph graph)
{
    printf("DFS\n");
    //从0开始遍历邻接表
    int is_scan[VERTEX_MAX];
    memset(is_scan, 0, sizeof(is_scan));
    DFS_Vertex(graph, 0, is_scan);
    printf("\n");
}
void DFS_Vertex(Graph graph, int v_seq, int is_scan[VERTEX_MAX])
{
    //如果没有被扫描过则输出
    //扫描其所有相连的 访问一个没有被访问过的 若所有与之相连接的结点都被访问过 则返回
    if (!is_scan[v_seq])
        printf("%d ", graph->vertex[v_seq]->key);
    is_scan[v_seq] = 1;
    Enode p = graph->vertex[v_seq]->first_edge;
    while (p)
    {
        //遍历邻接表
        if (!is_scan[p->seq])
            DFS_Vertex(graph, p->seq, is_scan);
        p = p->next;
    }
}
//非递归遍历
void DFS_none_recursive(Graph graph)
{
    printf("DFS_none_recursive\n");
    //将遇到的每一个未访问过的结点放入栈中 依次弹出访问 直到栈空
    int is_scan[VERTEX_MAX];
    memset(is_scan, 0, sizeof(is_scan));
    std::stack<int> s;
    s.push(0);
    while (!s.empty())
    {
        int seq = s.top();
        s.pop();
        if (!is_scan[seq])
        {
            is_scan[seq] = 1;
            printf("%d ", graph->vertex[seq]->key);
        }
        //将临界表内元素全部push
        Enode p = graph->vertex[seq]->first_edge;
        while (p)
        {
            if (!is_scan[p->seq])
                s.push(p->seq);
            p = p->next;
        }
    }
    printf("\n");
}

//广度优先搜索 递归
void BFS(Graph graph)
{
    printf("BFS\n");
    int is_scan[VERTEX_MAX];
    memset(is_scan, 0, sizeof(is_scan));
    std::deque<int> q;
    q.push_back(0);
    while (!q.empty())
    {
        int seq = q.front();
        q.pop_front();
        if (!is_scan[seq])
            printf("%d ", graph->vertex[seq]->key);
        is_scan[seq] = 1;
        Enode p = graph->vertex[seq]->first_edge;
        while (p)
        {
            if (!is_scan[p->seq])
                q.push_back(p->seq);
            p = p->next;
        }
    }
    printf("\n");
}
