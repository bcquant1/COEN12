/*Brandon Quant
COEN 12
Lab 2 Sorted
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"
#include <assert.h>
#include <stdbool.h>

typedef struct set{ //defining the set
    int length;
    int count;
    char **data;
}SET;

SET *createSet(int maxElts){ //runtime O(1), creating memory and assigning variables to the set
    SET *sp = malloc(sizeof(SET));
    assert(sp!= NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data != NULL);
    return sp;
}

void destroySet(SET *sp){ //runtime O(n), deletes the set at the end
    assert(sp!=NULL);
    int i;
    for(i=0; i < sp->count; i++){
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp);
}
int numElements(SET *sp){ //runtime O(1), returns the number of elements in the set
    assert(sp!=NULL);
    return sp->count;
}
static int search (SET *sp, char *elt, bool *found){ //runtime O(logn), searches for a string using binary search
    assert(sp!=NULL);
    assert(elt!=NULL);
    int lo =0;
    int hi = sp->count-1;
    int mid;
    while (lo <= hi){
        mid = (lo + hi)/2;
        if (strcmp(elt,sp->data[mid]) < 0){
            hi = mid - 1;
        }
        else if (strcmp(elt,sp->data[mid]) > 0){
            lo = mid + 1;
        }
        else{
            *found = true;
            return mid;
        }
    }
	*found = false;
	return lo;
}
void addElement(SET *sp, char *elt){ //runtime O(n), adds element where it should be in the sorted set
    assert(sp != NULL);
    assert(elt != NULL);
    int i;
    bool found;
    int pos = search(sp,elt,&found);
    if (sp->count > sp->length){
        return;
    }
    if (found == true){
        return;
    }
    else{
        for (i = sp->count-1; i >= pos;i--){
            sp->data[i+1] = sp->data[i];
        }
        sp->data[pos] = strdup(elt);
        sp->count++;
    }
    return;
}
void removeElement(SET *sp,char *elt){ //runtime O(n), removes a specific element by shifting elements up
    assert(sp!=NULL);
    assert(elt!=NULL);
    int i;
    bool found;
    int pos = search(sp,elt,&found);
    if (found == false){
        return;
    }
    else{
        for(i = pos+1; i < sp->count; i++){
            sp->data[i-1] = sp->data[i];
        }
        sp->count--;
    }   
    return;
}
char* findElement(SET *sp, char *elt){ //runtime O(logn), tells us if the element is found
    assert(sp!=NULL);
    assert(elt!=NULL);
    bool found;
    int pos = search(sp,elt,&found);
    if (found == false){
        return NULL;
    }
    else{
        return sp->data[pos];
    }
}
char **getElements(SET *sp){ //runtime O(n) ,reeturns the array of strings
    assert(sp!=NULL);
    char **arr = malloc(sizeof(char*)*sp->count);
    int i;
    for (i = 0; i < sp->count; i++){
        arr[i] = sp->data[i];
    }
    return arr;
}
