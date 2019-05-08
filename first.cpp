#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
using namespace std;


struct Edge
{
    int flow, capacity;
    // start vertex as u and end vertex as v.
    int origin, destination;

    Edge(int current_flow, int capacity, int origin, int destination)
    {
        this->flow = current_flow;
        this->capacity = capacity;
        this->origin = origin;
        this->destination = destination;
    }
};

// Represent a Vertex
struct Vertex
{
    int id;

    Vertex(int id)
    {
        this->id = id;
    }
};

class Network
{
    int num_vertex, num_suppliers, num_edges;
    vector<Vertex> vertex_list;
    vector<Edge> edge_list;
    vector<int> excessList, heightsList;

public:
    Network(int numSuppliers, int numStoring, int numConnections);   // Network Constructor
    void setConnection( int u, int v, int capacity);
    void freeNetwork();
    void relabel(int u);
    bool push(int u);
    void preflowInitializer(int source);
    int getMaxFlow(int s);
    void updateTranspostEdgeFlow(int i, int flow);
    int vertexOverflow();
    void print();
};
    Network::Network(int numSuppliers, int numStoring, int numConnections)  {
        int i;
        this->num_vertex = numSuppliers + 2*numStoring + 2;
        this->num_suppliers = numSuppliers;
        this->num_edges = numConnections + numStoring + numSuppliers;

        for (i=0; i<this->num_vertex; i++) {
            this->excessList.push_back(0);
            this->heightsList.push_back(0);
        }
    }

    void Network::setConnection( int u, int v, int capacity) {
        Edge connection = Edge(0, capacity,u,v);
        edge_list.push_back(connection);
    }

    void Network::preflowInitializer(int source)
{
    // Making h of source Vertex equal to no. of vertices
    // Height of other vertices is 0.
    heightsList[source] = num_vertex;

    //
    for (int i = 0; (unsigned) i < edge_list.size(); i++)
    {
        // If current edge goes from source
        if (edge_list[i].origin == source)
        {
            // Flow is equal to capacity
            edge_list[i].flow = edge_list[i].capacity;

            // Initialize excess flow for adjacent v
            excessList[edge_list[i].destination] += edge_list[i].flow;

            // Add an edge from v to s in residual graph with
            // capacity equal to 0
            edge_list.push_back(Edge(-edge_list[i].flow, 0, edge_list[i].destination, source));
        }
    }
}

int Network::vertexOverflow()
{

    for (int i = 2; i < num_vertex ; i++)
       if (excessList[i] > 0)
            return i;

    // -1 if no overflowing Vertex
    return -1;
}

// Update reverse flow for flow added on ith Edge
void Network::updateTranspostEdgeFlow(int i, int flow)
{
    int u = edge_list[i].destination, v = edge_list[i].origin;

    for (int j = 0; (unsigned) j < edge_list.size(); j++)
    {
        if (edge_list[j].destination == v && edge_list[j].origin == u)
        {
            edge_list[j].flow -= flow;
            return;
        }
    }

    // adding reverse Edge in residual graph
    Edge e = Edge(0, flow, u, v);
    edge_list.push_back(e);
}

bool Network::push(int u)
{
// Traverse through all edges to find an adjacent (of u)
// to which flow can be pushed
for (int i = 0; (unsigned) i < edge_list.size(); i++)
{
    // Checks u of current edge is same as given
    // overflowing vertex
    if (edge_list[i].origin == u)
    {
        // if flow is equal to capacity then no push
        // is possible
        if (edge_list[i].flow == edge_list[i].capacity)
            continue;

        // Push is only possible if height of adjacent
        // is smaller than height of overflowing vertex
        if (heightsList[u] > heightsList[edge_list[i].destination])
        {
            // Flow to be pushed is equal to minimum of
            // remaining flow on edge and excess flow.
            int flow = min(edge_list[i].capacity - edge_list[i].flow,
                           excessList[u]);
            // Reduce excess flow for overflowing vertex
            excessList[u] -= flow;

            // Increase excess flow for adjacent
            excessList[edge_list[i].destination] += flow;

            // Add residual flow (With capacity 0 and negative
            // flow)
            edge_list[i].flow += flow;

            updateTranspostEdgeFlow(i, flow);

            return true;
        }
    }
}
return false;
}

    void Network::relabel(int u)
{
    // Initialize minimum height of an adjacent
    int minHeight = 2* this->num_vertex;


    for (int i = 0; (unsigned) i < edge_list.size(); i++)
    {
        if (edge_list[i].origin == u)
        {
            // if flow is equal to capacity then no
            // relabeling
            if (edge_list[i].flow == edge_list[i].capacity)
                continue;

            // Update minimum height
            if (heightsList[edge_list[i].destination] < minHeight)
            {
                minHeight = heightsList[edge_list[i].destination];

                // updating height of u
                heightsList[u] = minHeight + 1;
            }
        }
    }
}

void Network::print() {
    int i;
    for (i=0; i< this->num_edges; i++) {
        printf("%d-%d\n", this->edge_list[i].origin, this->edge_list[i].destination);
    }
}

int Network::getMaxFlow(int s)
{

    preflowInitializer(s);
    // loop untill none of the Vertex is in overflow
    while (vertexOverflow() != -1)
    {
        int u = vertexOverflow();
        if (!push(u))
            relabel(u);
    }

    // ver.back() returns last Vertex, whose
    // e_flow will be final maximum flow
    return excessList[0];
}


int main() {
    int n_suppliers,n_storing, n_connections,offset,
    connection_capacity, sourceV,destinV,i,k;

    if(scanf("%d",&n_suppliers) < 0)
        exit(-1);
    if(scanf("%d",&n_storing) < 0)
        exit(-1);
    if(scanf("%d",&n_connections) < 0)
        exit(-1);

    Network network(n_suppliers, n_storing, n_connections);

        for (i=2; i< n_suppliers + 2; i++) {
            if(scanf("%d", &connection_capacity ) < 0)
                  exit(-1);
            network.setConnection(i,0, connection_capacity);
        }
        k = i;
        offset=n_storing;
        for (i=k; i < k+ n_storing; i++) {
            if(scanf("%d", &connection_capacity ) < 0)
                  exit(-1);
            network.setConnection(i+offset,i, connection_capacity);
        }

        for (i=0; i<n_connections; i++) {
            if(scanf("%d %d %d", &sourceV, &destinV, &connection_capacity ) < 0)
                  exit(-1);
            if (sourceV > 1 + n_suppliers) sourceV = sourceV + offset;
            network.setConnection(destinV,sourceV, connection_capacity);

        }
        network.print();
        printf("\n%d\n",network.getMaxFlow(1));

        //free all the memory allocated to the network object
        //network.freeNetwork();
        return 0;
    }
