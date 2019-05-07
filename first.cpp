#include <iostream>
#include <list>
#include <stack>
#include <algorithm>
using namespace std;

class Network
{
    int numStations;
    list<int> *adjLists;

public:
    Network(int numStations, int numStoring);   // Network Constructor
    void addRouterToNetwork(int router1, int router2);
    void freeNetwork();
    void setConnection(int sourceV, int destinV, int capacity);
};

    Network::Network(int numStations, int numStoring)  {
        int i;
        this->numStations = numStations + 2;
    	}

    void Network::addRouterToNetwork(int router1, int router2) {
            adjLists[router1].push_front(router2);
            adjLists[router2].push_front(router1);
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
        Network network(n_suppliers, n_storing);

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
