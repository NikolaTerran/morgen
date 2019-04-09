#include "engine.h"

/*random snipet
	filling in polygons by drawing successive horizontal or vertial lines
	* find bottom, top && middle vertices
	* y:by -> ty;
	* y += 1
*/

int main(){
printf("Please read README.md first\n");
printf("Please also read the commit message\n");

canvas_init();

int * i;
int * j;

i = malloc( sizeof(int) * 3);
j = malloc( sizeof(int) * 3);

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



canvas_set(i,j,4,color);

color[0] = 0;
color[1] = 255;
color[2] = 0;

i[0] = 25;
j[0] = 25;
i[1] = 26;
j[1] = 26;
i[2] = 27;
j[2] = 27;
i[3] = 28;
j[3] = 28;

canvas_set(i,j,4,color);
canvas_set(i,j,4,color);
//canvas_set(i,j,4,color);//arr = arr_set(arr,i,j,4,color);

printf("hi\n");

canvas_push("hi.ppm");

return 0;


}
