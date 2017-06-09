#include "queue.h"
#include "graphHK.h"

#define nil 0
#define MAX 65000

// LEMBRAR QUE OS NODOS COMEÇAM EM 1

int *pairU, *pairV, *dist;

int breadthFirstSearch (GRAPH graph) {
    
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
    
    
    while (!isEmpty(q)) {
        i = dequeue(&q);
        
        if (dist[i] < dist[nil]) {
            
            degree = graph.nodes[i].degree; // size of i's neighborhood
            j = 0;
            hood = neighboors(graph, i);
            while (j < degree) {
                vPosition = hood[j] - graph.uLast;
                if (dist[pairV[vPosition]] == MAX) {
                    dist[pairV[vPosition]] = dist[i]+1;
                    enqueue(&q, pairV[vPosition]);
                }
                j++;
            }
        }
    }
    
    if (dist[nil] == MAX) {
        return 0;
    }
    
    else {
        return 1;
    }
 
}


int main() {
    
    GRAPH graph = createGraph(stdin);
    
    pairU = (int*)malloc(sizeof(int)*graph.uLast+1);    // there is no node 0
    pairV = (int*)malloc(sizeof(int)*(graph.numberOfNodes - graph.uLast));
    dist = (int*)malloc(sizeof(int)*graph.numberOfNodes);   // node 0 is NIL
    
    int i;
    
    for (i = 0; i<graph.numberOfNodes-graph.uLast; i++)
    pairV[i] = 0;
    
    breadthFirstSearch(graph);
    
}
