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

point = mx_addsphere(point,0,0,0,100);
point = mx_addtorus(point,0,0,0,50,100);
point = mx_rotate(point,0,0.5);

printf("point.col: %d\n",point.col);
/*
edge = mx_addbezier(edge,0,0,50,50,-50,-50,100,100);
edge = mx_addbezier(edge,0,0,50,50,-50,-50,-100,100);
edge = mx_addbezier(edge,0,0,50,50,-50,-50,100,-100);
edge = mx_addbezier(edge,0,0,50,50,-50,-50,-100,-100);

edge = mx_addhermite(edge,0,0,50,50,-50,-50,200,200);
edge = mx_addhermite(edge,0,0,50,50,-50,-50,-200,200);
edge = mx_addhermite(edge,0,0,50,50,-50,-50,200,-200);
edge = mx_addhermite(edge,0,0,50,50,-50,-50,-200,-200);
drawLine(edge,color);
*/
drawPoint(point,color);

//mx_export(edge,"ok.ppm");

printf("hi\n");
canvas_push("hi.ppm");

return 0;


}
