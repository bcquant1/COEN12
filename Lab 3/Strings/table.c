/* Brandon Quant
COEN 12 Lab 3
*/
#include <stdio.h>
#include <string.h>
#include "set.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2

typedef struct set{
    int count;
    int length;
    char **elts;
    char *flags;
}SET;

unsigned strhash(char*s){ //hash function, expected runtime O(1), worst case runtime O(n)
    unsigned hash = 0;
    while (*s != '\0'){
        hash = 31 * hash + *s ++;//ensures to get a more unique index so there isn't as many collisions
    }
    return hash;
}

SET *createSet (int maxElts){ //creating the SET, runtime O(n)
    SET *sp = malloc(sizeof(SET));
    assert (sp!= NULL);
    sp->length = maxElts;
    sp->elts = malloc(sizeof(char*)*maxElts);
    assert (sp->elts != NULL);
    sp->flags = malloc (sizeof(char)*maxElts);
    int i;  
    for (i = 0; i< maxElts; i++){
        sp->flags[i] = EMPTY;
    }
    return sp;
}

void destroySet(SET *sp){ //destroys the memory at the end, runtime O(n)
    assert(sp!=NULL);
    int i;
    for (i=0; i<sp->length; i++){
        if (sp->flags[i] == FILLED){
            free(sp->elts[i]);
        }
    }
    free(sp->elts);
    free(sp->flags);
    free(sp);
}

int numElements(SET *sp){ //returns the number of elements in the SET, runtime O(1)
    assert(sp!=NULL);
    return sp->count;
}

static int search (SET *sp, char *elt, bool *found){ //searches the SET to find a specific element, expected runtime O(1), worst case runtime O(n)
    assert (sp != NULL);
    assert(elt != NULL);
    int i = 0;
    int delete_flag = 0;
    int deleted_index;
    int index = (strhash(elt)) % (sp->length);
    while (i < sp->length-1){
        if(sp->flags[index] == FILLED){
            if(strcmp(elt,sp->elts[index]) == 0){ //checks if the element is found
                *found = true;
                return index;
            }
            else{
                i++;
            }
        }
        if(sp->flags[index] == DELETED){ //checks if the index is a deleted spot
            if (delete_flag == 0){
                    delete_flag = 1;
                    deleted_index = index;  //remembers the deleted index
            }
            else{
                i++;
            }
        }
        if(sp->flags[index] == EMPTY){//checks if the index is empty
            if (delete_flag == 1){ //if a deleted spot was found
                *found = false;
                return deleted_index;
            }
            else{ //if no deleted spot was found
                *found = false;
                return index; //return the index of the empty spot
            }
        }
        index = (strhash(elt) + i) % (sp->length);
    }
}

void addElement(SET *sp, char *elt){ //adding element into the set, expected runtime O(1), worst case runtime O(n) 
    assert(sp!= NULL);
    assert(elt!=NULL);
    bool found;
    int pos = search(sp,elt,&found);
    if (found == true){ //if it was found, then return
        return;
    }
    else{
        sp->elts[pos] = strdup(elt); //adding element into set and changing flag to FILLED
        sp->flags[pos] = FILLED;
        sp->count++;
    }

}

void removeElement(SET *sp, char *elt){ //removing element from the set, expected runtime O(1), worst case runtime O(n)
    assert(sp!= NULL);
    assert(elt!= NULL);
    bool found;
    int pos = search(sp,elt,&found);
    if (found == false){ //if not found, then return
        return;
    }
    else{
        sp->flags[pos] = DELETED; //if found, free and change the flag to deleted at that index
        free (sp->elts[pos]);
        sp->count--;
    }
    return;
}

char *findElement(SET *sp, char *elt){ //checks if the element is found, expected runtime O(1), worst case runtime O(n)
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

char **getElements(SET *sp){ //returns an array with the filled spots, runtime O(n)
    assert(sp!=NULL);
    char **arr = malloc(sizeof(char*)*sp->count); //allocating memory
    int i;
    int j = 0;
    for(i = 0; i < sp->length; i++){
        if (sp->flags[i] == FILLED){
            arr[j] = sp->elts[i];
            j++;
        }
    }    
    return arr;
}


