#include <iostream>
#include <list>
#include <stack>
#include <algorithm>
using namespace std;


class Vertex
{
    int id, overflow, height;

    public:
        Vertex();
        int getId();
};
    Vertex::Vertex(){
        this->id=0;
        this->height = 0;
    }
    int Vertex::getId(){
        return this->id;
    }

class Edge
{
    int capacity, current_flow;
    int origin, destination;
};

class Network
{
    int num_vertex, num_suppliers;
    list<Vertex>* vertex_list;
    vector<Edge> edge_list;

public:
    Network(int numStations, int numStoring, int numConnections);   // Network Constructor
    void addEdge(Edge edge);
    void addVertex(Vertex vertex);
    void setConnection(int sourceV, int destinV, int capacity);
    void freeNetwork();
};
    Network::Network(int numSuppliers, int numStoring, int numConnections)  {
        int i;
        this->num_vertex = numSuppliers + numStoring + 2;
        this->num_suppliers = numSuppliers;
        vertex_list = new list<Vertex>[numSuppliers + numStoring + 2 + 2*numStoring];
    }

    void Network::addEdge(Edge edge) {
        edge_list.push_front(edge);
    }
    void Network::addVertex(Vertex vertex){
        vertex_list[vertex.getId()].push_front(vertex);
    }





    void Network::setConnection(int sourceV, int destinV, int capacity) {}

    void Network::freeNetwork() {}

    int main() {
        int n_stations, n_suppliers, supplier_production,
        current_id,n_storing, n_connections, connection_capacity, sourceV, destinV,i, k;
        if(scanf("%d",&n_suppliers) < 0)
          exit(-1);
        if(scanf("%d",&n_storing) < 0)
          exit(-1);
        if(scanf("%d",&n_connections) < 0)
          exit(-1);
        n_stations = n_suppliers + n_storing;
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
