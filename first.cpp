#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

queue<int> activeQueue;

struct Edge
{
    int flow, capacity;
    int origin, destination;

    Edge(int current_flow, int capacity, int destination)
    {
        this->flow = current_flow;
        this->capacity = capacity;
        this->destination = destination;
    }
};


class Network
{
    int num_vertex, num_suppliers, num_edges, num_storing;
    list<Edge> *edge_list;
    vector<int> excessList, heightsList;

public:
    Network(int numSuppliers, int numStoring, int numConnections);   // Network Constructor
    void setConnection( int u, int v, int capacity);
    bool isSupplier(int i);
    bool isStorer(int i);
    bool isInMinimumCut(int i);
    bool isOriginalStorer(int i);
    bool imagMinimum(int i);
    void freeNetwork();
    void relabel(int u);
    bool discharge(int u);
    void preflowInitializer(int source);
    int getMaxFlow(int s, int t);
    void updateTranspostEdgeFlow(int origin,int destination, int flow);
    void findCriticalStorage();
    void initializeQueue();
};
    Network::Network(int numSuppliers, int numStoring, int numConnections)  {
        int i;
        this->num_vertex = numSuppliers + 2*numStoring + 2;
        this->num_suppliers = numSuppliers;
        this->num_storing = numStoring;
        this->num_edges = numConnections + numStoring + numSuppliers;
        this->edge_list = new list<Edge>[num_vertex];
        for (i=0; i<this->num_vertex; i++) {
            this->excessList.push_back(0);
            this->heightsList.push_back(0);
        }
    }

    void Network::freeNetwork() {
        for (int i=0; i < this->num_vertex; i++)
            (this->edge_list[i]).clear();
        delete [] this->edge_list;
        this->excessList.clear();
        this->excessList.shrink_to_fit();
        this->heightsList.clear();
        this->heightsList.shrink_to_fit();
    }

    void Network::setConnection( int u, int v, int capacity) {
        Edge connection = Edge(0, capacity,v);
        this->edge_list[u].push_back(connection);
    }


    bool Network::isSupplier(int i){
        return i > 1 && i <= this->num_suppliers;
    }

    bool Network::isStorer(int i){
        return i > this->num_suppliers + 1;
    }

    bool Network::isOriginalStorer(int i){
        return i < 2 + this->num_suppliers + this->num_storing && i > 1 + this->num_suppliers;
    }

    bool Network::imagMinimum(int i) {
        int last_storing = this->num_suppliers + this->num_storing + 1;
        if(isStorer(i)){
            return this->heightsList[i] >= this->num_vertex && i > last_storing;
        }
        else
            return this->heightsList[i] >= this->num_vertex;
    }

    bool Network::isInMinimumCut(int i) {
        int offset = this->num_storing;
        int last_storing = this->num_suppliers + this->num_storing + 1;
        if(isStorer(i)){
            return this->heightsList[i] >= this->num_vertex && i + offset <= last_storing + offset;
        }
        else
            return this->heightsList[i] >= this->num_vertex;
    }



    void Network::preflowInitializer(int source)
    {

        this->heightsList[source] = this->num_vertex;

        list<Edge>::iterator r;
        for (r = this->edge_list[source].begin(); r != this->edge_list[source].end(); ++r)  {

            r->flow = r->capacity;

            this->excessList[r->destination] += r->flow;

            this->edge_list[r->destination].push_back(Edge(-r->flow, 0, source));
        }
    }

    // Update reverse flow for flow added on ith Edge
    void Network::updateTranspostEdgeFlow(int origin, int destination, int flow)
    {
        int u = destination, v = origin;

            list<Edge>::iterator r;
            for (r = this->edge_list[u].begin(); r != this->edge_list[u].end(); ++r)  {

            if (r->destination == v )
            {
                r->flow -= flow;
                return;
            }
        }
        // adding reverse Edge in residual graph
        Edge e = Edge(0, flow, v);
        this->edge_list[u].push_back(e);
    }

    bool Network::discharge(int u)
    {

        list<Edge>::iterator r;
        for (r = this->edge_list[u].begin(); r != this->edge_list[u].end(); ++r)

        {

            if (r->flow == r->capacity)
                continue;


            if (this->heightsList[u] > this->heightsList[r->destination])
            {

                int flow = min(r->capacity - r->flow,
                               this->excessList[u]);

                this->excessList[u] -= flow;
                if(this->excessList[u] == 0) activeQueue.pop();

                if(this->excessList[r->destination]==0 && r->destination != 0 && r->destination !=1) activeQueue.push(r->destination);
                this->excessList[r->destination] += flow;

                r->flow += flow;
                updateTranspostEdgeFlow(u,r->destination, flow);

                return true;
            }
        }
        return false;
    }

    void Network::relabel(int u)
    {
        // Initialize minimum height of an adjacent
        double minHeight = 2* this->num_vertex;

        list<Edge>::iterator r;
        for (r = this->edge_list[u].begin(); r != this->edge_list[u].end(); ++r)  {

            if (r->flow == r->capacity)
                continue;

            if (this->heightsList[r->destination] < minHeight)
            {
                minHeight = this->heightsList[r->destination];

                this->heightsList[u] = minHeight + 1;
            }
        }
    }

    void Network::initializeQueue() {
        for (int i = 2; i < this->num_vertex; i++) {
        if ( this->excessList[i] > 0) {
            activeQueue.push(i);
        }
    }
}
        int Network::getMaxFlow(int s, int t){
            preflowInitializer(s);

            initializeQueue();
            while (!(activeQueue.empty()))
            {
                    int i=activeQueue.front();
                    if (!discharge(i)) {
                        relabel(i);
                    }

            }
            return this->excessList[0];
        }




    void Network::findCriticalStorage() {
        int i, fixedSource, fixedDestination;
        vector<int> critical_stores;
        vector<pair<int,int>> to_upgrade;

        int offset = this->num_storing;
        for(i = 2; i < this->num_vertex; i++)
        {
            if(!isInMinimumCut(i)){
                if( isOriginalStorer(i) && this->heightsList[i+offset] >= this->num_vertex )
                    critical_stores.push_back(i);
            }
        }

        for(i = 1; i < this->num_vertex; i++){
            if(isInMinimumCut(i)){
                list<Edge>::iterator r;
                for (r = this->edge_list[i].begin(); r != this->edge_list[i].end(); r++)  {
                    if ( r->destination != 0) {
                        if (isStorer(i) && isStorer(r->destination)) {
                            if(i - r->destination == offset)
                            continue;
                        }
                        if(!isInMinimumCut(r->destination) && !imagMinimum(r->destination)){
                            fixedSource = r->destination;
                            fixedDestination = i;
                            if (r->destination > 1 + this->num_storing + this->num_suppliers) fixedSource -= offset;
                            if ( i > 1 + this->num_storing + this->num_suppliers) fixedDestination -=offset;
                            to_upgrade.push_back(make_pair(fixedSource, fixedDestination));
                        }
                    }
                }
            }
        }
        sort(critical_stores.begin(), critical_stores.end());
        sort(to_upgrade.begin(),to_upgrade.end());
        for(i = 0; (unsigned) i < critical_stores.size(); i++)
        {
            printf("%d", critical_stores[i]);
            if ((unsigned) i != critical_stores.size()-1) printf(" ");
        }
        printf("\n");

        for(i=0; (unsigned) i < to_upgrade.size(); i++){
            printf("%d %d\n", to_upgrade[i].first, to_upgrade[i].second);
        }
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

        printf("%d\n",network.getMaxFlow(1,0));
        network.findCriticalStorage();

        //free all the memory allocated to the network object
        network.freeNetwork();
        return 0;
    }
