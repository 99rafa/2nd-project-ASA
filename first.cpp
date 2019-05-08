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
        this->flow = flow;
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
    void setConnection( int capacity, int u, int v);
    void freeNetwork();
    void relabel(int u);
    bool push(int u);
    void preflowInitializer(int id);
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
        
        for (i=0; i< this->num_vertex; i++) {
            vertex_list.push_back(Vertex(i));
        }
    }

    void Network::setConnection(int capacity, int origin, int destination) {
        Edge connection = Edge(0, capacity, origin, destination);
        edge_list.push_back(connection);
    }

    void Network::relabel(int u) {
        
    }

    void Network::print(){
        int i;
        
        for(i = 0; i < num_edges; i++)
        {
            printf("%d - %d\n", edge_list[i].origin, edge_list[i].destination);
        }
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

    int offset = n_storing;
    
    //import transposed graph
    for (i=2; i< n_suppliers + 2; i++) {
        if(scanf("%d", &connection_capacity ) < 0)
                exit(-1);
        network.setConnection(connection_capacity, i, 0); //destination is origin
    }
    k = i;
    for (i = k; i < k + n_storing; i++) {
        if(scanf("%d", &connection_capacity ) < 0)
                exit(-1);
        network.setConnection(connection_capacity, i + offset, i); //offset of imaginary storing stations
    }

    for (i = 0; i < n_connections; i++) {
        if(scanf("%d %d %d", &sourceV, &destinV, &connection_capacity ) < 0)
                exit(-1);
        network.setConnection(connection_capacity, destinV, sourceV);
    }

    network.print();
        //free all the memory allocated to the network object
        //network.freeNetwork();
        return 0;
    }
