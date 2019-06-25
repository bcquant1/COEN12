/*
Brandon Quant
*/

#ifndef DATASET_H
#define DATASET_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct node NODE;
typedef struct list LIST;
typedef struct set SET;

LIST* createList();

SET* createSet();

void destroyList(LIST *lp);

void destroySet (SET *sp);

int searchAge (SET *sp, LIST *lp, int age);

int searchId (SET *sp, LIST *lp, int id);

void addItem(SET *sp, LIST *lp, int id, int age);

void removeItem(SET *sp, LIST *lp, int id, int age);

int maxAgeGap(SET *sp, LIST *lp);
# endif 

