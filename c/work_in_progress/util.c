#include "engine.h"

void db(char * say,double a){
	printf("%s:%f\n",say,a);
}


void initialize(int array[][X_MAX - X_MIN][3], int color[]){

	//char line[20];
	int i, j;
	
	//snprintf(line, sizeof(line), "P3 500 500 255\n");
	//write (file, line, strlen(line));
	
	for(i=0; i < (Y_MAX - Y_MIN); i ++){
		for(j=0; j < (X_MAX - X_MIN); j++){
			array[i][j][0] = color[0];
			array[i][j][1] = color[1];
			array[i][j][2] = color[2];
		}		 
	}
}

void push(int array[][X_MAX - X_MIN][3],int file){
	char line[20];
	int i,j;

	snprintf(line, sizeof(line), "P3 %d %d 255\n",(X_MAX - X_MIN),(Y_MAX - Y_MIN));
	write (file, line, strlen(line));
	for(i=0; i < 500; i ++){
			for(j=0; j < 500; j++){
				snprintf(line, sizeof(line), "%d %d %d\n", array[i][j][0], array[i][j][1], array[i][j][2]);
				write(file, line, strlen(line));
			}		 
		}
}

