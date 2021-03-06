/* Brandon Quant
COEN 12 Lab 6
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "set.h"

#define EMPTY 0
#define FILLED 1
#define DELETED 2

typedef struct set{ //defining the set
    int count;
    int length;
    void **elts;
    char *flags;
    int (*compare)();
    unsigned(*hash)();
}SET;

void quicksort(void **, int, int, int (*compare)());
int partition(void **, int, int, int (*compare)());

SET *createSet (int maxElts, int (*compare)(), unsigned(*hash)()){// creating SET, runtime O(n)
    SET *sp = malloc(sizeof(SET));
    assert (sp!= NULL);
    sp->length = maxElts;
    sp->elts = malloc(sizeof(char*)*maxElts);
    assert (sp->elts != NULL);
    sp->flags = malloc (sizeof(char)*maxElts);
    sp->compare = compare;
    sp->hash = hash;
    int i;  
    for (i = 0; i< maxElts; i++){
	sp->flags[i] = EMPTY;
    }
    return sp;
}

void destroySet(SET *sp){ //destroys the memory at the end, runtime O(1)
    assert(sp!=NULL);
    free(sp->elts);
    free(sp->flags);
    free(sp);
}

int numElements(SET *sp){ //returns the number of elements in the SET, runtime O(1)
    assert(sp!=NULL);
    return sp->count;
}
static int search (SET *sp, void *elt, bool *found){ //seraches the SET for a specific element, expected runtime O(1), worst case runtime O(n)
    assert (sp != NULL);
    assert(elt != NULL);
    int i = 0;
    int delete_flag = 0;
    int deleted_index;
    int index = (*sp->hash)(elt) % (sp->length);
    while (i < sp->length-1){
	if(sp->flags[index] == FILLED){//checking if the spot is filled
	    if((*sp->compare)(elt,sp->elts[index]) == 0){ //if it is found, return the index of the found element
		*found = true;
		return index;    
	
	    }
	    else{
		i++;
	    }
	}
	if(sp->flags[index] == DELETED){ // if found a deleted spot, remember the deleted index
	    if (delete_flag == 0){
		delete_flag = 1;
		deleted_index = index;  
	    }
	    else{
		i++;
	    }
	}
	if(sp->flags[index] == EMPTY){//checks if found EMPTY
	    if (delete_flag == 1){
		*found = false; //if it wasn't found and passed a deleted spot, return the deleted index
		return deleted_index;
	    }
	    else{
		*found = false; //return the index of the empty spot
		return index;
	    }
	}
	index = ((*sp->hash)(elt) + i) % (sp->length);
    }
    return deleted_index;
}

void addElement(SET *sp, void *elt){//adding an elemtn into the set, expected runtime O(1), worst case runtime O(n)
    assert(sp!= NULL);
    assert(elt!=NULL);
    bool found;
    int pos = search(sp,elt,&found);
    if (found == true){
	return;
    }
    else{
	sp->elts[pos] = elt;
	sp->flags[pos] = FILLED;
	sp->count++;
    }

}

void removeElement(SET *sp, void *elt){//removing an element from the set, expected runtime O(1), worst case runtime O(n)
    assert(sp!= NULL);
    assert(elt!= NULL);
    bool found;
    int pos = search(sp,elt,&found);
    if (found == false){
	return;
    }
    else{
	sp->flags[pos] = DELETED;
	sp->count--;
    }
    return;
}
void *findElement(SET *sp, void *elt){ //checks if element is found, expected runtime O(1), worst case runtime O(n)
    assert(sp!=NULL);
    assert(elt!=NULL);
    bool found;
    int pos = search(sp,elt,&found);
    if (found == false){
	return NULL;
    }
    else{
	return sp->elts[pos];
    }
}

void* getElements(SET *sp){ // returns an array with the filled spots, runtime O(n)
    assert(sp!=NULL);
    void **elts = malloc(sizeof(void*)*sp->count);    
    assert(elts!=NULL);
    int i;
    int j = 0;
    for(i = 0; i < sp->length; i++){
	if (sp->flags[i] == FILLED){
	    elts[j] = sp->elts[i];
	    j++;
	}
    }    
    quicksort(elts,0,sp->count-1,sp->compare); //sorting the array
    return elts;
}
void quicksort (void **elts, int low, int high, int(*compare)()){ //sorts the array in alphabetical order, runtime O(n)
    if (low < high){
        int root = partition(elts,low,high,compare);
        quicksort(elts,low, root-1, compare); //sorting the left side of the wall
        quicksort(elts,root+1, high, compare); //sorting the right side of the wall
    }
} 
int partition (void **elts, int low, int high, int (*compare)()){ //setting where the wall is and moving words that are lower in the alphabet on the left side of thee first element in elts, runtime O(n)
    int i = low;
    void *temp;
    void *pivot = elts[high];
    for (int j = low; j < high; j++){ //running through 
        if ((*compare)(elts[j], pivot) < 0){
            temp = elts[i];
            elts[i] = elts[j];
            elts[j] = temp;
            i++;
        }
    }
	temp = elts[i];
	elts[i] = elts[high];
	elts[high] = temp; 
	return i;
}
