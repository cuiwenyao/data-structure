#include "graph.h"

//图不可以是一个空图
//初始化一个图
Graph init(int vertex_num)
{
    Graph graph = (Graph)malloc(sizeof(struct _GRAPH));
    graph->edge_num = 0;
    graph->vertex_num = 0;
    memset(graph->matrix, 0, sizeof(graph->matrix));
    graph = random_fill_graph(graph, vertex_num);
    return graph;
}
Graph random_fill_graph(Graph graph, int vertex_num)
{
    srand(time(NULL));
    int totle_vertex_num = vertex_num + graph->vertex_num;
    for (int i = 1; i <= vertex_num; i++)
    {
        int key = rand() % VERTEX_MAX;
        Vertex v = (Vertex)malloc(sizeof(struct _VERTEX));
        if (!v)
            exit(EXIT_FAILURE);
        v->key = key;
        graph->vertex[graph->vertex_num] = v;
        int source = graph->vertex_num++;
        int degree = 0;
        if (totle_vertex_num > 1)
            degree = rand() % (totle_vertex_num - 1) + 1;
        for (int j = 1; j <= degree; j++)
        {
            int destination = rand() % (totle_vertex_num - 1);
            if (destination != source)
            {
                if (graph->matrix[source][destination] == 0)
                {
                    graph->matrix[source][destination] = 1;
                    graph->matrix[destination][source] = 1;
                    graph->edge_num++;
                }
            }
        }
    }
    return graph;
}
//图的遍历
//深度优先搜索 DFS 递归
void DFS(Graph graph)
{
    printf("DFS\n");
    //任意找一个顶点开始进行递归深度搜索。
    int is_sacn[VERTEX_MAX];
    memset(is_sacn, 0, sizeof(is_sacn));
    DFS_Vertex(graph, 0, is_sacn);
    printf("\n");
}
void DFS_Vertex(Graph graph, int v_seq, int is_sacn[VERTEX_MAX])
{
    //如果没有被扫描过则输出
    //扫描其所有相连的 访问一个没有被访问过的 若所有与之相连接的结点都被访问过 则返回
    if (!is_sacn[v_seq])
    {
        is_sacn[v_seq] = 1;
        printf("%d ", graph->vertex[v_seq]->key);
    }
    for (int i = 0; i <= graph->vertex_num - 1; i++)
    {
        if (graph->matrix[v_seq][i] == 1 && !is_sacn[i])
        {
            DFS_Vertex(graph, i, is_sacn);
        }
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
        //访问这个结点 可能有多个结点与该节点相连则该节点就入栈多次 但是访问一次即可
        if (!is_scan[seq])
            printf("%d ", graph->vertex[seq]->key);
        else
            continue;
        is_scan[seq] = 1;
        //将这个结点所连接的节点中未访问过的结点push
        for (int i = 0; i <= graph->vertex_num - 1; i++)
        {
            if (graph->matrix[seq][i] == 1 && !is_scan[i])
                s.push(i);
        }
    }
    printf("\n");
}
//广度优先搜索
void BFS(Graph graph)
{
    printf("BFS\n");
    //层次搜索 和树一样
    std::deque<int> q;
    int is_scan[VERTEX_MAX];
    memset(is_scan, 0, sizeof(is_scan));
    q.push_back(0);
    while (!q.empty())
    {
        int seq = q.front();
        q.pop_front();
        if (!is_scan[seq])
            printf("%d ", graph->vertex[seq]->key);
        else
            continue;
        is_scan[seq] = 1;
        //将下一层入队
        for (int i = 0; i <= graph->vertex_num - 1; i++)
        {
            if (graph->matrix[seq][i] == 1 && !is_scan[i])
                q.push_back(i);
        }
    }
    printf("\n");
}
