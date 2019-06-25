/*
Brandon Quant
*/

#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
#include <time.h>

int main (void){
    SET *sp = createDataSet(3000); //creating the dataset of 3000 students
    int id, age;
    srand(time(0));
    for (int i = 0; i <1000; i++){ //generating 1000 random students with ages and unique ids and inserting them into the id and age arrays
	id = ((rand()%2)+1)+ id;
	age = (rand()%13)+18;
	insertID (sp, id, age); 
    }
    int studentID = (rand()%2000)+1; //creating a student with a random id and searching for it
    searchID(sp, studentID);
    int studentID2 = (rand()%2000)+1; //creating another student with a random id
    int studentAge = (rand()%13)+18;
    if (searchID(sp, studentID2) != -1){ //checking if the student's id was found then delete the student's id and age from the arrays
	deleteID(sp, studentID2);
    }
    destroyDataSet(sp);
}
