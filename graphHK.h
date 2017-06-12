#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUFFER_SIZE 100

typedef struct NODE {
  int edgesPosition;  // position of its edges on the edges array
  int currentOffset; // counting the number of edges already added
	int degree;
	//int previous;	// previous node in the path
}NODE;

typedef struct GRAPH {
  int numberOfNodes;
  int numberOfEdges;
  int uLast;  // last node on the U partition
  int insertedEdges;  // current position on the edges array
  NODE *nodes;
  int *targets;
}GRAPH;

void addEdge (GRAPH *graph, int source, int target) {

	int position;

	position = graph->nodes[source].edgesPosition + graph->nodes[source].currentOffset;

    assert(0 <= position && position < graph->numberOfEdges);
    graph->targets[position] = target;
    graph->insertedEdges++;
    graph->nodes[source].currentOffset++;
}

GRAPH createGraph (FILE *file) {
	GRAPH graph;

	char buffer[BUFFER_SIZE];
	int i, nodes, edges;

	do {
		fgets(buffer, sizeof(buffer), file);

		if (buffer[0] == 'p') {
			strtok(buffer, " ");	// reads the p
			strtok(NULL, " ");		// reads edge
			nodes = atoi(strtok(NULL, " "));
			edges = atoi(strtok(NULL, " "));
		}
	}while (buffer[0]  != 'e');
    
    edges = edges*2;

	graph.numberOfNodes = nodes+1;	//.gr doesnt have node 0
	graph.numberOfEdges = edges;
	graph.insertedEdges = 0;

	graph.nodes = (NODE*)malloc(sizeof(NODE)*(nodes+1));
	graph.targets = (int*)malloc(sizeof(int)*edges);

	for (i = 0; i<(nodes+1); i++) {
		graph.nodes[i].degree = 0;
		graph.nodes[i].currentOffset = 0;
	}


  // build the graph
  int source, edgeSource, edgeTarget;

  fseek(file, 0, SEEK_SET);
  do {
    fgets(buffer, sizeof(buffer), file);
  }while (buffer[0]  != 'e');		// reads till the beggining of the edges
  fseek(file, -1*strlen(buffer), SEEK_CUR);

  while (fgets(buffer, sizeof(buffer), file) != NULL) {	// sets the nodes degrees
    strtok(buffer, " "); // reads the identifier character
    source = atoi(strtok(NULL, " "));
    graph.nodes[source].degree++;
    source = atoi(strtok(NULL, " "));
    graph.nodes[source].degree++; // the graph isnt directed so the edge has to exist both ways
  }

  graph.nodes[0].edgesPosition = 0;	// sets the offsets
	for (i = 1; i < graph.numberOfNodes; i++) {
		graph.nodes[i].edgesPosition = graph.nodes[i-1].edgesPosition + graph.nodes[i-1].degree;
	}

  fseek(file, 0, SEEK_SET); // return to the beggining of the edges
	do {
		fgets(buffer, sizeof(buffer), file);
	}while (buffer[0]  != 'e');
	fseek(file, -1*strlen(buffer), SEEK_CUR);

  while (fgets(buffer, sizeof(buffer), file) != NULL) {	// for each edge
    strtok(buffer, " ");	// reads the identifier character
    edgeSource = atol(strtok(NULL, " "));
    edgeTarget = atol(strtok(NULL, " "));
    addEdge(&graph, edgeSource, edgeTarget);
    addEdge(&graph, edgeTarget, edgeSource);
      
    graph.uLast = edgeSource; // updates the last node in the u partition
    }

	return graph;
}

void printGraph (GRAPH graph) {

	int i = 1, j = 0;

	while (i < graph.numberOfNodes) {
		printf("nodo %d:\n", i);
		while (j < graph.nodes[i].degree) {
			printf("%d\n", graph.targets[graph.nodes[i].edgesPosition+j]);
			j++;
		}
		j = 0;
		i++;
	}
}

int isNeighboor (GRAPH graph, int source, int target) {

	int i = 0;
	int offset = graph.nodes[source].edgesPosition;

	while (i < graph.nodes[source].degree) {
		if (graph.targets[offset+i] == target)
			return 1;

		i++;
	}

	return 0;
}

int *neighboors (GRAPH graph, int source) { // ESSA NAO FOI TESTADA O SUFICIENTE
    
    int i, degree, start;
    i = 0;
    degree = graph.nodes[source].degree;
    start = graph.nodes[source].edgesPosition;
    
    int *hood = (int*)malloc(sizeof(int)*degree);
    
    while (i < degree) {
        hood[i] = graph.targets[start+i];
        i++;
    }
    
    return hood;
}
