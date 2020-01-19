#include<iostream>

class Edge
{
    public:
        int src;
        int dst;
        int wt;
};


class Graph
{
    public:
    int V, E;
    Edge *edge;

    Graph * createGraph (int e, int v)
    {
        Graph *graph = new Graph;
        graph->E = e;
        graph->V = v;
        grapg->edge = new Edge [E];
        return graph;
    }
};

class subset
{
    public:
        int parent;
        int rank;
};



int find ( )
{
}

int main()
{
}
 
