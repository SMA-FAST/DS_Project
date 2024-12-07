// version 2.1
#include <iostream>
#include "Queue.cpp"
//#include "Stack.cpp"
#include "LinkedList.cpp"
using namespace std;

template <class EgdeObject>
struct GraphEdge
{
    long int from_vertex;
    long int to_vertex;
    float weight;
    EgdeObject data;
};
template <class EgdeObject>
ostream &operator<<(ostream &os, GraphEdge<EgdeObject> &edge)
{
    os << "(" << "From Vertex " << edge.from_vertex << ", " << "To Vertex " << edge.to_vertex << ", Weight " << edge.weight << ")";
    return os;
}

template <class NodeObject>
struct GraphNode
{
    long int id;
    NodeObject data;
};
template <class NodeObject>
ostream &operator<<(ostream &os, GraphNode<NodeObject> &node)
{
    os<< "Vertex " << node.id << endl;
    return os;
}

template <class NodeObject,class EdgeObject>
class Graph
{
    LinkedList<GraphNode<NodeObject>> vertices;
    LinkedList<LinkedList<GraphEdge<EdgeObject>>> conneting_edges;
public:
    Graph(int n)
    {
        for (int i = 0; i < n; i++)
        {
            GraphNode<NodeObject> node{i};
            vertices.append(node);
            conneting_edges.append(LinkedList<GraphEdge<EdgeObject>>());
        }
    }
    void addEdge(int from, int to, float weight)
    {
        if (to < vertices.size && from < vertices.size)
        {
            conneting_edges[from].append(GraphEdge<EdgeObject>{from,to, weight});
        }
    }
    void addVertex(NodeObject new_data)
    {
        long int id = vertices.size;
        vertices.append(GraphNode{id,new_data});
        conneting_edges.append(LinkedList<GraphEdge<EdgeObject>>());
    }
    void printGraph()
    {
        for (int i = 0; i < vertices.size; i++)
        {
            cout<<vertices[i];
            cout<<"Connection Edges: \n";
            conneting_edges[i].display();
        }
    }
    void BFS(int start_id)
    {
        GraphNode<NodeObject> *start_node = &vertices[start_id];

        if (!start_node)
        {
            cout << "Start node not found!" << endl;
            return;
        }
        
        bool visited[vertices.size] = {false};
        Queue<GraphNode<NodeObject> *> q;
        q.enqueue(start_node);
        visited[start_node->id] = true;

        cout << "BFS Traversal: ";
        while (!q.isEmpty())
        {
            GraphNode<NodeObject> *current_node = q.dequeue();
            cout << current_node->id << " ";

            for (int i = 0; i < conneting_edges[current_node->id].size; i++)
            {
                long int neighbor_id = conneting_edges[current_node->id][i].to_vertex;
                if (!visited[neighbor_id])
                {
                    visited[neighbor_id] = true;
                    q.enqueue(&vertices[neighbor_id]);
                }
            }
        }
        cout << endl;
    }
};
int main()
{
    Graph<string,string> g(6);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 8);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 10);
    g.addEdge(4, 5, 11);
    g.addEdge(4,0,1);
    g.printGraph();
    g.BFS(4);
    return 0;
}
