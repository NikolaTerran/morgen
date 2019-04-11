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

struct Matrix edge;
edge = mx_init_e(edge,0);


int color[3];
color[0] = 255;
color[1] = 0;
color[2] = 0;

edge = mx_addcircle(edge,0,0,0,100);
edge = mx_addbezier(edge,0,0,50,50,-50,-50,100,100);
edge = mx_addbezier(edge,0,0,50,50,-50,-50,-100,100);
edge = mx_addbezier(edge,0,0,50,50,-50,-50,100,-100);
edge = mx_addbezier(edge,0,0,50,50,-50,-50,-100,-100);

edge = mx_addhermite(edge,0,0,50,50,-50,-50,200,200);
edge = mx_addhermite(edge,0,0,50,50,-50,-50,-200,200);
edge = mx_addhermite(edge,0,0,50,50,-50,-50,200,-200);
edge = mx_addhermite(edge,0,0,50,50,-50,-50,-200,-200);
drawLine(edge,color);


//mx_export(edge,"ok.ppm");

printf("hi\n");
canvas_push("hi.ppm");

return 0;


}
