/*
Brandon Quant
COEN 12 Term Project
Application 2  Dataset
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct set{ //defining the set and declaring the id and age in the set
    int *id;
    int *age;
}SET;

SET *createDataSet(int maxElts){ //creating the set by mallocing data for the id and age and setting all of the elements in the id and age arrays to 0
    SET *sp = malloc(sizeof(SET));
    assert (sp!= NULL);
    sp->id = malloc(sizeof(int) *maxElts);
    sp->age = malloc(sizeof(int) *maxElts);
    assert (sp->id != NULL);
    assert (sp->age != NULL);
    for (int i = 0; i< maxElts; i++){
	sp->id[i] = 0;
	sp->age[i] = 0;
    }
    return sp;
}

void destroyDataSet(SET *sp){ //destroying the set by freeing the id and age arrays and then freeing sp
    assert(sp!= NULL);
    free (sp->id);
    free (sp->age);
    free (sp);
}

int searchID(SET *sp, int inputid){ //searches for the id given an input id, returns the id/index if found in the ID array and returns -1 if the ID is not found in the ID array
    assert (sp != NULL);
    assert (inputid != 0);
    if (sp->id[inputid] == inputid){
	printf("The student we are looking for has an id of %d and an age of %d \n", inputid,sp->age[inputid]);
	printf("The Id has been found\n");
	return inputid;
    }
    else{
	printf("The student we are looking for has an id of %d\n", inputid);
	printf("There is no student with that id\n");
	return -1;
    }
}

void insertID(SET *sp, int inputid, int inputage){ //inserts the person with an given id and age into its respective arrays
    sp->id[inputid] = inputid;
    sp->age[inputid] = inputage;
}

void deleteID(SET *sp, int inputid){ //deletes the person given an id and removes the id and age from its respective arrays
    assert(sp!= NULL);
    assert (inputid != 0);
    if (sp->id[inputid] == inputid){
	printf("The student we are looking for has an id of %d and an age of %d \n", inputid,sp->age[inputid]);
	printf("Deletion was successful! \n");
	sp->id[inputid] = 0;
	sp->age[inputid] = 0;
    }
    else{
	printf("The student we are looking for has an id of %d \n", inputid);
	printf("Deletion failed\n");
    }
}



