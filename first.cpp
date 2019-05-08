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
    int u, v;

    Edge(int current_flow, int capacity, int u, int v)
    {
        this->flow = flow;
        this->capacity = capacity;
        this->u = u;
        this->v = v;
    }
};

// Represent a Vertex
struct Vertex
{
    int id;
    vector<Edge> adjList;

    Vertex(int id)
    {
        this->id = id;
    }
};

class Network
{
    int num_vertex, num_suppliers;
    vector<Vertex> vertex_list;
    vector<int> excessList, heightsList;

public:
    Network(int numSuppliers, int numStoring, int numConnections);   // Network Constructor
    void setConnection( int capacity, int u, int v);
    void freeNetwork();
    void relabel(int u);
    bool push(int u);
    void preflowInitializer(int id);
};
    Network::Network(int numSuppliers, int numStoring, int numConnections)  {
        int i;
        this->num_vertex = numSuppliers + 2*numStoring + 2;
        this->num_suppliers = numSuppliers;
        for (i=0; i<this->num_vertex; i++) {
            this->excessList.push_back(0);
            this->heightsList.push_back(0);
        }
        for (i=0; i< this->num_vertex; i++) {
            vertex_list.push_back(Vertex(i));
        }
    }

    void Network::setConnection(int capacity, int u, int v) {
        Edge connection = Edge(0, capacity,u,v);
        vertex_list[u].adjList.push_back(connection);
    }

    void Network::relabel() {
        
    }




int main() {
    int n_suppliers,n_storing, n_connections,
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
            network.setConnection(0,i, connection_capacity);
        }
        k = i;
        for (i=k; i < k+ n_storing; i++) {
            if(scanf("%d", &connection_capacity ) < 0)
                  exit(-1);
            network.setConnection(i,i+n_storing+1, connection_capacity);
        }

        for (i=0; i<n_connections; i++) {
            if(scanf("%d %d %d", &sourceV, &destinV, &connection_capacity ) < 0)
                  exit(-1);
            network.setConnection(sourceV,destinV, connection_capacity);
        }

        //free all the memory allocated to the network object
        //network.freeNetwork();
        return 0;
    }
