#include "graph.cpp"

int main()
{
    Graph graph = init(10);
    DFS(graph);
    DFS_none_recursive(graph);
    BFS(graph);
    return 0;
}