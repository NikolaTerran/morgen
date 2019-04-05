#include "engine.h"

int main(){
printf("Please read README.md first\n");


struct Array a;
a = arr_init(a);

int * i;
int * j;

i = malloc( sizeof(int));
j = malloc( sizeof(int));

i[0] = 0;
j[0] = 0;

int color[3];
color[0] = 255;
color[1] = 0;
color[2] = 0;

a = arr_set(a,i,j,1,color);

arr_push(a,"hi.ppm");

return 0;


}
