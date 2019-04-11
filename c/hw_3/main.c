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
edge = mx_addedge(edge,0   ,0   ,0,		100,0,    0);
edge = mx_addedge(edge,0   ,0   ,0,	    0,100,    0);
edge = mx_addedge(edge,100   ,100   ,0,		100,0,    0);
edge = mx_addedge(edge,100   ,100   ,0,		0,100,    0);

struct Matrix edge_d;
edge_d = mx_copy(edge,edge_d);
edge_d = mx_dilate(edge_d,2,2,1);

struct Matrix edge_t;
edge_t = mx_copy(edge,edge_t);
edge_t = mx_transform(edge_t,-100,-100,0);

struct Matrix edge_x;
edge_x = mx_copy(edge,edge_x);
edge_x = mx_rotate(edge_x,0,1);

struct Matrix edge_y;
edge_y = mx_copy(edge,edge_y);
edge_y = mx_rotate(edge_y,1,1);

struct Matrix edge_z;
edge_z = mx_copy(edge,edge_z);
edge_z = mx_rotate(edge_z,2,1);

int color[3];
color[0] = 255;
color[1] = 0;
color[2] = 0;

drawLine(edge,color);
drawLine(edge_d,color);
drawLine(edge_t,color);
drawLine(edge_x,color);
drawLine(edge_y,color);
drawLine(edge_z,color);

//mx_export(edge,"ok.ppm");

printf("hi\n");
canvas_push("hi.ppm");

return 0;


}
