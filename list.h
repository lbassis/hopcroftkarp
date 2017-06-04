#include <stdio.h>
#include <stdlib.h>

typedef struct LIST {
    int key;
    struct LIST *next;
} LIST;

LIST *createList () {
    return NULL;
}

void insert (LIST **list, int key) {
    
    if (*list == NULL) {
        *list = (LIST*)malloc(sizeof(LIST));
        (*list)->key = key;
        (*list)->next = NULL;
    }
    
    
    else {

        LIST *aux, *prev;
        aux = *list;
    
        while (aux != NULL) {
            prev = aux;
            aux = aux->next;
        }
        
        aux = (LIST*)malloc(sizeof(LIST));
        aux->key = key;
        aux->next = NULL;
        
        prev->next = aux;
    }
}

int atList (LIST *list, int key) {
    
    if (list == NULL) {
        return 0;
    }
    
    else if (list->key == key)
        return 1;
    
    else {
        
        LIST *aux = list;
        
        while (aux != NULL) {
            if (aux->key == key) {
                return 1;
            }
            
            aux = aux->next;
        }
        
        return 0;
    }
}

void printList (LIST *list) {
    
    LIST *aux = list;
    
    while (aux != NULL) {
        printf("%d ", aux->key);
        aux = aux->next;
    }
    printf("\n");
}

void destroy (LIST **list) {
    
    LIST *current = *list;
    LIST *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *list = NULL;
}

/*
int main () {
 
    LIST *teste = createList();
    insert (&teste, 5);
    insert (&teste, 9);
    insert (&teste, 11);
    printf("%d\n", teste->next->next->key);
    destroy(&teste);
}
*/
