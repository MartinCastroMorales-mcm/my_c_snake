#include "entities.h"
#include "game_container.h"
#include <stdlib.h>

//typedef struct player {
	//int posX;
	//int posY;
	//int dirX;
	//int dirY;
	//char c;
//} Player;


void initPlayer(Player* player, GameContainer* gc) {
	player->posX = 4;
	player->posY = 5;
	player->dirX = 0;
	player->dirY = 0;
	player->c = '@';
	player->listOfTails = malloc(sizeof(ArrayList));
	initArrayList(player->listOfTails, gc->logfile);
}

//typedef struct wall {
	//int posX;
	//int posY;
	//char c;
//} Wall

void initWall(Wall* wall, int x, int y) {
	wall->posX = x;
	wall->posY = y;
	wall->c = 'W';
}

//typedef struct {
	//int posX;
	//int posY;
	//char c;
	//char* type;
//}Entity;

