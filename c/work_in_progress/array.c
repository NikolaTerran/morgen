#include "engine.h"

struct Array arr_init(struct Array arr){
	int y_lim = Y_MAX - Y_MIN;
	int x_lim = X_MAX - X_MIN;
	
	arr.r = malloc(sizeof(int) * x_lim * y_lim);
	arr.g = malloc(sizeof(int) * x_lim * y_lim);
	arr.b = malloc(sizeof(int) * x_lim * y_lim);
	
	int i, j;
	

    for(i = 0; i < y_lim; i++) {
        for (j = 0; j < x_lim; j++) {
                arr.r[i * y_lim + j] = ARR_INIT_R;
                arr.g[i * y_lim + j] = ARR_INIT_R;
                arr.b[i * y_lim + j] = ARR_INIT_R;
    //printf("arr[%d][%d]: %d\n",i,j,arr.list[i * y_lim + j]);
        }
    }
    
    return arr;
}

struct arr_set_helper(struct Array arr, int *x, int *y, int index, int color[]){
	if(index < 4){
		arr_set_helper(arr, *x, *y, index + 1, color);
		if(fork() != 0){
			index = 0;
		    while(y[index] <= Y_MAX || y[index] > Y_MIN || x[index] < X_MAX || x[index] >= X_MIN){
		            y[index] = 0 - y[index];
		            arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[0];
		            arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[1];
		            arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[2];
		            index += 4;
		            if(index >= res){
		            	exit(0);
		            }
			}
		}
	}
}

struct Array arr_set(struct Array arr, int *x, int *y, int res, int color[]){
	int index;
	int x_lim = X_MAX - X_MIN;
	

	
	if(fork() != 0){
		index = 1;
    	while(y[index] <= Y_MAX || y[index] > Y_MIN || x[index] < X_MAX || x[index] >= X_MIN){
                y[index] = 0 - y[index];
                arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[0];
                arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[1];
                arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[2];
                index += 4;
    	}
	    exit(0);
	}
	
	if(fork() != 0){
		index = 2;
       	while(y[index] <= Y_MAX || y[index] > Y_MIN || x[index] < X_MAX || x[index] >= X_MIN){
                y[index] = 0 - y[index];
                arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[0];
                arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[1];
                arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[2];
                index += 4;
                if(index >= res){
                	exit(0);
                }
    	}
	}
	
	index = 3;
	while(y[index] <= Y_MAX || y[index] > Y_MIN || x[index] < X_MAX || x[index] >= X_MIN){
            y[index] = 0 - y[index];
            arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[0];
            arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[1];
            arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[2];
            if(index >= res){
                	exit(0);
            }
	}

	
	
	return arr;
}

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
				snprintf(line, sizeof(line), "%d %d %d\n", 
					arr.r[i * y_lim + j], 
					arr.g[i * y_lim + j], 
					arr.b[i * y_lim + j]);
				write(file, line, strlen(line));
			}		 
		}
}


/*
int offset(int x, int y, int z) { 
    return (z * xSize * ySize) + (y * xSize) + x; 
}
*/
