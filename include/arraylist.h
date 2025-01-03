#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include <stdio.h>

typedef struct arraylist {
	void** list; 
	int maxsize;
	int current_size;
} ArrayList;

void initArrayList(ArrayList* this, FILE* file);
//O(1)
void addArrayList(ArrayList* this, void* ptr);
//O(1)
void fastRemoveArrayList(ArrayList* this, int i);

//O(n)
void removeArrayListByIndex(ArrayList* this, int index);

void printArrayList(FILE* logfile, ArrayList* this);

#endif