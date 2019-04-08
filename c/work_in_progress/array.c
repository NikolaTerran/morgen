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


//global thread index, this will probably ruin everything in the future
int thread_index=-1;

void * arr_set_helper(void *arguments){ 
	struct Array *my_arr = arguments;

	pthread_mutex_t mutex1;
	
	pthread_mutex_lock( &mutex1 );
	thread_index++;
	pthread_mutex_unlock(&mutex1); 

	printf("index:%d\n",thread_index);
	//printf("In funtion \nthread id = %d\n", pthread_self()); 

	my_arr->r[0] = 133;
	pthread_exit((void*)my_arr);
/*
    	while(index < THREAD){
		index = i;
		i ++;
		if(fork() != 0){
			while(y[index] <= Y_MAX || y[index] > Y_MIN || x[index] < X_MAX || x[index] >= X_MIN){
		            y[index] = 0 - y[index];
		            //printf("%d\n",color[0]);
		            arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[0];
		            arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[1];
		            arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[2];
		            printf("arr.r:%d\n",arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
		            printf("arr.g:%d\n",arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
		            prin	tf("arr.b:%d\n",arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
		            index += THREAD;
		            if(index >= res){
		            	exit(0);
		            }
			}
		}
	}
    */
} 

/*random snipit
	filling in polygons by drawing successive horizontal or vertial lines
	* find bottom, top && middle vertices
	* y:by -> ty;
	* y += 1
*/

struct Array arr_set(struct Array arr, int *x, int *y, int res, int color[]){
	int index;
	int x_lim = X_MAX - X_MIN;
	
	int i = 0;

	struct Argument{    	
    	int * r;
    	int * g;
    	int * b;
    	int index;
	};
	
	
    pthread_t tid[THREAD]; 
 
    // create threads 
    for(i = 0; i < THREAD; i++){
        pthread_create(&tid[i], NULL, arr_set_helper, (void *)&arr);
    }
    //pthread_join(tid,arr.r); 

    printf("arr.r:%d\n",arr.r[0]);
/*
	while(index < THREAD){
		index = i;
		i ++;
		if(fork() != 0){
			while(y[index] <= Y_MAX || y[index] > Y_MIN || x[index] < X_MAX || x[index] >= X_MIN){
		            y[index] = 0 - y[index];
		            //printf("%d\n",color[0]);
		            arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[0];
		            arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[1];
		            arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX] = color[2];
		            printf("arr.r:%d\n",arr.r[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
		            printf("arr.g:%d\n",arr.g[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
		            printf("arr.b:%d\n",arr.b[(y[index] + Y_MAX) * x_lim + x[index] + X_MAX]);
		            index += THREAD;
		            if(index >= res){
		            	exit(0);
		            }
			}
		}
	} 
*/
	
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
