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

edge = addedge(edge,200,200,0,250,200,0);
edge = addedge(edge,250,200,0,250,250,0);
edge = addedge(edge,250,250,0,200,250,0);
edge = addedge(edge,200,250,0,200,200,0);


//rotate transformed edge matrix 1 radian around x-axis
struct Matrix rotatex;
rotatex = mx_rotate(transform,0,0.1);
rotatex = mx_mult(rotatex,transform);



/*
//necessary init statement


//initial triangular prism

edge = addedge(edge,50,50,0,100,150,0);
edge = addedge(edge,100,150,0,150,50,0);

edge = addedge(edge,50,50,100,150,50,100);
edge = addedge(edge,50,50,100,100,150,100);
edge = addedge(edge,100,150,100,150,50,100);

edge = addedge(edge,50,50,0,50,50,100);
edge = addedge(edge,100,150,0,100,150,100);
edge = addedge(edge,150,50,0,150,50,100);

//dilate by a factor of 2
struct Matrix dilation;
dilation = mx_dilation(edge,2,2.5,1.5);
dilation = mx_mult(dilation,edge);

//transform edge matrix 200 px right, 200 px down, 50 px forward
struct Matrix transform;
transform = mx_transform(edge,200,200,-50);
transform = mx_mult(transform,edge);

//rotate transformed edge matrix 1 radian around x-axis
struct Matrix rotatex;
rotatex = mx_rotate(transform,0,1);
rotatex = mx_mult(rotatex,transform);

//rotate transformed edge matrix 1 radian around y-axis
struct Matrix rotatey;
rotatey = mx_rotate(transform,1,1);
rotatey = mx_mult(rotatey,transform);
mx_print(rotatey);

//rotate transformed edge matrix 1 radian around z-axis
struct Matrix rotatez;
rotatez = mx_rotate(transform,2,1);
rotatez = mx_mult(rotatez,transform);
mx_print(rotatez);

//add those matrix together
struct Matrix result;
result = mx_addc(edge,dilation);
result = mx_addc(result,transform);
result = mx_addc(result,rotatex);
result = mx_addc(result,rotatey);
result = mx_addc(result,rotatez);
*/
//mx_print(result);
result = mx_addc(result,rotatex);
printf("done!\n");
mx_export(result);


}
