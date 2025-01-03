#include <assert.h>
//TODO: Sin implementar

typedef struct nodo {
	void* valor;
	struct nodo* siguiente;
	struct nodo* anterior;
	int index;
} Nodo;
//typedef struct {
	//Nodo* cabeza;
	//Nodo* cola;
//} LinkList;

//void initLinkList(LinkList* this) {
	//this->cabeza = NULL;
	//this->cola = NULL;
//}
//void addLinkList(LinkList* this, void* valor) {
	////Crea un nodo nuevo
	//Nodo nuevoNodo;
	//nuevoNodo.valor = valor;
	//nuevoNodo.siguiente = NULL;
	//nuevoNodo.anterior = this->cabeza;
	////agrega el nodo a la lista
	//if(this->cabeza == NULL) {
		//nuevoNodo.index = 0;
		//this->cabeza = &nuevoNodo;
		//this->cola = &nuevoNodo;
	//}else {
		//nuevoNodo.index = this->cabeza->index + 1;
		//this->cabeza->siguiente = &nuevoNodo;
		//nuevoNodo.anterior = this->cabeza;
		//this.cabeza = &nuevoNodo;
	//}
//}
//void deleteLinkList(LinkList* this, int index) {
	////TODO: revisar si es mas rapido desde la cabeza o la cola
	////TODO: implementar
	//assert(0 == 1, "Sin implementar");
//}