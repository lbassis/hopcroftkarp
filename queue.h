#include <stdio.h>
#include <stdlib.h>

typedef struct KEY {
    int key;
    struct KEY *next;
}KEY;


typedef struct QUEUE {
    KEY *head;
    KEY *last;
}QUEUE;

QUEUE *createQueue() {
    
    QUEUE *q = (QUEUE*)malloc(sizeof(QUEUE));
    q->head = NULL;
    q->last = NULL;
    return q;
}

int isEmpty(QUEUE *q) {
    
    if (q->head == NULL)
        return 1;
    
    else
        return 0;
}

void printQueue(QUEUE *q) {
    
    if (q->head != NULL) {
        
        KEY *key = q->head;
        while (key != NULL) {
            printf("%d ", key->key);
            key = key->next;
        }
        printf("\n");
    }
    
    else {
        printf("Empty\n");
    }
}

void enqueue(QUEUE **q, int key) {
    
    if ((*q)->head == NULL) {
        
        KEY *new = (KEY*)malloc(sizeof(KEY));
        new->key = key;
        new->next = NULL;
        
        (*q)->head = new;
        (*q)->last = new;
    }
    
    else {
        
        KEY *new = (KEY*)malloc(sizeof(KEY));
        KEY *last = (*q)->last;
        
        new->key = key;
        new->next = NULL;
        last->next = new;
        (*q)->last = new;
    }
}


int dequeue(QUEUE **q) {
    
    if ((*q)->head != NULL) {
    
        int result;
        KEY *temp = (*q)->head;
    
        result = (*q)->head->key;
        (*q)->head = (*q)->head->next;
        free(temp);
        
        return result;
    }
    
    else {
        return -1;
    }
    
}

void destroy (QUEUE **q) {
    
    int result;
    
    do {
        result = dequeue(q);
    } while (result != -1);
}
