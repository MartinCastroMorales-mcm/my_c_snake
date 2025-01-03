#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/entities.h"
#include <stdarg.h>
#include "../include/arraylist.h"
#include "game_container.h"
#include "logs.h"
#include <time.h>

void game_over() {
	exit(0);
}
void setBounds(GameContainer* gc, int minX, int maxX, int minY, int maxY) {
	gc->minWidth = minX;
	gc->maxWidth = maxX;
	gc->minHeight = minY;
	gc->maxHeight = maxY;
	//write top
	for(int i = minX; i < maxX + 1; i++) {
		Entity* entity = malloc(sizeof(entity));
		*entity = (Entity) {
			.posX = i,
			.posY = minY,//Se usa el minimo porque 0,0 es la esquina superior izquierda
			.c = 'W',
			.mtype = wall
		};
		addArrayList(gc->listOfEntities, (void*) entity);
	}
	//write left
	for(int i = minY + 1; i < maxY + 1; i++) { //minY + 1 porque ya se escribio el minY en top
		Entity* entity = malloc(sizeof(entity));
		*entity = (Entity) {
			.posX = minX,
			.posY = i,//Se usa el minimo porque 0,0 es la esquina superior izquierda
			.c = 'W',
			.mtype = wall
		};
		addArrayList(gc->listOfEntities, (void*) entity);
	}
	//write right
	for(int i = minY + 1; i < maxY + 1; i++) { //minY + 1 porque ya se escribio el minY en top
		Entity* entity = malloc(sizeof(entity));
		*entity = (Entity) {
			.posX = maxX,
			.posY = i,//Se usa el minimo porque 0,0 es la esquina superior izquierda
			.c = 'W',
			.mtype = wall
		};
		addArrayList(gc->listOfEntities, (void*) entity);
	}
	//write bottom
	for(int i = minX + 1; i < maxY; i++) { //minY + 1 porque ya se escribio el minY en top lo mismo con el -1
		Entity* entity = malloc(sizeof(entity));
		*entity = (Entity) {
			.posX = i,
			.posY = maxY,//Se usa el minimo porque 0,0 es la esquina superior izquierda
			.c = 'W',
			.mtype = wall
		};
		addArrayList(gc->listOfEntities, (void*) entity);
	}
}
void addTail(GameContainer* gc, Player* player) {
	//TODO: iniciar ArrayList
	//get tail
	Entity* entity = malloc(sizeof(Entity));
	entity->posX = player->posX;
	entity->posY = player->posY;
	entity->c = 'S';
	entity->mtype = tail;
	addArrayList(player->listOfTails, entity);
	addArrayList(gc->listOfEntities, entity);
}
void createFruit(GameContainer* gc) {
	srand(time(NULL));
	int rc = -1;
	int fruitX = rand() % 9 + 1; //min 1 max 9
	int fruitY = rand() % 9 + 1;
	do {
		fruitX = rand() % 9 + 1; //min 1 max 9
		fruitY = rand() % 9 + 1;
		rc = searchByCordinate(gc->listOfEntities, fruitX, fruitY);
		log_message(gc->logfile, "createFruit rc: %d\n", rc);
	}while(rc != -1); //Repetir hasta que se encuentre un espacio vacio
	Entity* entity = malloc(sizeof(entity));
	*entity = (Entity) {
		.posX = fruitX,
		.posY = fruitY,
		.c = 'F',
		.mtype = fruit,
	};
	addArrayList(gc->listOfEntities, (void*) entity);
}

void move_snake(GameContainer* gc, Player* player, int newPosX, int newPosY) {
	log_message(gc->logfile, "move_snake\n");
	if(player->listOfTails->current_size == 0) {
		player->posX = newPosX;
		player->posY = newPosY;
		return;
	}
	Entity* tail = NULL;
	Entity* prevTail = NULL;
	for(int i = player->listOfTails->current_size - 1 ; i > 0; i--) {
		tail = (Entity*) player->listOfTails->list[i];
		prevTail = (Entity*) player->listOfTails->list[i - 1];
		tail->posX = prevTail->posX;
		tail->posY = prevTail->posY;
	}
	tail = (Entity*) player->listOfTails->list[0];
	tail->posX = player->posX;
	tail->posY = player->posY;
	
	player->posX = newPosX;
	player->posY = newPosY;
}

void update_game(GameContainer* gc, Player* player) {
	int pressed = wgetch(gc->window); //ver en man
	if(pressed == KEY_LEFT) {
		player->dirX = -1;
		player->dirY = 0;
	}
	if(pressed == KEY_RIGHT) {
		player->dirX = 1;
		player->dirY = 0;
	}
	if(pressed == KEY_UP) {
		player->dirX = 0;
		player->dirY = -1;
	}
	if(pressed == KEY_DOWN) {
		player->dirX = 0;
		player->dirY = 1;
	}
	int newPosX = player->posX + player->dirX;
	int newPosY = player->posY + player->dirY;

	//TODO: Implementar colisiones usando una tabla hash
	int i = searchByCordinate(gc->listOfEntities, newPosX, newPosY);
	Entity* entidad = (Entity*) gc->listOfEntities->list[i];
	log_message(gc->logfile, "entidad es nulo %zu ¿?\n", entidad);
	if(i == -1) {
		move_snake(gc, player, newPosX, newPosY);
		return;
	}
	log_message(gc->logfile, "entidad c: %c ¿?\n", entidad->c);
	switch(entidad->c) {
		case 'W':
		case 'S':
			log_message(gc->logfile, "game over\n");
			game_over();
			break;
		case 'F':
			move_snake(gc, player, newPosX, newPosY);
			removeArrayListByIndex(gc->listOfEntities, i);
			createFruit(gc);
			addTail(gc, player);
			gc->points += 10;
			printArrayList(gc->logfile, gc->listOfEntities);
			break;
	}
}
void render_entities(GameContainer* gc) {
	for(int i = 0; i < gc->listOfEntities->current_size; i++) {
		Entity* entity = (Entity*) gc->listOfEntities->list[i];
		const char tmp[2] = { entity->c, '\0' } ;
		mvaddstr(entity->posY, entity->posX, tmp);
		//log_message(gc->logfile, "render entity: (%d, %d) \n", entity->posX, entity->posY);
	}
}
void render_game(GameContainer* gc, Player* player) {
	erase(); //ver en man
	mvaddstr(player->posY, player->posX, "@");
	render_entities(gc);
	//TODO: Para hacer las coliciones tener una tabla hash donde
	//Un par ordenado te entrega un valor
}

void add_test_wall(GameContainer* gc) {
	Entity* entity = malloc(sizeof(Entity));
	*entity = (Entity) {
		.posX = 3,
		.posY = 3,
		.c = 'W',
		.mtype = wall
	};
	addArrayList(gc->listOfEntities, (void*) entity);
	Entity* entity2 = malloc(sizeof(Entity));
	*entity2 = (Entity) {
		.posX = 3,
		.posY = 4,
		.c = 'W',
		.mtype = wall
	};
	addArrayList(gc->listOfEntities, (void*) entity2);
}

int main(void) {
	GameContainer gc;
	initGameContainer(&gc);
	Player player;
	initPlayer(&player, &gc);
	//add_test_wall(&gc);
	setBounds(&gc, 0, 10, 0, 10);
	createFruit(&gc);
	while(true) {
		update_game(&gc, &player);
		render_game(&gc, &player);
	usleep(200000);
	}
	endwin();
	printf("hello world\n");
	return 0;
}