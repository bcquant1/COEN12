/*
Brandon Quant
COEN 12 Term Project
Application 3 Main
*/

#include <time.h>
#include "dataset.h"

int main(void){
    LIST *lp = createList();
    SET *sp = createSet();
    int id,age;
    srand(time(0));
    for(int i = 0; i < 1000; i++){
	id = (rand()%2 + 1) + id;
	age = (rand()%13) + 18;
	addItem(sp,lp,id,age);
    }
    int studentID = (rand()%2000)+1;
    int studentage = (rand()&13)+18;
    searchId(sp,lp,id);
    int studentId2 = (rand()%2000)+1;
    if (searchId(sp,lp, studentId2) != -1){
	removeItem(sp,lp, studentId2,studentage);
    }
    printf("The max age gap is %d\n", maxAgeGap(sp,lp));
    destroySet(sp);
}

