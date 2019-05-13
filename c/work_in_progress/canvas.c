#include "engine.h"

int x_lim;
int y_lim;
int thread_index=-1;
int global_res = 0;
int global_color[3];
int *global_r;
int *global_g;
int *global_b;

int *global_x;
int *global_y;
int *global_canvas_z;

struct Layer lay_init(){
	struct Layer lay;

	y_lim = Y_MAX - Y_MIN;
	x_lim = X_MAX - X_MIN;

	lay.r = malloc(sizeof(int) * x_lim * y_lim);
	lay.g = malloc(sizeof(int) * x_lim * y_lim);
	lay.b = malloc(sizeof(int) * x_lim * y_lim);
	lay.z = malloc(sizeof(int) * x_lim * y_lim);

	int i, j;

  for(i = 0; i < y_lim; i++) {
    for (j = 0; j < x_lim; j++) {
    	lay.r[i * y_lim + j] = ARR_INIT_R;
    	lay.g[i * y_lim + j] = ARR_INIT_G;
    	lay.b[i * y_lim + j] = ARR_INIT_B;
			lay.z[i * y_lim + j] = ARR_INIT_Z;
		}
  }

	return lay;
}

/*
void layer_set_s(struct Layer lay, int x, int y, int z, int color[]){

	if(y > Y_MAX || y <= Y_MIN || x >= X_MAX || x < X_MIN){
	 printf("Error: canvas_set_s outof bound\n");
	 printf("Bound: y <= Y_MAX || y > Y_MIN || x < X_MAX  || x >= X_MIN\n");
	 if(y > Y_MAX){
		 printf("DEBUG: y is suppose to be <= %d but is %d\n",Y_MAX,y);
	 }
	 if(y <= Y_MIN){
		 printf("DEBUG: y is suppose to be > %d but is %d\n",Y_MIN,y);
	 }
	 if(x >= X_MAX){
		 printf("DEBUG: x is suppose to be < %d but is %d\n",X_MAX,x);
	 }
	 if(x < X_MIN){
		 printf("DEBUG: x is suppose to be >= %d but is %d\n",X_MIN,x);
	 }
	 //exit(1);
	}else{
	 int local_y =  0 - y;
	 int val = (local_y + Y_MAX) * x_lim + x + X_MAX;
	 lay.z[100] = 122501;

	 printf("dsada:%d\n",lay.z[122501]);
	 if(lay.z[val] == ARR_INIT_Z){



		 lay.r[val] = global_color[0];
		 lay.g[val] = global_color[1];
		 lay.b[val] = global_color[2];
	 }else if(z < global_z[val]){
		 r[val] = global_color[0];
		 global_g[val] = global_color[1];
		 global_b[val] = global_color[2];
	 }
	}
}
*/

void canvas_init(){
	y_lim = Y_MAX - Y_MIN;
	x_lim = X_MAX - X_MIN;

	global_r = malloc(sizeof(int) * x_lim * y_lim);
	global_g = malloc(sizeof(int) * x_lim * y_lim);
	global_b = malloc(sizeof(int) * x_lim * y_lim);
	global_canvas_z = malloc(sizeof(int) * x_lim * y_lim);

	int i, j;

    for(i = 0; i < y_lim; i++) {
        for (j = 0; j < x_lim; j++) {
        	global_r[i * y_lim + j] = ARR_INIT_R;
        	global_g[i * y_lim + j] = ARR_INIT_G;
        	global_b[i * y_lim + j] = ARR_INIT_B;
					global_canvas_z[i * y_lim + j] = ARR_INIT_Z;
				}
    }
		//printf("global_z:%d\n",global_z[1000]);
}



void * canvas_set_helper(void * arg){
	int index = (int *)arg;

	while(global_y[index] <= Y_MAX || global_y[index] > Y_MIN || global_x[index] < X_MAX || global_x[index] >= X_MIN){
		//printf("global_y:%d\n",global_y[index]);
		//printf("global_x:%d\n",global_x[index]);
        //int local_y = 0 - global_y[index];

				if(index >= global_res){
        	break;
        }
        int local_y =  0 - global_y[index];
        //global_y[index] = 0 - global_y[index];
        //printf("local_y: %d\n",local_y);
        global_r[(local_y + Y_MAX) * x_lim + global_x[index] + X_MAX] = global_color[0];
        global_g[(local_y + Y_MAX) * x_lim + global_x[index] + X_MAX] = global_color[1];
        global_b[(local_y + Y_MAX) * x_lim + global_x[index] + X_MAX] = global_color[2];

        index += THREAD;

	}

	pthread_exit(NULL);
}

void canvas_set_s(int x, int y,
	 int z,
	 int color[]){
	if(y > Y_MAX || y <= Y_MIN || x >= X_MAX || x < X_MIN){
		printf("Error: canvas_set_s outof bound\n");
		printf("Bound: y <= Y_MAX || y > Y_MIN || x < X_MAX  || x >= X_MIN\n");
		if(y > Y_MAX){
			printf("DEBUG: y is suppose to be <= %d but is %d\n",Y_MAX,y);
		}
		if(y <= Y_MIN){
			printf("DEBUG: y is suppose to be > %d but is %d\n",Y_MIN,y);
		}
		if(x >= X_MAX){
			printf("DEBUG: x is suppose to be < %d but is %d\n",X_MAX,x);
		}
		if(x < X_MIN){
			printf("DEBUG: x is suppose to be >= %d but is %d\n",X_MIN,x);
		}
		//exit(1);
	}else{

    int local_y =  0 - y;
		int val = (local_y + Y_MAX) * x_lim + x + X_MAX;
		//global_z[100] = 123123;
		//printf("local_z:%d\n",z);
		//printf("dsada:%d\n",global_z[val]);
		if(global_canvas_z[val] == ARR_INIT_Z){
			//printf("global_canvas_val:%d\n",global_canvas_z[val]);


			global_r[val] = color[0];
			global_g[val] = color[1];
			global_b[val] = color[2];
			global_canvas_z[val] = z;
		}else if(z < global_canvas_z[val]){
			//printf("global_canvas_val:%d\n",global_canvas_z[val]);
			global_r[val] = color[0];
			global_g[val] = color[1];
			global_b[val] = color[2];
			global_canvas_z[val] = z;
		}
	}
}

void canvas_set_p(int *x,int *y,int res,int color[]){

    pthread_t thread_id[THREAD];
 	int index[THREAD];
 	int i;

 	global_x = x;
 	global_y = y;
 	// global_x = realloc(res * sizeof(int));
 	// global_y = realloc(res * sizeof(int));
 	global_res = res;


 	global_color[0] = color[0];
 	global_color[1] = color[1];
 	global_color[2] = color[2];
    // create threads
    for(i = 0; i < THREAD; i++){
    	index[i] = i;
        pthread_create(&thread_id[i], NULL, canvas_set_helper, (void *)index[i]);
    }

    for(i = 0; i < THREAD; i++){
    	pthread_join(thread_id[i], NULL);
	}
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
			//printf("asdaploqw\n" );
			snprintf(line, sizeof(line), "%d %d %d\n",
				global_r[i * y_lim + j],
				global_g[i * y_lim + j],
				global_b[i * y_lim + j]);

			write(file, line, strlen(line));
		}
	}

}
