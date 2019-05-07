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
    Network(int numStations);   // Network Constructor
    void addRouterToNetwork(int router1, int router2);
    void freeNetwork();
};

    Network::Network(int numStations, int numStoring)  {
        int i;
        this->numStations = numStations + 2;
        adjLists = new list<int>[numRouters+];
    	}

    void Network::addRouterToNetwork(int router1, int router2) {
            adjLists[router1].push_front(router2);
            adjLists[router2].push_front(router1);
    }

    void Network::freeNetwork() {}

    int main() {
        int n_stations,n_suppliers, supplier_production, n_storing, n_connections, router_1, router_2,i;
        if(scanf("%d",&n_suppliers) < 0)
          exit(-1);
        if(scanf("%d",&n_storing) < 0)
          exit(-1);
        if(scanf("%d",&n_connections) < 0)
          exit(-1);
        n_stations = n_suppliers + n_storing;
        Network network(n_stations);

        list<int>::iterator r;
        i=0;
        for (r= adjLists[i].begin() ; r != adjLists[router_id].end(); i++) {
            if(scanf("%d", network.[0] ) < 0)
                  exit(-1);

        }
           if(scanf("%d %d", &router_1, &router_2) < 0)
                 exit(-1);
             network.addRouterToNetwork(router_1, router_2);
         }

        //free all the memory allocated to the network object
        //network.freeNetwork();
        return 0;
    }
