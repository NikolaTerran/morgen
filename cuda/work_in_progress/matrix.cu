#include "engine.h"

/////////////////////////////
//basic matrix manipulation//
/////////////////////////////

void mx_print(struct Matrix mx){
	int i,j;
	for(i = 0; i < mx.row; i++){
		printf("[  ");
		for(j = 0; j < mx.col; j++){
			printf("%0.2f  ",mx.grid[i * mx.col + j]);
		}
		printf("]\n");
	}
}

int * mx_rowtoint( struct Matrix mx, int * ptr,int row){
	ptr = (int *)malloc(mx.col * sizeof(int));
	int i;
	for(i = 0; i < mx.col; i++){
		ptr[i] = mx_get(mx,row,i);
	}
	return ptr;
}

double mx_get(struct Matrix mx, int row, int col){
	int i, j;
	for(i = 0; i <= mx.row; i++){
		for(j = 0; j <= mx.col; j++){
			if(i == row && j == col){
				return mx.grid[i * mx.col + col];
			}
		}
	}
}

struct Matrix mx_init(struct Matrix mx, int row, int col){
	mx.row = row;
	mx.col = col;

	mx.grid = (double *)malloc(row * col * sizeof(double));

	int i, j;

	i = row;
	j = col;
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			mx.grid[i * col + j] = INIT_VALUE;
		}
	}
	return mx;
}

struct Matrix mx_set(struct Matrix mx, int row, int col, double val){
	if(row >= mx.row || col >= mx.col){
    	printf("ERROR: mx_set, target row or column doesn't exist, return original Matrix\n");
    	return mx;
    }
		int i, j;
		for(i = 0; i <= row; i++){
			for(j = 0; j <= col; j++){	
				if(j == col && i == row){
					mx.grid[i * mx.col + j] = val;
				}
			}
		}
	return mx;
}

struct Matrix mx_addc(struct Matrix m1, struct Matrix m2){
	struct Matrix m3;
	if(m1.row != m2.row){
		printf("ERROR: mx_addc, two matrices have different numbers of rows, return an empty matrix\n");
		return m3;
	}else{
	
		int column = m1.col + m2.col;
		m3 = mx_init(m3,m1.row,column);
		int i, j;
		for(i = 0; i < m3.row; i++){
			for(j = 0; j < m3.col; j++){
			
				if(j < m1.col){
					m3 = mx_set(m3,i,j,m1.grid[i * m1.col + j]);
				}else{
					m3 = mx_set(m3,i,j,m2.grid[i * m2.col + j - m1.col]);
				}	
			}
			j = 0;
		}
		return m3;
	}
}

struct Matrix mx_addp(struct Matrix mx, int x, int y, int z){
	struct Matrix m1;
	m1 = mx_init(m1,4,1);
	m1 = mx_set(m1,0,0,x);
	m1 = mx_set(m1,1,0,y);
	m1 = mx_set(m1,2,0,z);
	m1 = mx_set(m1,3,0,1);

	mx = mx_addc(mx,m1);

	return mx;
}

struct Matrix mx_adde(struct Matrix mx, int x, int y, int z, int x1, int y1, int z1){
	mx = mx_addp(mx, x,y,z);
	mx = mx_addp(mx, x1,y1,z1);

	return mx;
}

void mx_export(struct Matrix mx, struct Array arr){
	
}
