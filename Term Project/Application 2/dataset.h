/*
Brandon Quant
COEN12
*/

#ifndef DATASET_H
#define DATASET_H

typedef struct set SET;

SET *createDataSet(int maxElts);

void destroyDataSet (SET *sp);

int searchID (SET *sp, int inputid);

void insertID(SET *sp, int inputid, int inputage);

void deleteID(SET *sp, int inputid);

#endif


