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

struct Matrix point;
point = mx_init(point,0);


int color[3];
color[0] = 0;
color[1] = 0;
color[2] = 0;

struct Matrix poly;
poly = mx_init_p(poly,0);

poly = mx_addsphere(poly,0,0,0,200);
poly = mx_rotate(poly,0,0.5);
mx_export(poly,color);

/*
point = mx_addsphere(point,0,0,0,100);
point = mx_addtorus(point,0,0,0,50,200);
point = mx_rotate(point,0,0.5);

struct Matrix edge;
edge = mx_init_e(edge,0);
edge = mx_addbox(edge,-100,-100,-100,200,200,200);
edge = mx_rotate(edge,0,M_PI/4);
edge = mx_rotate(edge,1,M_PI/4);

mx_export(point,color);
mx_export(edge,color);
*/

//mx_export(edge,"ok.ppm");

printf("hi\n");
canvas_push("hi.ppm");

return 0;


}
