#include "engine.h"
/////////////////////////////
// matrix tranformation /////
/////////////////////////////

//create a transformation matrix 4 x 4
struct Matrix mx_dilate(struct Matrix mx, double x, double y, double z){

	int i;
	for(i = 0; i < mx.col;i++){
		mx.x[i] *= x;
		mx.y[i] *= y;
		mx.z[i] *= z;
	}

	return mx;
}

struct Matrix mx_transform(struct Matrix mx, double x, double y, double z){
		int i;

		for(i = 0; i < mx.col; i++){
			mx.x[i] += x;
			mx.y[i] += y;
			mx.z[i] += z;
		}

		return mx;
}

//axis == x,y,z
struct Matrix mx_rotate(struct Matrix mx, int axis, double radian){
	if(mx.type == 'a' || mx.type == 'b'){
		int i;
		double t;
		if(axis == 0){
			// id = mx_set(id,1,1,cos(radian));
			// id = mx_set(id,1,2,-sin(radian));
			// id = mx_set(id,2,1,sin(radian));
			// id = mx_set(id,2,2,cos(radian));
			for(i = 0; i < mx.col;i++){
				t = mx.y[i];
				mx.y[i] = mx.y[i] * cos(radian) + mx.z[i] * -sin(radian);
				mx.z[i] = t * sin(radian) + mx.z[i] * cos(radian);
			}

			// [1][0][0][0]
			// [0][cos(radian)][-sin(radian)][0]
			// [0][sin(radian)][cos(radian)][0]
			// [0][0][0][1]


		}else if(axis == 1){
			for(i = 0; i < mx.col; i++){
				t = mx.x[i];
				mx.x[i] = mx.x[i] * cos(radian) + mx.z[i] * sin(radian);
				mx.z[i] = t * -sin(radian) + mx.z[i] * cos(radian);
			}
			// id = mx_set(id,0,0,cos(radian));
			// id = mx_set(id,0,2,sin(radian));
			// id = mx_set(id,2,0,-sin(radian));
			// id = mx_set(id,2,2,cos(radian));
			//[cos(radian)][][sin(radian)][]
			//[][1][][]
			//[-sin(radian)][][cos(radian)][]
			//[][][][1]

		}else{
			for(i = 0; i < mx.col; i++){
				t = mx.x[i];
				mx.x[i] = mx.x[i] * cos(radian) + mx.y[i] * -sin(radian);
				mx.y[i] = t * sin(radian) + mx.y[i] * cos(radian);
			}
			// id = mx_set(id,0,0,cos(radian));
			// id = mx_set(id,1,0,sin(radian));
			// id = mx_set(id,0,1,-sin(radian));
			// id = mx_set(id,1,1,cos(radian));
			//[cos(radian)][-sin(radian)][][]
			//[sin(radian)][cos(radian)][][]
			//[][][1][]
			//[][][][1]
		}

		return mx;
	}
	else if(mx.type == 'c'){
		int i;
		double t;
		if(axis == 0){
			// id = mx_set(id,1,1,cos(radian));
			// id = mx_set(id,1,2,-sin(radian));
			// id = mx_set(id,2,1,sin(radian));
			// id = mx_set(id,2,2,cos(radian));
			for(i = 0; i < mx.col;i++){
				t = mx.y[i];
				mx.y[i] = mx.y[i] * cos(radian) + mx.z[i] * -sin(radian);
				mx.z[i] = t * sin(radian) + mx.z[i] * cos(radian);
			}

			for(i = 0; i < mx.col / 3; i++){
				t = mx.vy[i];
				mx.vy[i] = mx.vy[i] * cos(radian) + mx.vz[i] * -sin(radian);
				mx.vz[i] = t * sin(radian) + mx.vz[i] * cos(radian);
			}

			// [1][0][0][0]
			// [0][cos(radian)][-sin(radian)][0]
			// [0][sin(radian)][cos(radian)][0]
			// [0][0][0][1]


		}else if(axis == 1){
			for(i = 0; i < mx.col; i++){
				t = mx.x[i];
				mx.x[i] = mx.x[i] * cos(radian) + mx.z[i] * sin(radian);
				mx.z[i] = t * -sin(radian) + mx.z[i] * cos(radian);
			}

			for(i = 0; i < mx.col / 3; i++){
				t = mx.vx[i];
				mx.vx[i] = mx.vx[i] * cos(radian) + mx.vz[i] * sin(radian);
				mx.vz[i] = t * -sin(radian) + mx.vz[i] * cos(radian);
			}
			// id = mx_set(id,0,0,cos(radian));
			// id = mx_set(id,0,2,sin(radian));
			// id = mx_set(id,2,0,-sin(radian));
			// id = mx_set(id,2,2,cos(radian));
			//[cos(radian)][][sin(radian)][]
			//[][1][][]
			//[-sin(radian)][][cos(radian)][]
			//[][][][1]

		}else{
			for(i = 0; i < mx.col; i++){
				t = mx.x[i];
				mx.x[i] = mx.x[i] * cos(radian) + mx.y[i] * -sin(radian);
				mx.y[i] = t * sin(radian) + mx.y[i] * cos(radian);
			}

			for(i = 0; i < mx.col; i++){
				t = mx.vx[i];
				mx.vx[i] = mx.vx[i] * cos(radian) + mx.vz[i] * sin(radian);
				mx.vz[i] = t * -sin(radian) + mx.vz[i] * cos(radian);
			}
			// id = mx_set(id,0,0,cos(radian));
			// id = mx_set(id,1,0,sin(radian));
			// id = mx_set(id,0,1,-sin(radian));
			// id = mx_set(id,1,1,cos(radian));
			//[cos(radian)][-sin(radian)][][]
			//[sin(radian)][cos(radian)][][]
			//[][][1][]
			//[][][][1]
		}

		return mx;
	}
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
