#include "engine.h"

void drawPoint(struct Matrix mx, int color[3]){
	int * x;
	x = malloc(mx.col * sizeof(int));
	x = mx_toint(mx,x,1);
	int * y;
	y = malloc(mx.col * sizeof(int));
	y = mx_toint(mx,y,2);

	canvas_set_p(x,y,mx.col,color);
}

struct Matrix mx_addpoint(struct Matrix mx, double x, double y, double z){
	/*if(mx.type != 'a'){
		printf("Err: mx_addpoint, incompatible matrix type, force quitting the program\n");
		exit(1);
	}*/
	
	//mx.edge_num += 1;
	mx.col ++;
	
	mx.x = realloc(mx.x,mx.col * sizeof(double));
	mx.y = realloc(mx.y,mx.col * sizeof(double));
	mx.z = realloc(mx.z,mx.col * sizeof(double));
 	//mx.one = realloc(mx.one,mx.col * sizeof(double));
 	
 	mx.x[mx.col - 1] = x;
 	mx.y[mx.col - 1] = y;
 	mx.z[mx.col - 1] = z;
 	//mx.one[mx.col - 1] = 1;
 	
 	return mx;
}
