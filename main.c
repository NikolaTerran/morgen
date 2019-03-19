#include "engine.h"

int main(){

printf("Please read README.md first\n");
//edge don't require mx_init for some reason
struct Matrix edge;
edge = mx_init(4,0);
//edge.row = 4;





edge = sphere(edge,250,250,0,100);
//edge = circle(edge,250,250,0,100);
//edge = mx_transform(edge,50,50,0);
/*
struct Matrix ok;
ok = mx_init(4,4);
ok = mx_transform(edge,50,50,0);
edge = mx_mult(ok,edge);
*/

mx_print(edge);


printf("done!\n");
mx_export(edge);


}
