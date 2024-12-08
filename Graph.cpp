// version 2.1
#include <iostream>
#include "Queue.cpp"
#include "Stack.cpp"
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
    os << "Vertex " << node.id << endl;
    return os;
}

template <class NodeObject, class EdgeObject>
class Graph
{
public:
    LinkedList<GraphNode<NodeObject>> vertices;
    LinkedList<LinkedList<GraphEdge<EdgeObject>>> conneting_edges;

    Graph(int n = 0)
    {
        for (int id = 0; id < n; i++)
        {
            GraphNode<NodeObject> node{id};
            vertices.append(node);
            conneting_edges.append(LinkedList<GraphEdge<EdgeObject>>());
        }
    }
    bool addEdge(int from, int to, float weight, EdgeObject new_data = EdgeObject())
    {
        
        if (to < vertices.size && from < vertices.size)
        {
            conneting_edges[from].append(GraphEdge<EdgeObject>{from, to, weight, new_data});
            return true;
        }
        return false;
    }
    void addVertex(NodeObject new_data = NodeObject())
    {
        long int id = vertices.size;
        vertices.append(GraphNode{id, new_data});
        conneting_edges.append(LinkedList<GraphEdge<EdgeObject>>());
    }

    void printGraph()
    {
        for (int i = 0; i < vertices.size; i++)
        {
            cout << vertices[i];
            cout << "Connection Edges: \n";
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
    int findVertexIndex(NodeObject data)
    {
        for (int i = 0; i < vertices.size; i++)
        {
            if (vertices[i].data == data)
            {
                return i;
            }
        }
        return -1;
    }
    int findVertexIndex(int id)
    {
        for (int i = 0; i < vertices.size; i++)
        {
            if (vertices[i].id == id)
            {
                return i;
            }
        }
        return -1;
    }
    int findVertexID(NodeObject data)
    {
        for (int i = 0; i < vertices.size; i++)
        {
            if (vertices[i].data == data)
            {
                return vertices[i].id;
            }
        }
        return -1;
    }
    LinkedList<GraphEdge<EdgeObject>> getAdjacencyList(int index)
    {
        return conneting_edges[index];
    }
    int getEdgeIndex(int from, int to)
    {
        if (from < vertices.size)
        {
            for (int i = 0; i < vertices.size; i++)
            {
                if (conneting_edges[from][i].to_vertex == to)
                {
                    return i;
                }
            }
        }
        return -1;
    }
    GraphEdge<EdgeObject> getEdge(int from, int to)
    {
        int i = getEdgeIndex(from, to);
        return conneting_edges[from][to];
    }
    bool removeEdge(int from, int to)
    {
        from = findVertexIndex(from), to = findVertexIndex(to);
        int i = getEdgeIndex(from, to);
        if (from > 0 && i > 0)
        {
            conneting_edges[from].removeAtPosition(i);
            return true;
        }
        return false;
    }
    bool removeEdge(NodeObject from, NodeObject to)
    {
        int from_index = findVertexID(from), to_index = (findVertexID(to));
        from_index = findVertexIndex(from_index), to_index = findVertexIndex(to_index);
        int i = getEdgeIndex(from_index, to_index);
        if (from >= 0 && i >= 0)
        {
            conneting_edges[from].removeAtPosition(i);
            return true;
        }
        return false;
    }
    bool removeVertex(int id)
    {
        int index = findVertexIndex(id);
        if(index>=0)
        {
        vertices.removeAtPosition(index);
        conneting_edges.removeAtPosition(index);
        return true;
        }
        return false;
    }
        bool removeVertex(NodeObject data)
    {
        int index = findVertexIndex(data);
        if(index>=0)
        {
        vertices.removeAtPosition(index);
        conneting_edges.removeAtPosition(index);
        return true;
        }
        return false;
    }
};

int main()
{
    Graph<char, string> g(6);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(2, 5, 8);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 10);
    g.addEdge(4, 5, 11);
    g.addEdge(4, 0, 1);
    g.printGraph();
    g.removeEdge(2, 4);
    g.printGraph();
    g.removeEdge(2, 4);
    g.printGraph();
    g.removeVertex(2);
    g.printGraph();
    g.BFS(4);
    return 0;
}
