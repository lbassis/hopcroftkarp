#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readNodes(char *filename) {
    
    char buffer[100];
    int nodes;
    FILE *file = fopen(filename, "r");
    
    do {
        fgets(buffer, sizeof(buffer), file);
        
        if (buffer[0] == 'p') {
            strtok(buffer, " ");	// reads the p
            strtok(NULL, " ");		// reads edge
            nodes = atoi(strtok(NULL, " "))/2;
        }
    }while (buffer[0]  != 'e');
    
    fclose(file);
    
    return nodes;
}

void writeSource(int nodes) {
    
    FILE *file = fopen("transformed.gr", "w");
    
    int i = 1;
    
    fprintf(file, "n 0 s\nn %d t\n", nodes*2+1);
    
    
    while (i <= nodes) {
        fprintf(file, "e 0 %d\n", i);
        i++;
    }
    
    fclose(file);
}

void writeSink(int nodes, char *filename) {
    
    int i = nodes+1;
    FILE *file = fopen(filename, "a");
    
    while (i <= nodes*2) {
        fprintf(file, "e %d %d\n", i, nodes*2+1);
        i++;
    }
    
    
}
int main (int argc, char **argv) {
    
    char originalFile[50];
    strcpy(originalFile, argv[1]);
    
    int nodes = readNodes(originalFile);
    writeSource(nodes);
    writeSink(nodes, originalFile);
    
}
