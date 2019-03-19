#include "engine.h"

int main(){

printf("Please read README.md first\n");
//edge don't require mx_init for some reason
struct Matrix edge;
edge.row = 4;

/*
//edge = addedge(edge,50,50,0,51.499850,51.500000,0);
edge = bezier(edge,50,50,200,100,150,150,50,200);
edge = hermite(edge,50,50,200,100,150,150,50,200);
//edge = circle(edge,250,250,10,50);
//edge = circle(edge,250,250,0,50);
edge = addedge(edge,50,50,0,50,200,0);
edge = sphere(edge,250,250,20,50);
*/

struct Matrix result;
//result = mx_init(4,0);


edge = circle(edge,250,250,0,100);
//result = mx_addc(result,edge);
//edge = addedge(edge,200,200,0,250,200,0);
//edge = addedge(edge,250,200,0,250,250,0);
//edge = addedge(edge,250,250,0,200,250,0);
//edge = addedge(edge,200,250,0,200,200,0);


//rotate transformed edge matrix 1 radian around x-axis
struct Matrix rotatex;
rotatex = mx_rotate(edge,0,0.1);
rotatex = mx_mult(rotatex,edge);
result = mx_addc(edge,rotatex);

rotatex = mx_rotate(edge,0,0.1);
edge = mx_mult(rotatex,edge);
result = mx_addc(result,edge);

rotatex = mx_rotate(edge,0,0.1);
edge = mx_mult(rotatex,edge);
result = mx_addc(result,edge);

rotatex = mx_rotate(edge,0,0.1);
edge = mx_mult(rotatex,edge);
result = mx_addc(result,edge);

rotatex = mx_rotate(edge,0,0.1);
edge = mx_mult(rotatex,edge);
result = mx_addc(result,edge);

rotatex = mx_rotate(edge,0,0.1);
edge = mx_mult(rotatex,edge);
result = mx_addc(result,edge);

rotatex = mx_rotate(edge,0,0.1);
edge = mx_mult(rotatex,edge);
result = mx_addc(result,edge);
rotatex = mx_rotate(edge,0,0.1);
edge = mx_mult(rotatex,edge);
result = mx_addc(result,edge);
rotatex = mx_rotate(edge,0,0.1);
edge = mx_mult(rotatex,edge);
result = mx_addc(result,edge);
rotatex = mx_rotate(edge,0,0.1);
edge = mx_mult(rotatex,edge);
result = mx_addc(result,edge);







printf("done!\n");
mx_export(result);


}
