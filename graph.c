#include <stdio.h>
#include <stdlib.h>
#include "list.h"

	

LIST *symmetricDifference (LIST *a, LIST *b) {

    LIST *aux = a;
    LIST *list = createList();
    
    while (aux != NULL) {
        if (!atList(list, aux->key)) {
            insert(&list, aux->key);
        }
        aux = aux->next;
    }
    
    aux = b;
    
    while (aux != NULL) {
        if (!atList(list, aux->key)) {
            insert(&list, aux->key);
        }
        aux = aux->next;
    }
        
    return list;
}


int main() {

    LIST *teste1 = createList();
    LIST *teste2 = createList();
    
    int i;
    
    for (i = 0; i < 5; i++)
    insert (&teste1, i);
    
    for (i = 1; i <10; i = i+2)
    insert (&teste2, i);
    
    printList(teste1);
    printList(teste2);
    printList(symmetricDifference(teste1, teste2));
    
	
}
