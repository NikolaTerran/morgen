#include "engine.h"

int main(){

printf("Please read README.md first\n");
//edge don't require mx_init for some reason
struct Matrix edge;
edge = mx_init(4,0);
//edge.row = 4;





edge = add_sphere(edge,250,250,0,100);
edge = add_torus(edge, 250,250,0,50,150,1);
edge = add_box(edge,50,100,0,100,100,100);
//edge = mx_rotate(edge,0,0.5);
//edge = circle(edge,250,250,0,100);
//edge = mx_transform(edge,50,50,0);
/*
struct Matrix ok;
ok = mx_init(4,4);
ok = mx_transform(edge,50,50,0);
edge = mx_mult(ok,edge);dis
*/

edge = mx_rotate(edge,0,0.5);
edge = mx_rotate(edge,1,0.5);
//mx_print(edge);


printf("done!\n");
mx_export(edge,0);


}
