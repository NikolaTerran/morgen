#include "engine.h"

struct Array arr_init(struct Array arr){
	int y_lim = Y_MAX - Y_MIN;
	int x_lim = X_MAX - X_MIN;
	
	arr.list = malloc(sizeof(int) * x_lim * y_lim);
	int i, j;
	

    for(i = 0; i < y_lim; i++) {
        for (j = 0; j < x_lim; j++) {
                arr.list[i * y_lim + j] = ARR_INIT_VAL;
    //printf("arr[%d][%d]: %d\n",i,j,arr.list[i * y_lim + j]);
        }
    }
    
    return arr;
}
/*
int arr_traverse(int x, int y, int z){
	printf("%d\n",
}
*/
void arr_push(struct Array arr, char * filename){
	int y_lim = Y_MAX - Y_MIN;
	int x_lim = X_MAX - X_MIN;

	char line[20];

	int i,j,file;
	file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);

	snprintf(line, sizeof(line), "P3 %d %d 255\n",x_lim,y_lim);
	write (file, line, strlen(line));
	for(i = 0; i < y_lim; i++){
			for(j = 0; j < x_lim; j++){
			//printf("hi\n");
			//printf("oh\n%d %d %d\n",arr.list[i * y_lim + j], 
			//		arr.list[i * y_lim + j], 
			//		arr.list[i * y_lim + j]);
				snprintf(line, sizeof(line), "%d %d %d\n", 
					arr.list[i * y_lim + j] / 1000 / 1000, 
					arr.list[i * y_lim + j] / 1000 % 1000, 
					arr.list[i * y_lim + j] % 1000);
				write(file, line, strlen(line));
			}		 
		}
}


/*
int offset(int x, int y, int z) { 
    return (z * xSize * ySize) + (y * xSize) + x; 
}
*/
