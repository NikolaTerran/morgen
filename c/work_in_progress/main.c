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
edge = mx_init(edge,6);
mx_print(edge);


printf("hi\n");
canvas_push("hi.ppm");

return 0;


}
