#include <iostream>
#include <list>
#include <stack>
#include <algorithm>
using namespace std;

class Network
{
    int numRouters
    list<int> *adjLists;

public:
    Network(int numRouters);   // Network Constructor
    void addRouterToNetwork(int router1, int router2);
};

    Network::Network(int numRouters)  {
        int i;
        this->numRouters = numRouters;
    	}

    void Network::addRouterToNetwork(int router1, int router2) {
            adjLists[router1].push_front(router2);
            adjLists[router2].push_front(router1);
    }

    void Network::freeNetwork() {}

    int main() {
        int n_routers, n_edges, router_1, router_2,i;
        if(scanf("%d",&n_routers) < 0)
          exit(-1);
        Network network(n_routers);

        if(scanf("%d",&n_edges) < 0)
          exit(-1);

        for (i=0; i < n_edges; i++) {
          if(scanf("%d %d", &router_1, &router_2) < 0)
                exit(-1);
            network.addRouterToNetwork(router_1, router_2);
        }

        //free all the memory allocated to the network object
        network.freeNetwork();
        return 0;
    }
