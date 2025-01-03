#include <stdlib.h>
#include <stdio.h>
#include "logs.h"
#include "entities.h"

//Creo que en un futuro seria mas eficiente no usar void** porque las direcciones de 
//memoria importantes no van a ser contiguas
//typedef struct arraylist {
	//void** list; 
	//int maxsize;
	//int current_size;
//} ArrayList;

void initArrayList(ArrayList* this, FILE* logfile) {
	log_message(logfile, "initArrayList start\n");	
	this->maxsize = 16;
	this->current_size = 0;
	this->list = malloc(sizeof(void*) * this->maxsize);
	log_message(logfile, "initArrayList end\n");	
}
//O(1)
void addArrayList(ArrayList* this, void* ptr) {
	if(this->current_size == this->maxsize) {
		this->maxsize = this->maxsize * 2;
		this->list = realloc(this->list, sizeof(void*) * this->maxsize);
	}
	this->list[this->current_size] = ptr;
	this->current_size++;
}
//O(1)
void fastRemoveArrayList(ArrayList* this, int i) {
	this->list[i] = this->list[this->current_size-1];
	this->current_size--;
}
//O(n)
void removeArrayListByIndex(ArrayList* this, int index) {
	for(int i = index; i < this->current_size; i++) {
		if(i+1 == this->current_size) {
			this->current_size--;
		}else {
			this->list[i] = this->list[i + 1];
		}
	}
}
void printArrayList(FILE* logfile, ArrayList* this) {
	log_message(logfile, "[");
	for(int i = 0; i < this->current_size; i++) {
		if(i != 0) {
			log_message(logfile, ", ");
		}
		Entity* entity = (Entity*) this->list[i];
		log_message(logfile, "%c", entity->c);
	}
	log_message(logfile, "]");
}
void printArrayListPos(FILE* logfile, ArrayList* this) {
	log_message(logfile, "[");
	for(int i = 0; i < this->current_size; i++) {
		if(i != 0) {
			log_message(logfile, ", ");
		}
		Entity* entity = (Entity*) this->list[i];
		log_message(logfile, "%c (%d, %d)", entity->c, entity->posX, entity->posY);
	}
	log_message(logfile, "]");
}