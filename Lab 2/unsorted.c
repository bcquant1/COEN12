/*Brandon Quant
COEN 12
Lab 2 Unsorted
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"
#include <assert.h>

typedef struct set{ //defining the set
    int length;
    int count;
    char **data;
}SET;

SET *createSet(int maxElts){ //creating memory for the set and assigning values to variables
    SET *sp = malloc(sizeof(SET));
    assert(sp!= NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data != NULL);
    return sp;
}

void destroySet(SET *sp){ //destroys the set at the end
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
int search (SET *sp, char *elt){ //runtime O(n), searches the set for a string
    assert(sp!=NULL);
    assert(elt!=NULL);
    int i;
    for (i = 0; i < sp->count;i++){
        if (strcmp(elt,sp->data[i]) == 0){
            return i;
        }
    }
    return -1;
}
void addElement(SET *sp, char *elt){ //runtime O(n), adding element at the bottom of the list
    assert(sp != NULL);
    assert(elt!=NULL);
    if (sp->count > sp->length){
        return;
    }
    if (search(sp,elt) != -1){
        return;
    }
    else{
        sp->data[sp->count] = malloc(sizeof(char)*(strlen(elt)+1));
        assert(sp->data[sp->count]!=NULL);
        strcpy(sp->data[sp->count],elt);
        sp->count++;
    }
}
void removeElement(SET *sp,char *elt){ //runtime O(n), deleting a specific string and placing the last element to the deleted place
    assert(sp!=NULL);
    assert(elt!=NULL);
    if (search(sp,elt) == -1){
        return;
    }
    else{
        free(sp->data[search(sp,elt)]);
        sp->count--;
        sp->data[search(sp,elt)] = sp->data[sp->count];
    }   
}
char* findElement(SET *sp, char *elt){ //runtime O(n), tell us if the string is found or not
    assert(sp!=NULL);
    assert(elt!=NULL);
    if (search(sp,elt) == -1){
        return NULL;
    }
    else{
        return sp->data[search(sp,elt)];
    }
}
char **getElements(SET *sp){ //runtime O(n), returns the array of strings
    assert(sp!=NULL); 
    char **arr = malloc(sizeof(char*)*sp->count);
    int i;
    for (i = 0; i < sp->count; i++){
        arr[i] = sp->data[i];
    }
    return arr;
}
