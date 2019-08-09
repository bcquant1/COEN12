/*Brandon Quant
COEN 12
Project 5
Huffman Code
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "pack.h"
#include "pqueue.h"
#include <ctype.h>

//defines the parent, left and right child
#define p(x) ((x-1)/2);
#define l(x) ((x*2)+1);
#define r(x) ((x*2)+2);

typedef struct node NODE;
int nodecompare (NODE *n1, NODE *n2);

NODE* makeNode (int data, NODE *left, NODE *right){ //makes the parent node and links the left and right child to it, runtime: O(1)
    NODE *np = malloc(sizeof(NODE));
    np-> parent = NULL;
    assert (np!=NULL);
    np->count = data;
    if (left != NULL){
	left->parent = np;
    }
    if (right != NULL){
	right->parent = np;
    }
    return np;
}

int main (int argc, char*argv[]){ // runtime: O(n)
    FILE *fp;
    PQ *pq;
    pq = createQueue(nodecompare); 
    int arr[257]; //array that shows the occurences of each letter
    int c;
    NODE *leaves[257];
    NODE *n1;
    NODE *n2;
    NODE *traverse;
    
    fp = fopen(argv[1], "r"); //opens and reads the file
    assert(argc != 0 && fp!= NULL);
    for (int i = 0; i < 257; i++){ //initializing the two arrays
	arr[i] = 0;
	leaves[i] = NULL;
    }
    while ((c = getc(fp)) != EOF){ //counts the number of occurences of each letter in the file
	arr[c]++;
    }  
    fclose(fp); //closes the file

    for (int i = 0; i < 256; i++){ //makes the binary tree of just the leaf for each character
	if (arr[i] > 0){
	    leaves[i] = makeNode(arr[i], NULL, NULL);
	    addEntry(pq, leaves[i]);
	}
    }
    addEntry(pq, (leaves[256] = makeNode(0, NULL, NULL)));//adding the last element to be of 0 count
    
    while(numEntries(pq) > 1){ //runs until there is only 1 tree left
	int temp_count;
	n1 = removeEntry(pq); //removing the two lowest priority queues
	n2 = removeEntry(pq);
	temp_count = n1->count + n2->count; //count for the new tree
	addEntry(pq, makeNode(temp_count, n1,n2));
    }

    int bitcount = 0;
    for (int i = 0; i < 257; i++){ // finding the bit count for each character in the file
	if (leaves[i] != NULL){
	    for (traverse = leaves[i], bitcount = 0; traverse->parent != NULL; traverse = traverse->parent){
		bitcount++;
	    }
	    if(isprint(i) != 0){
		printf("%c : %d", i , arr[i]);
	    }
	    else{
		printf("%03o :  %d", i , arr[i]);

	    }
	    printf(" x %d bits = %d bits\n", bitcount, arr[i] * bitcount);
	}
    }
    pack(argv[1], argv[2], leaves);    
}

int nodecompare(NODE *n1, NODE *n2){ //returns the added count from n1 and n2, runtime: O(1)
    assert (n1 != NULL && n2 != NULL);
    int counter;
    counter =n1->count - n2->count;
    return counter;
}




