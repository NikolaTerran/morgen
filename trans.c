#include "engine.h"
/////////////////////////////
// matrix tranformation /////
/////////////////////////////

//create a transformation matrix 4 x 4
struct Matrix mx_dilation(struct Matrix mx, double x, double y, double z){
	struct Matrix id = mx_iden(mx,1);
	
	int i = 0;
	
	id = mx_set(id,0,0,x);
	id = mx_set(id,1,1,y);
	id = mx_set(id,2,2,z);
	
	return id;
}

struct Matrix mx_transform(struct Matrix mx, double x, double y, double z){
	struct Matrix id = mx_iden(mx,1);

	int i = 0;

	id = mx_set(id,0,3,x);
	id = mx_set(id,1,3,y);
	id = mx_set(id,2,3,z);
	
	mx = mx_mult(id,mx);
	
	return mx;
}

//axis == x,y
struct Matrix mx_rotate(struct Matrix mx, int axis, double radian){
	struct Matrix id;
	id = mx_iden(mx,1);
	if(axis == 0){
		id = mx_set(id,1,1,cos(radian));
		id = mx_set(id,1,2,-sin(radian));
		id = mx_set(id,2,1,sin(radian));
		id = mx_set(id,2,2,cos(radian));
	}else if(axis == 1){
		id = mx_set(id,0,0,cos(radian));
		id = mx_set(id,0,2,sin(radian));
		id = mx_set(id,2,0,-sin(radian));
		id = mx_set(id,2,2,cos(radian));
	}else{
		id = mx_set(id,0,0,cos(radian));
		id = mx_set(id,1,0,sin(radian));
		id = mx_set(id,0,1,-sin(radian));
		id = mx_set(id,1,1,cos(radian));
	}
	return id;
}

//only applies for standard 4 row matrix
struct Matrix mx_yrev(struct Matrix mx){
	int row = 1;
	int i = 0;
	while(i < mx.col){
		mx = mx_set(mx,row,i,500 - mx_get(mx,row,i));
		i++;
	}
	return mx;
}
