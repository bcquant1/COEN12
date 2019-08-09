/*
Brandon Quant
COEN 12 Lab
Project 5 
*/


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

//defining the parent, left and right child
#define p(x) ((x-1)/2) 
#define l(x) ((x*2)+1)
#define r(x) ((x*2)+2)


typedef struct pqueue{ //structure that contains the data, number of entries, the max amount of entries and the pointer to the compar e function
    int count;
    int length;
    void **data;
    int (*compare)();
}PQ;

void swap (PQ *, int, int);

PQ *createQueue(int (*compare)()){ //creating the queue, runtime: O(1)
    PQ *pq = malloc(sizeof(PQ));
    assert (pq != NULL);
    pq->count = 0;
    pq->length = 10;
    pq->compare = compare;
    pq->data = malloc(sizeof(void*)*pq->length);
    return pq;
}

void destroyQueue(PQ *pq){ //destroying the queue at the end, runtime: O(1)
    assert (pq!=NULL);
    free(pq->data);
    free(pq);
}

int numEntries(PQ *pq){ //returns the number of entries, runtime: O(1)
    return pq->count;
}

void addEntry(PQ *pq, void *entry){ //adds an entry to the priority queue, runtime: O(n)
    assert (pq!= NULL);
    assert (entry != NULL);
    int index;
    if(pq->length == pq->count){ //checking if the queue is full
	pq->length = pq->length *2;
	pq->data= realloc(pq->data, sizeof(void*)*pq->length); //reallocating more memory
    }
    index = pq->count;
    pq->data[index] = entry; 
    while (index > 0){ 
	if ((*pq->compare)(pq->data[index], pq->data[p(index)]) < 0){//checking if the parent is larger than the value at the index
	    swap(pq, index, p(index)); //swapping the nodes
	    index = p(index);
	}
	else{
	    break;
	} 
    }
    pq->count++;
}

void *removeEntry(PQ *pq){ //removes an entry and then fixes the tree, runtime O(n)
    assert (pq != NULL);
    void *root = pq->data[0]; //remembers the value at the root
    int pCur = 0;
    int children_index;
    pq->data[0] = pq->data[pq->count-1];
    while (l(pCur) < pq->count){
	if (r(pCur) < pq->count){
	    if ((*pq->compare)(pq->data[l(pCur)],pq->data[r(pCur)]) < 0){// compares the left and right child
		children_index = l(pCur);
	    }
	    else{
		children_index = r(pCur);
	    }
	}
	else{
	    children_index = l(pCur);
	}
	if ((*pq->compare)(pq->data[children_index], pq->data[pCur]) < 0){ //comparing the smaller value from the smaller value from the left and right child to the current index 
	    swap(pq,children_index,pCur);
	}
	pCur = children_index;
    }	
    pq->count--;
    return root;
}

void swap (PQ *pq, int index1, int index2){ //swaps the values at the indexes, runtime: O(1)
    void *temp = pq->data[index1];
    pq->data[index1] = pq->data[index2];
    pq->data[index2] = temp;
    //printf("Swap: %d with %d\n", index1,index2); 
}



