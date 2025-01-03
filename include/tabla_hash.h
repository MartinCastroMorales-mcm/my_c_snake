#ifndef TABLA_HASH_H
#define TABLA_HASH_H

typedef struct key_value_pair {
	void* value;
	int key;
    struct key_value_pair* next;
} KeyValuePair;
typedef struct tabla_hash {
	KeyValuePair* datos;
	int max_size;	
	int used_keys;
} TablaHash;

void initTablaHash(TablaHash* this);
void addTablaHash(TablaHash* this, int key, void* value);
void* getValueByKey(TablaHash* this, int key);
void deleteTablaHash(TablaHash* this, int key);
TablaHash* resize(TablaHash* this);
void downsize(TablaHash* this);

#endif