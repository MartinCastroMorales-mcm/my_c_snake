#include <stdlib.h>
#include "tabla_hash.h"
#include <assert.h>


//typedef struct key_value_pair {
	//void* value;
	//int key;
//} KeyValuePair;
//typedef struct tabla_hash {
	//KeyValuePair* datos;
	//int max_size;	
	//int used_keys;
//} TablaHash;

void initTablaHash(TablaHash* this) {
	this->max_size = 64;	
	this->datos = malloc(sizeof(KeyValuePair) * this->max_size);
}

//O(1)
void addTablaHash(TablaHash* this, int key, void* value) {
	//assert(key >= 0)
	this->used_keys++;
	if(this->used_keys > this->max_size) {
		resize(this);
	}
	int modulo = key % this->max_size;
	if(this->datos[modulo].next == NULL && this->datos[modulo].value == NULL) {
		KeyValuePair key_value_pair;
		key_value_pair.key = key;
		key_value_pair.value = value;
		key_value_pair.next = NULL;
		this->datos[modulo] = key_value_pair;
		return;
	}
	//TODO: que pasa si solo hay un elemento
	// Agregar caso de colision
	// Encontrar el ultimo elemento de la lista
	KeyValuePair* nodo = &this->datos[modulo];
	while(nodo->next != NULL) {
		if(nodo->key == key) {
			//Se va a remplazar el valor del nodo
			nodo->value = value;
			return;
		}
		nodo = nodo->next;
	}
	//Ahora nodo es el ultimo
	KeyValuePair* nuevoNodo = malloc(sizeof(KeyValuePair));
	nuevoNodo->key = key;
	nuevoNodo->value = value;
	nuevoNodo->next = NULL;
	nodo->next = nuevoNodo;
	return;
}
//O(1)
void* getValueByKey(TablaHash* this, int key) {
	int i = key % this->max_size;
	KeyValuePair* key_value_pair = &this->datos[i];
	while(key_value_pair->next != NULL){
		if(key_value_pair->key == key) {
			return key_value_pair->value;
		}
		key_value_pair = key_value_pair->next;
	}
	//No se encontro la llave buscada
	return NULL;
}
//O(1)
void deleteTablaHash(TablaHash* this, int key) {
	int i = key % this->max_size;
	KeyValuePair* key_value_pair = &this->datos[i];
	KeyValuePair* prev = NULL;
	while(key_value_pair->next != NULL) {
		if(key_value_pair->key == key) {
			//delete
			if(prev == NULL) {
				key_value_pair->value = NULL;
				if(key_value_pair->next != NULL) {
					this->datos[i] = *key_value_pair->next;	
				}
				return;
			}
			//Se borra uno dentro de una linklist
			prev->next = key_value_pair->next;
			free(key_value_pair);
			return;
		}
		prev = key_value_pair;
		key_value_pair = key_value_pair->next;
	}
}

TablaHash* resize(TablaHash* this) {
	assert(this->max_size < this->used_keys);

	//TablaHash* nuevaTabla = malloc(sizeof(tabla_hash))
	//for(int i = 0; i < this->max_size; i++) {
		//addTablaHash(nuevaTabla, this->datos[i]);	
	//}
	//free(this);
	return NULL;
}
//void downsize(TablaHash* this) {

//}

//Para decidir cuando resize y downsize
//https://courses.csail.mit.edu/6.006/spring11/rec/rec07.pdf