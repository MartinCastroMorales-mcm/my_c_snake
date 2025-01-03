#include <stdio.h>
#include <assert.h>


//int read_line(char* line, long buffer_size) {

//}

//Leer todas las lineas agregarlas a como entidades si son distintas a ' '

int build_map(char* mapfile_path) {
	FILE* file_map = fopen(mapfile_path, "r");
	assert(file_map != NULL);
	char* lineptr = NULL;
	size_t buffer_size = 0;
	long rc = getline(&lineptr, &buffer_size, file_map);
	while(rc != -1) {
		return 0;	 
	}
	return 1;
}