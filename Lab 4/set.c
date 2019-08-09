/*Brandon Quant
COEN 12
Lab 4 Part 2
*/
#include "set.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"

#define AVG_CHAIN_LENGTH 20

typedef struct set{ 
    int count;
    int length;
    int (*compare)();
    unsigned(*hash)();
    LIST **arr;    
}SET;


SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){ //creating the set of list pointers, runtime O(n)
    SET *sp = malloc(sizeof(SET));
    assert (sp!=NULL);
    sp->length = maxElts/AVG_CHAIN_LENGTH;
    sp->arr = malloc(sizeof(LIST*)*sp->length);
    assert (sp->arr != NULL);
    for (int i = 0; i < sp->length; i++){ //creating sp->length list pointers
        sp->arr[i] = createList((compare));
    }
    sp->compare = compare;
    sp->hash = hash;
    return sp;
}

void destroySet(SET *sp){ //destroys the linked lists pointed by the list pointers and list pointers, runtime O(n^2)
    assert (sp!= NULL);
    for (int i = 0; i <sp->length; i++){
        destroyList(sp->arr[i]);
    }
    free(sp);
}

int numElements(SET *sp){// returns the number of pointers in the array, runtime O(1)
    assert (sp!= NULL);
    return sp->count;
}

void addElement(SET *sp, void *elt){ //adding an element by getting the hash index and then calling the addLast from list.c, runtime O(1);
    assert(sp!=NULL);
    assert(elt!=NULL);
    int index =(*sp->hash)(elt) % (sp->length);
    if (findItem(sp->arr[index], elt) == NULL){ //checking if the element is not already in the linked list pointed by the specific pointer
        addLast(sp->arr[index],elt);
        sp->count++;//increments the count
    }
}

void removeElement(SET *sp, void *elt){//removes the element by getting the hash index and then calling the removeItem function, runtime O(n);
    assert(sp!= NULL);
    assert(elt!= NULL);
    int index = (*sp->hash)(elt) % (sp->length);
    if (findItem(sp->arr[index],elt) != NULL){
        removeItem(sp->arr[index], elt);
        sp->count--; //decrements the count
    }
}

void *findElement (SET *sp, void *elt){//find the element in a specific linked list pointed by a list pointer, runtime O(n)
    assert(sp!= NULL);
    assert(elt!=NULL);
    int index = (*sp->hash)(elt) % (sp->length); //gives the index of the linked list pointer in order to search that specific linked list
        return findItem(sp->arr[index], elt);
}

void *getElements(SET *sp){ //returns an array of all the elements in all of the linked lists, runtime O(n^2)
    assert (sp!=NULL);
    int j = 0;
    void **data2 = malloc(sizeof(void*)*sp->count);
    assert(data2!=NULL);
    for (int i = 0; i < sp->length; i++){
        memcpy(data2+j,getItems(sp->arr[i]), sizeof(void*)*numItems(sp->arr[i]));
        j += numItems(sp->arr[i]);
    }
    return data2;
}


