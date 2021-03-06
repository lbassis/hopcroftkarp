#include "queue.h"
#include "graphHK.h"
#include <sys/time.h>
#include <math.h>


#define nil 0
#define MAX 65000


int *pairU, *pairV, *dist;
int bfs = 0;
int dfs = 0;

int breadthFirstSearch (GRAPH graph) {
    
    bfs++;
    int i = 1;
    int degree, j, vPosition;   // vpairs should use its id - uLast for they start at the uLast position
    int *hood;
    
    QUEUE *q = createQueue();
    
    
    while (i < graph.uLast+1) {
        if (pairU[i] == nil) {
            dist[i] = 0;
            enqueue(&q, i);
        }
        
        else {
            dist[i] = MAX;
        }
        i++;
    }
    

    dist[nil] = MAX;
    
    
    // search between the free vertices
    
    while (!isEmpty(q)) {
        i = dequeue(&q);
        
        if (dist[i] < dist[nil]) {  // if it was free   (this might be redundant)
            
            degree = graph.nodes[i].degree; // size of i's neighborhood
            j = 0;
            hood = neighboors(graph, i);
            while (j < degree) {            // checks the neighborhood
                vPosition = hood[j] - graph.uLast;
                if (dist[pairV[vPosition]] == MAX) {
                    dist[pairV[vPosition]] = dist[i]+1;
                    enqueue(&q, pairV[vPosition]);
                }
                j++;
            }
        }
    }
    
    destroy(&q);
    q = NULL;
     
    
    if (dist[nil] == MAX) {
        return 0;
    }
    
    else {
        return 1;
    }
 
}

int depthFirstSearch (int u, GRAPH graph) {
    
    dfs++;
    int *hood;
    int i = 0, degree, vPosition;
    
    if (u != nil) {
        
        hood = neighboors(graph, u);
        degree = graph.nodes[u].degree;
        
        while (i < degree) {
            vPosition = hood[i]-graph.uLast;
            
            if (dist[pairV[vPosition]] == dist[u] + 1) {
                
                if (depthFirstSearch(pairV[vPosition], graph)) {
                    pairV[vPosition] = u;
                    pairU[u] = hood[i];
                    return 1;
                }
            }
            
            i++;
        }
        
        dist[u] = MAX;
        return 0;
    }
    return 1;
}

int main() {
    
    GRAPH graph = createGraph(stdin);
    
    if (graph.numberOfEdges == 0) {
        printf("0\n");
        return 0;
    }
    
    pairU = (int*)malloc(sizeof(int)*(graph.uLast+1));
    pairV = (int*)malloc(sizeof(int)*(graph.numberOfNodes - graph.uLast));
    dist = (int*)malloc(sizeof(int)*graph.numberOfNodes);   // node 0 is NIL
    
    int i;
    
    for (i = 0; i<graph.numberOfNodes-graph.uLast; i++) {
        pairV[i] = nil;
    }
    
    for (i=0; i<graph.uLast+1; i++) {
        pairU[i] = nil;
    }
    
    int matching = 0;
    
    while (breadthFirstSearch(graph)) {
        i = 1;
        
        while (i < graph.uLast+1) {
            if (pairU[i] == nil) {
                if (depthFirstSearch(i, graph)) {
                    matching = matching+1;
                }
            }
            i++;
        }
    }
    
    free(pairU);
    free(pairV);

    
    printf("%d\n", matching);
    
    
    return 0;
}
