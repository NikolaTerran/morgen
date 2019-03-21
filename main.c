#include "engine.h"

int main(){

printf("Please read README.md first\n");
//edge don't require mx_init for some reason
struct Matrix edge;
edge = mx_init(4,0);
//edge.row = 4;

struct Matrix sp,to;
sp = mx_init(4,0);
to = mx_init(4,0);




sp = add_sphere(edge,250,250,0,100);
to = add_torus(edge, 250,250,0,50,150,1);
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

sp = mx_rotate(sp,0,0.5);
sp = mx_rotate(sp,1,0.5);
 
to = mx_rotate(to,0,0.5);
to = mx_rotate(to,1,0.5);

struct Matrix result;
result = mx_init(4,0);
result = mx_addc(result,edge);
//mx_print(edge);
result = mx_addc(result,to);
result = mx_addc(result,sp);

printf("done!\n");
mx_export(result,0);


}
