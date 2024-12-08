// version 2.1
#include <iostream>
#define FLT_MAX 2147483647
#include "Queue.cpp"
#include "Stack.cpp"
#include "LinkedList.cpp"
#include "ObjectClasses.cpp"
using namespace std;

struct GraphEdge
{
    long int from_vertex;
    long int to_vertex;
    float weight;
    Road data;
};
ostream &operator<<(ostream &os, GraphEdge &edge)
{
    if (!edge.data.is_closed)
        os << "(" << "From Intersection " << edge.data.from << ", " << "To Intersection " << edge.data.to << ", with Travel Time " << edge.weight << ")";
    return os;
}

struct GraphNode
{
    long int id;
    Intersection data;
};
ostream &operator<<(ostream &os, GraphNode &node)
{
    os << "Intersection " << node.data << endl;
    return os;
}

// template <class Intersection, class Road>
class Graph
{
public:
    LinkedList<GraphNode> vertices;
    LinkedList<LinkedList<GraphEdge>> connecting_edges;
    LinkedList<GraphEdge> blocked_roads;
    Graph(long int n = 0)
    {
        for (long int id = 0; id < n; id++)
        {
            GraphNode node{id, id + 65};
            vertices.append(node);
            connecting_edges.append(LinkedList<GraphEdge>());
        }
    }
    bool addEdge(long int from, long int to, float weight, Road new_data)
    {
        if (to < vertices.size && from < vertices.size)
        {
            connecting_edges[from].append(GraphEdge{from, to, weight, new_data});
            return true;
        }
        return false;
    }
    bool addEdge(Road new_data)
    {
        long int to = findVertexIndex(new_data.to);
        long int from = findVertexIndex(new_data.from);
        float weight = new_data.travel_time;
        long int already_exist = getEdgeIndex(to, from);
        if (already_exist == -1 && to >= 0 && from >= 0 && to < vertices.size && from < vertices.size)
        {
            connecting_edges[from].append(GraphEdge{from, to, weight, new_data});
            return true;
        }
        return false;
    }
    void addVertex(Intersection new_data)
    {
        long int id = vertices.size;
        vertices.append(GraphNode{id, new_data});
        connecting_edges.append(LinkedList<GraphEdge>());
    }

    void printGraph()
    {
        for (long int i = 0; i < vertices.size; i++)
        {
            cout << vertices[i];
            cout << "Connection Roads: \n";
            connecting_edges[i].display();
        }
    }
    void BFS(long int start_id)
    {
        GraphNode *start_node = nullptr;
        for (long int i = 0; i < vertices.size; i++)
        {
            if (vertices[i].id == start_id)
            {
                start_node = &vertices[i];
                break;
            }
        }

        bool visited[vertices.size] = {false};
        Queue<GraphNode *> q;
        q.enqueue(start_node);
        visited[start_node->id] = true;

        cout << "BFS Traversal: ";
        while (!q.isEmpty())
        {
            GraphNode *current_node = q.dequeue();
            cout << current_node->id << " ";

            for (long int i = 0; i < connecting_edges[findVertexIndex(current_node->id)].size; i++)
            {
                long int neighbor_id = connecting_edges[findVertexIndex(current_node->id)][i].to_vertex;
                if (!visited[findVertexIndex(neighbor_id)])
                {
                    visited[findVertexIndex(neighbor_id)] = true;
                    q.enqueue(&vertices[findVertexIndex(neighbor_id)]);
                }
            }
        }
        cout << endl;
    }
    void DFS(long int start_id)
    {
        GraphNode *start_node = nullptr;
        for (long int i = 0; i < vertices.size; i++)
        {
            if (vertices[i].id == start_id)
            {
                start_node = &vertices[i];
                break;
            }
        }

        if (!start_node)
        {
            cout << "Start node not found!" << endl;
            return;
        }

        bool visited[vertices.size] = {false};
        Stack<GraphNode *> s;
        s.push(start_node);

        cout << "DFS Traversal: ";
        while (!s.isEmpty())
        {
            GraphNode *current_node = s.pop();

            if (!visited[findVertexIndex(current_node->id)])
            {
                visited[findVertexIndex(current_node->id)] = true;
                cout << current_node->id << " ";
            }

            // Pushing unvisited neighbors onto stack
            for (long int i = 0; i < connecting_edges[findVertexIndex(current_node->id)].size; i++)
            {
                long int index = findVertexIndex(connecting_edges[findVertexIndex(current_node->id)][i].to_vertex);
                GraphNode *neighbor = &vertices[index];
                if (!visited[findVertexIndex(neighbor->id)])
                {
                    s.push(neighbor);
                }
            }
        }
        cout << endl;
    }
    long int findVertexIndex(Intersection data)
    {
        for (long int i = 0; i < vertices.size; i++)
        {
            if (vertices[i].data == data)
            {
                return i;
            }
        }
        return -1;
    }
    long int findVertexIndex(long int id)
    {
        for (long int i = 0; i < vertices.size; i++)
        {
            if (vertices[i].id == id)
            {
                return i;
            }
        }
        return -1;
    }
    long int findVertexID(Intersection data)
    {
        for (long int i = 0; i < vertices.size; i++)
        {
            if (vertices[i].data == data)
            {
                return vertices[i].id;
            }
        }
        return -1;
    }
    LinkedList<GraphEdge> getAdjacencyList(long int index)
    {
        return connecting_edges[index];
    }
    long int getEdgeIndex(long int from, long int to)
    {
        if (from < vertices.size)
        {
            for (long int i = 0; i < connecting_edges[from].size; i++)
            {
                if (connecting_edges[from][i].to_vertex == to)
                {
                    return i;
                }
            }
        }
        return -1;
    }
    long int getBlockedIndex(long int from, long int to)
    {
        if (from < vertices.size && to < vertices.size)
        {
            for (long int i = 0; i < blocked_roads.size; i++)
            {
                if (blocked_roads[i].from_vertex == from && blocked_roads[i].to_vertex == to)
                {
                    return i;
                }
            }
        }
        return -1;
    }
    GraphEdge getEdge(long int from, long int to)
    {
        long int i = getEdgeIndex(from, to);
        return connecting_edges[from][to];
    }
    bool removeEdge(long int from, long int to)
    {
        from = findVertexIndex(from), to = findVertexIndex(to);
        long int i = getEdgeIndex(from, to);
        if (from > 0 && i > 0)
        {
            connecting_edges[from].removeAtPosition(i);
            return true;
        }
        return false;
    }
    bool removeEdge(Road road)
    {
        long int from = findVertexIndex(road.from), to = findVertexIndex(road.to);
        long int i = getEdgeIndex(from, to);
        if (from > 0 && i > 0)
        {
            connecting_edges[from].removeAtPosition(i);
            return true;
        }
        return false;
    }
    bool removeVertex(long int id)
    {
        long int index = findVertexIndex(id);
        if (index >= 0)
        {
            vertices.removeAtPosition(index);
            connecting_edges.removeAtPosition(index);
            for (int to = 0; to < connecting_edges.size; to++)
            {
                for (int i = 0; i < connecting_edges[to].size; i++)
                {
                    if (connecting_edges[to][i].to_vertex == id)
                    {
                        connecting_edges[to].removeAtPosition(i);
                    }
                }
            }
            return true;
        }
        return false;
    }
    bool removeEdgeInter(Intersection from, Intersection to)
    {
        long int from_index = findVertexID(from), to_index = (findVertexID(to));
        from_index = findVertexIndex(from_index), to_index = findVertexIndex(to_index);
        long int i = getEdgeIndex(from_index, to_index);
        if (from >= 0 && i >= 0)
        {
            connecting_edges[from].removeAtPosition(i);
            return true;
        }
        return false;
    }
    bool removeVertexInter(Intersection data)
    {
        long int index = findVertexIndex(data);
        long int id = findVertexID(data);
        if (index >= 0)
        {
            vertices.removeAtPosition(index);
            connecting_edges.removeAtPosition(index);
            for (int to = 0; to < connecting_edges.size; to++)
            {
                for (int i = 0; i < connecting_edges[to].size; i++)
                {
                    if (connecting_edges[to][i].to_vertex == id)
                    {
                        connecting_edges[to].removeAtPosition(i);
                    }
                }
            }
            return true;
        }
        return false;
    }
    // Assuming your GraphEdge, GraphNode, and other classes are the same as above

    void findShortestPath(long int start_id, long int end_id)
    {
        if (start_id >= vertices.size || end_id >= vertices.size)
        {
            cout << "Invalid vertex ID(s)!" << endl;
            return;
        }

        long int n = vertices.size;

        float *distances = new float[n];
        long int *previous = new long int[n];
        bool *visited = new bool[n];

        for (long int i = 0; i < n; i++)
        {
            distances[i] = FLT_MAX;
            previous[i] = -1;
            visited[i] = false;
        }

        distances[start_id] = 0.0f;

        long int *queue = new long int[n];
        long int queue_size = 0;

        for (long int i = 0; i < n; i++)
            queue[queue_size++] = i;

        while (queue_size > 0)
        {
            long int current = -1;
            float min_distance = FLT_MAX;
            for (long int i = 0; i < queue_size; i++)
            {
                if (!visited[queue[i]] && distances[queue[i]] < min_distance)
                {
                    current = queue[i];
                    min_distance = distances[queue[i]];
                }
            }

            if (current == -1 || distances[current] == FLT_MAX)
            {
                break;
            }

            visited[current] = true;

            for (long int i = 0; i < queue_size; i++)
            {
                if (queue[i] == current)
                {
                    queue[i] = queue[--queue_size];
                    break;
                }
            }

            for (long int i = 0; i < connecting_edges[current].size; i++)
            {
                GraphEdge edge = connecting_edges[current][i];
                long int neighbor = edge.to_vertex;
                float new_distance = distances[current] + edge.weight;

                if (!visited[neighbor] && new_distance < distances[neighbor])
                {
                    distances[neighbor] = new_distance;
                    previous[neighbor] = current;
                }
            }
        }

        if (distances[end_id] == FLT_MAX)
        {
            cout << "No path exists between vertex " << start_id << " and vertex " << end_id << "." << endl;
        }
        else
        {
            cout << "Shortest path distance: " << distances[end_id] << endl;
            cout << "Path: ";

            LinkedList<Intersection> path;
            long int current = end_id;
            while (current != -1)
            {
                path.insertAtFirst(vertices[findVertexIndex(current)].data);
                current = previous[current];
            }

            for (long int i = 0; i < path.size; i++)
            {
                if (i > 0)
                    cout << " -> ";
                cout << path[i];
            }
            cout << endl;

            cout << "Edges in the path: ";
            current = start_id;
            for (long int i = 1; i < path.size; i++)
            {
                long int next = findVertexID(path[i]);
                for (long int j = 0; j < connecting_edges[current].size; j++)
                {
                    GraphEdge edge = connecting_edges[current][j];
                    if (edge.to_vertex == next)
                    {
                        cout << "(" << vertices[findVertexIndex(current)].data << " -> " << vertices[findVertexIndex(next)].data << ", weight=" << edge.weight << ") ";
                        break;
                    }
                }
                current = next;
            }
            cout << endl;
        }

        delete[] distances;
        delete[] previous;
        delete[] visited;
        delete[] queue;
    }
    bool blockRoad(char from, char to)
    {
        int from_id = findVertexID(from), to_id = findVertexID(to);
        int from_index = findVertexIndex(from), to_index = findVertexIndex(to);
        if (to_index != -1 && from_index != -1)
        {
            for (int i = 0; i < connecting_edges[from_index].size; i++)
            {
                if (connecting_edges[from_index][i].to_vertex == to_id)
                {
                    Road blocked_road = getEdge(from_id, to_id).data;
                    removeEdge(blocked_road);
                    float weight = blocked_road.travel_time;
                    long int already_exist = getBlockedIndex(to_id, from_id);
                    if (already_exist == -1 && to_index >= 0 && from_index >= 0 && to_index < vertices.size && from_index < vertices.size)
                    {
                        blocked_roads.append(GraphEdge{from_id, to_id, weight, blocked_road});
                        return true;
                    }
                    return false;
                }
            }
        }
    }
        bool unblockRoad(char from, char to)
    {
        int from_id = findVertexID(from), to_id = findVertexID(to);
        int from_index = findVertexIndex(from), to_index = findVertexIndex(to);
        if (to_index != -1 && from_index != -1)
        {
            int index=getBlockedIndex(from,to);
            Road unblock_road=blocked_roads[index].data;
            blocked_roads.removeAtPosition(index);
            addEdge(unblock_road);
        }
    }
};

// int main()
// {
//     Road r = Road('a', 'b', 0);
//     Graph g(6);
//     g.addEdge(0, 1, 2, r);
//     g.addEdge(0, 4, 2, r);
//     g.addEdge(1, 2, 5, r);
//     g.addEdge(1, 3, 7, r);
//     g.addEdge(2, 4, 3, r);
//     g.addEdge(2, 5, 8, r);
//     g.addEdge(3, 4, 9, r);
//     g.addEdge(3, 5, 10, r);
//     g.addEdge(4, 5, 11, r);
//     g.addEdge(4, 0, 1, r);
//     g.printGraph();
//     g.removeEdge(2, 4);
//     g.printGraph();
//     g.removeEdge(2, 4);
//     g.printGraph();
//     g.removeVertex(2);
//     g.printGraph();
//     g.BFS(4);
//     g.DFS(0);
//     g.findShortestPath(1,2);
//     g.findShortestPath(5,1);
//     g.findShortestPath(1,4);
//     g.findShortestPath(1,2);
//     g.findShortestPath(4,1);
//     g.findShortestPath(1,3);
//     g.findShortestPath(1,5);
//     g.findShortestPath(1,5);
//     return 0;
// }
