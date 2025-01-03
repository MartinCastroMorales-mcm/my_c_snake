#ifndef ENTITIES_H
#define ENTITIES_H
#include "arraylist.h"
#include "game_container.h"



typedef struct wall {
	int posX;
	int posY;
	char c;
} Wall;

void initWall(Wall* wall, int x, int y);


typedef enum {player, wall, fruit, tail} type;
typedef struct {
	int posX;
	int posY;
	char c;
	type mtype;
	//type mtype;
} Entity;

typedef struct player {
	int posX;
	int posY;
	int dirX;
	int dirY;
	char c;
	ArrayList* listOfTails;	
} Player;

void initPlayer(Player* player, GameContainer* gc);

#endif