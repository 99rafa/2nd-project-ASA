#include <iostream>
#include <list>
#include <stack>
#include <algorithm>
using namespace std;

class Network
{
    int num_vertex, num_suppliers;
    list<Vertex> vertex_list;
    list<Edge> edge_list;

public:
    Network(int numStations, int numStoring, int numConnections);   // Network Constructor
    void addEdge(Edge edge);
    void addVertex(Vertex vertex);
    void freeNetwork();
};

class Vertex
{
    int overflow, height;
};

class Edge 
{
    int capacity, current_flow;
    int origin, destination;
};

Network::Network(int numSuppliers, int numStoring, int numConnections)  {
    int i;
    this->num_vertex = numSuppliers + numStoring + 2;
    this->num_suppliers = numSuppliers;
    vertex_list = new list<Vertex>[numSuppliers + numStoring + 2 + 2*numStoring];
    edge_list = new list<Edge>[numConnections + numStoring];
}

void Network::addEdge(Edge edge) {
    edge_list.push_front(edge);
}


int main() {
    int n_suppliers, supplier_production,
     n_storing, n_connections, router_1, router_2,i;
    
    if(scanf("%d",&n_suppliers) < 0)
        exit(-1);
    if(scanf("%d",&n_storing) < 0)
        exit(-1);
    if(scanf("%d",&n_connections) < 0)
        exit(-1);
    
    Network network(n_suppliers, n_storing, n_connections);


    
    //free all the memory allocated to the network object
    network.freeNetwork();
    return 0;
}
