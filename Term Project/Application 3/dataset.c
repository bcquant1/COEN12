
/*
Brandon Quant
COEN12 Term Project
Application 3
array of linked lists based on ages
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


typedef struct node{ //initializing the node that contains the age, id, and the next and prev that point to the next and previous nodes respectively
    struct node *next;
    struct node *prev;
    int age;
    int id;
}NODE;

typedef struct list{ //initializing the list that contains the count as well as the head node
    int count;
    NODE *head;
}LIST;

typedef struct set{ //initializing the set that contains the length and the list of head pointers
    int length;
    LIST **arr;
}SET;

LIST *createList (){ //allocates data for the list and initializes the count,age, and id  and the next,prev,and head nodes 
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head != NULL);
    lp->head->next = NULL;
    lp->head->prev = NULL;
    lp->head->age = 0;
    lp->head->id = 0;
    return lp;    
}

SET *createSet(){ //allocates memory for the set, and initializes the length and creates the array of head pointers
    SET *sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->length = 13;
    sp->arr = malloc(sizeof(LIST*)*sp->length);
    assert (sp->arr != NULL);
    for (int i = 0; i < sp->length;i++){
	sp->arr[i] = createList();
    }
    return sp;
}
    
void destroyList (LIST *lp){ //destroys a linked list and then frees the pointer
    assert(lp != NULL);
    NODE *pDel = lp->head;
    NODE *pPrev;
    while (pDel != NULL){
	pPrev = pDel;
	pDel = pDel->next;
	free(pPrev);
    }
    free(lp);
}

void destroySet (SET *sp){ //destroys the array of linked lists and then frees the set
    assert (sp != NULL);
    for (int i = 0; i < sp->length; i++){
	destroyList(sp->arr[i]);
    }
    free(sp);
}

int searchAge (SET *sp,LIST *lp, int age){ //searches for the age given sp, lp, and the age. if the age is found, the age is returned. If the age is not found, the function returns -1
    assert(sp != NULL);
    assert (lp != NULL);
    printf("The age we are looking for is %d\n",age);
    int index = age - 18;
    if (sp->arr[index]->count > 0){
	printf("The age has been found.\n");
	return age;
    }
    else{
	printf("There is no student with that age.\n");
	return -1;
    }
}

int searchId (SET *sp, LIST *lp, int id){ //searches for a specific id when given the sp, lp, and the id. If the id is found, then the index is returned and if the age is not found, the function returns -1
    assert (lp!= NULL);
    assert (id != 0);
    printf("The id that we are looking for is %d. \n", id);
    for (int i = 0; i < sp->length; i++){    
	NODE *pLoc = sp->arr[i]->head->next;
	while(pLoc != NULL) {
	    if (pLoc->id == id){
		printf("The id has been found. \n");
		return i;
	    }
	    pLoc = pLoc->next;
	}
    }
    printf("There is no student with that id\n");
    return -1;
}

void addItem(SET *sp,LIST *lp, int id, int age){ //the function adds the item into the array of linked list. The function gets the age and corresponds that to the index of the head pointer, where then the new node that was created can be inserted from the front of the linked list which is right after the dummy node. Then the count for that specific linked list which is categorized by age is increased. 
    assert (sp != NULL && lp != NULL);
    assert(id != 0);
    assert(age != 0);
    NODE *pNew;
    pNew = malloc(sizeof(NODE));
    pNew->id = id;
    pNew->age = age;
    int index = age - 18;
    if (sp->arr[index]->head->next != NULL){
	NODE *pLoc = sp->arr[index]->head->next;
	pLoc->prev = pNew;
	pNew->next = pLoc;
	sp->arr[index]->head->next = pNew;
    }
    else{
	sp->arr[index]->head->next = pNew;
	pNew->prev = sp->arr[index]->head;
    }
    sp->arr[index]->count++;
}

void removeItem(SET *sp,LIST *lp, int id, int age){ //the function removes the item from the array of linked lists. The function first searches based on id to see if the id exists, and then deletes the id. Then the count for that linked list is decremented
    assert(sp != NULL && lp!=NULL);
    assert(id != 0 && age != 0);
    int index;
    printf("The student that we want to delete has an id of %d and an age of %d\n", id, age);
    if (searchId(sp,lp,id) != -1){
	if ((index = searchId(sp,lp,id)) != -1){
	    NODE *pLoc = sp->arr[index]->head->next;
	    while(pLoc != NULL){
		if (pLoc->id == id){
		    pLoc->prev->next = pLoc->next;
		    pLoc->next->prev = pLoc->prev;
		    free(pLoc);
		    printf("The student has been deleted\n");
		}    
		pLoc = pLoc->next;
	    }
	    sp->arr[index]->count--;
	}	
    }
}    

int maxAgeGap (SET *sp,LIST *lp){// the function returns the max age gap. The function gets the min and max based on if the count for that age exists. then the difference between the max and min ages are calculated and returned.
    assert(lp!= NULL);
    int max = 12;
    while (sp->arr[max]->count == 0){
	max--;
    }
    int min = 0;
    while (sp->arr[min]->count == 0){
	min++;
    }
    int ageGap = (sp->arr[max]->head->next->age) - (sp->arr[min]->head->next->age);
    return ageGap;
}


