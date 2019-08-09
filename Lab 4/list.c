/*Brandon Quant
COEN 12
Project 4
*/

#include <stdio.h>
#include <string.h>
#include "list.h"
#include <assert.h>
#include <stdlib.h>

typedef struct node{ //creating a node with a next and a previous pointer
    struct node *next;
    struct node *prev;
    void *data;
}NODE;

typedef struct list{ //list containing the count, the head node(dummy node), and the compare function
    int count;
    NODE *head;
    int (*compare)();
}LIST;


LIST *createList (int(*compare)()){ //creating the list, runtime O(1)
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->compare = compare;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head !=NULL);
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
}

void destroyList(LIST *lp){ //destroy the list, runtime O(n)
    assert (lp != NULL);
    NODE *pDel;
    NODE *pPrev = lp->head->prev;
    do{
        pDel = pPrev;
        pPrev = pDel->prev;
        free (pDel);
    }
    while (pDel != lp->head);
    free (lp);
}

int numItems(LIST *lp){ //returns the number of items in the list, runtime O(1)
    assert (lp != NULL);
    return lp->count;
}

void addFirst(LIST *lp, void *item){ //adding an element after the head node, runtime O(1)
    assert (lp!= NULL);
    assert (item != NULL);
    NODE *pNew;
    pNew = malloc(sizeof( NODE));
    assert (pNew != NULL);
    pNew->data = item; //assigning the item into the new node
    pNew->next = lp->head->next; //making the links
    lp->head->next = pNew;
    pNew->prev = lp->head;
    pNew->next->prev = pNew;
    lp->count++; 
}

void addLast(LIST *lp, void *item){ //adding an element at the end if the list, runtime O(1)
    assert (lp!=NULL);
    assert (item != NULL);
    NODE *pNew;
    pNew = malloc(sizeof(NODE));
    assert (pNew!=NULL);
    pNew->data = item;
    pNew->next = lp->head; //making the links
    pNew->prev = lp->head->prev;
    lp->head->prev->next = pNew;
    lp->head->prev= pNew;
    lp->count++;
}

void *removeFirst(LIST *lp){ //removes the element after the dummy node and returns that item, runtime O(1)
    assert (lp!=NULL);
    NODE *pDel = lp->head->next;
    void *tempData = pDel->data;
    if (lp->head == lp->head->next){ //checking if there is only the dummy node
        return NULL;
    }
    else{
        lp->head->next = pDel->next; //deleting the node
        pDel->next->prev = lp->head;
        free(pDel);
        lp->count--;
        return tempData;
    }
}

void *removeLast(LIST *lp){ //removing the last item and returns that item, runtime O(1)
    assert (lp!=NULL);
    NODE *pDel = lp->head->prev;
    void *tempData = pDel->data;
    if(lp->head == lp->head->prev){ //checks if there is only the dummy node
        return NULL;
    }
    else{
        lp->head->prev = pDel->prev; //making the links and deleting the node
        pDel->prev->next = lp->head;
        free (pDel);
        lp->count--;
        return tempData;
    }
}


void *getFirst(LIST *lp){ //returns the data in the node after the head node, runtime O(1)
    assert (lp!= NULL);
    if (lp->head == lp->head->next){
        return NULL;
    }
    else{
        return lp->head->next->data;
    }
}

void *getLast(LIST *lp){ //returns the data in the last node, runtime O(1)
    assert (lp!= NULL);
    if (lp->head == lp->head->next){
        return NULL;
    }
    else{
        return lp->head->prev->data;
    }
}

void removeItem(LIST *lp, void *item){ //if item is found, the item is removed, runtime O(n)
    assert (lp!=NULL);
    assert (item != NULL);
    assert (lp->compare != NULL);
    NODE *pLoc = lp->head->next;
    while (pLoc != lp->head){ // traversing through the linked list
        if ((*lp->compare)(pLoc->data,item) == 0){ //compare function
            pLoc->prev->next = pLoc->next;
            pLoc->next->prev = pLoc->prev;
            free(pLoc);
            lp->count--;
        }
        pLoc = pLoc->next;
    }
}

void *findItem(LIST *lp, void *item){ //checking if item is found and if found, the data in that node is returned, runtime O(n)
    assert (lp!=NULL);
    assert (item != NULL);
    assert (lp->compare != NULL);
    NODE *pLoc = lp->head->next;
    while (pLoc != lp->head){ //traversing through the linked list
        if ((*lp->compare)(pLoc->data,item) == 0){
            return pLoc->data;
        }
        pLoc = pLoc->next;
    }
    return NULL;
}

void *getItems(LIST *lp){ //returns the array of items, runtime O(n)
    assert (lp!= NULL);
    int i = 0;
    void **data2 = malloc(sizeof(void*)*lp->count);
    assert (data2 != NULL);
    NODE *pLoc = lp->head->next;
    while (pLoc != lp->head){ //traversing through the linked list and placing the data into the array
        data2[i] = pLoc->data;
        pLoc = pLoc->next;
        i++;
    }
    return data2;
}

