#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include "entities.h"
#include "arraylist.h"
#include "game_container.h"
#include "logs.h"

//typedef struct game_container {
	//WINDOW* window;
	////arraylist
	//ArrayList* listOfEntities;
	////file for logs
	//FILE * logfile;
//} GameContainer;

void initGameContainer(GameContainer* gc) {
	gc->window = initscr();
	gc->logfile = fopen("debug.log", "w");
	if(!gc->logfile) {
		exit(1);
	}
	//Caracteristicas de WINDOW
	keypad(gc->window, true); // ver en man
	nodelay(gc->window, true); //ver en man
	log_message(gc->logfile, "pacman game start\n");
	ArrayList* listOfEntities = malloc(sizeof(ArrayList));
	initArrayList(listOfEntities, gc->logfile);
	gc->listOfEntities = listOfEntities;
}

int searchByCordinate(ArrayList* Lista, int posX, int posY) {
	//TODO optimizar esto con una tabla hash
	for(int i = 0; i < Lista->current_size; i++) {
		Entity* entity = (Entity*) Lista->list[i];
		if(entity->posX == posX && entity->posY == posY) {
			return i;
		}
	}
	return -1;
}