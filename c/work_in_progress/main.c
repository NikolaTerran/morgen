#include "engine.h"

int main(){
printf("Please read README.md first\n");

////////////////////////////////
	int y_lim = Y_MAX - Y_MIN;
	int x_lim = X_MAX - X_MIN;
	key_t key = ftok("shm",65); 
	int shmid = shmget(key,sizeof(int) * x_lim * y_lim ,0666|IPC_CREAT); 
////////////////////////////////

// struct Array arr;
// arr = arr_init(arr);

canvas_init();

int * i;
int * j;

i = malloc( sizeof(int));
j = malloc( sizeof(int));

i[0] = 0;
j[0] = 0;
i[1] = 1;
j[1] = 1;
i[2] = 2;
j[2] = 2;
i[3] = 3;
j[3] = 3;

int color[3];
color[0] = 255;
color[1] = 0;
color[2] = 0;

canvas_set(color);
//arr = arr_set(arr,i,j,4,color);

printf("hi\n");

canvas_push("hi.ppm");

return 0;


}
