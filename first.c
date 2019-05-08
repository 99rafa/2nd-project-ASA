#include <stdio.h>
#include<stdlib.h>

/************** Structures **************/
typedef struct Edge
{
    int flow, capacity;
    // start vertex as u and end vertex as v.
    int u, v;
}*edge

typedef struct Net{

}*Network
    Edge(int current_flow, int capacity, int u, int v)
    {
        this->flow = flow;
        this->capacity = capacity;
        this->u = u;
        this->v = v;
    }
};

// Represent a Vertex
typedef struct Vertex
{
    int height, id;
}*vertex
    Vertex(int id)
    {
        this->id = id;
        this->height = 0;
    }
};



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
