#include "engine.h"
/*
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
*/

int thread_index=-1;
int restriction = 0;
int x_lim = X_MAX - X_MIN;
int global_color[3];
int *global_r;      
int *global_g;
int *global_b;



void canvas_init(){
	int y_lim = Y_MAX - Y_MIN;
	int x_lim = X_MAX - X_MIN;

	global_r = malloc(sizeof(int) * x_lim * y_lim);
	global_g = malloc(sizeof(int) * x_lim * y_lim);
	global_b = malloc(sizeof(int) * x_lim * y_lim);

	int i, j;	

    for(i = 0; i < y_lim; i++) {
        for (j = 0; j < x_lim; j++) {
                // arr.r[i * y_lim + j] = ARR_INIT_R;
                // arr.g[i * y_lim + j] = ARR_INIT_R;
                // arr.b[i * y_lim + j] = ARR_INIT_R;
        	global_r[i * y_lim + j] = ARR_INIT_R;
        	global_g[i * y_lim + j] = ARR_INIT_G;
        	global_b[i * y_lim + j] = ARR_INIT_B;
    //printf("arr[%d][%d]: %d\n",i,j,arr.list[i * y_lim + j]);
        }
    }

}

//global thread index, this will probably ruin everything in the future




/*
void * arr_set_helper(void *arguments){ 
	int * my_index = (int *)arguments;

	printf("index:%d\n",thread_index);
	//printf("In funtion \nthread id = %d\n", pthread_self()); 

	while(arg->y[thread_index] <= Y_MAX || arg->y[thread_index] > Y_MIN || arg->x[thread_index] < X_MAX || arg->x[thread_index] >= X_MIN){
            // arg->y[thread_index] = 0 - arg->y[thread_index];
            // //printf("%d\n",color[0]);
            // arg->r[(arg->y[thread_index] + Y_MAX) * x_lim + arg->x[thread_index] + X_MAX] = global_color[0];
            // arg->g[(arg->y[thread_index] + Y_MAX) * x_lim + arg->x[thread_index] + X_MAX] = global_color[1];
            // arg->b[(arg->y[thread_index] + Y_MAX) * x_lim + arg->x[thread_index] + X_MAX] = global_color[2];
            // printf("arr.r:%d\n",arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
            // printf("arr.g:%d\n",arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
            // printf("arr.b:%d\n",arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
            thread_index += THREAD;
            printf("index_while:%d\n",thread_index);
            if(thread_index >= restriction){
            	break;
            }
	}
	pthread_exit((void*)arg);
} 

/*random snipit
	filling in polygons by drawing successive horizontal or vertial lines
	* find bottom, top && middle vertices
	* y:by -> ty;
	* y += 1
*/


void canvas_set(int color[]){
	int y_lim = Y_MAX - Y_MIN;
	int x_lim = X_MAX - X_MIN;
	
	// int i = 0;

	// global_r = malloc(sizeof(int) * x_lim * y_lim);
	// global_g = malloc(sizeof(int) * x_lim * y_lim);
	// global_b = malloc(sizeof(int) * x_lim * y_lim);

    // for(i = 0; i < y_lim; i++) {
    //     for (j = 0; j < x_lim; j++) {
    //             // arr.r[i * y_lim + j] = ARR_INIT_R;
    //             // arr.g[i * y_lim + j] = ARR_INIT_R;
    //             // arr.b[i * y_lim + j] = ARR_INIT_R;
    //     	global_r[i * y_lim + j] = color[0];
    //     	global_g[i * y_lim + j] = color[1];
    //     	global_b[i * y_lim + j] = color[2];
    // //printf("arr[%d][%d]: %d\n",i,j,arr.list[i * y_lim + j]);
    //     }
    // }
	// struct Argument arg;
	// arg.r = arr.r;
	// arg.g = arr.g;
	// arg.b = arg.b;
	// arg.x = x;
	// arg.y = y;

 //    pthread_t tid[THREAD]; 
 
 //    // create threads 
 //    for(i = 0; i < THREAD; i++){
 //        pthread_create(&tid[i], NULL, arr_set_helper, (void *)&arg);
 //    }
 //    //pthread_join(tid,arr.r); 

 //    printf("arr.r:%d\n",arr.r[0]);

	// while(index < THREAD){
	// 	index = i;
	// 	i ++;
	// 	if(fork() != 0){
	// 		while(y[index] <= Y_MAX || y[index] > Y_MIN || x[index] < X_MAX || x[index] >= X_MIN){
	// 	            y[index] = 0 - y[index];
	// 	            //printf("%d\n",color[0]);
	// 	            arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[0];
	// 	            arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[1];
	// 	            arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[2];
	// 	            printf("arr.r:%d\n",arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
	// 	            printf("arr.g:%d\n",arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
	// 	            printf("arr.b:%d\n",arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
	// 	            index += THREAD;
	// 	            if(index >= res){
	// 	            	exit(0);
	// 	            }
	// 		}
	// 	}
	// } 
}


void canvas_push(char * filename){
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
				// arr.r[i * y_lim + j], 
				// arr.g[i * y_lim + j], 
				// arr.b[i * y_lim + j]);
				global_r[i * y_lim + j],
				global_g[i * y_lim + j],
				global_b[i * y_lim + j]);

			write(file, line, strlen(line));
		}		 
	}
}


/*
int offset(int x, int y, int z) { 
    return (z * xSize * ySize) + (y * xSize) + x; 
}
*/
