#ifndef GAME_CONTAINER_H
#define GAME_CONTAINER_H
#include "arraylist.h"
#include <curses.h>

typedef struct game_container {
	WINDOW* window;
	//arraylist
	ArrayList* listOfEntities;
	//file for logs
	FILE * logfile;
	int minWidth;
	int maxWidth;
	int maxHeight;
	int minHeight;
	int points;
} GameContainer;
typedef struct stats {
	int points;
} Stats;

void initGameContainer(GameContainer* gc);

int searchByCordinate(ArrayList* Lista, int posX, int posY);

#endif