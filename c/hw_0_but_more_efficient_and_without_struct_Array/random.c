#include "engine.h"

int* sys_random(int size){
	int *buffer;
	buffer = malloc(sizeof(int) * size );
	
	printf("initiating...this may take several minites\n");
	
	FILE* file = fopen("/dev/urandom", "r");
	fread(buffer, sizeof(int), size ,file);
	
	//close(file);
	//printf("wut\n");
	return buffer;
}


