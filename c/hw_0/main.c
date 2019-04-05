#include "engine.h"

int main(){
printf("Please read README.md first\n");


struct Array arr;
arr = arr_init(arr);

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

arr = arr_set(arr,i,j,4,color);

arr_push(arr,"hi.ppm");

return 0;


}
