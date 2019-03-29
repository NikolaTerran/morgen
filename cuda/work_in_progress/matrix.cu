#include "engine.h"

/////////////////////////////
//basic matrix manipulation//
/////////////////////////////

void ed_print(struct Edge mx){
	int i,j;
	for(i = 0; i < mx.row; i++){
		printf("[  ");
		for(j = 0; j < mx.col; j++){
			printf("%0.2f  ",mx.grid[i * mx.col + j]);
		}
		printf("]\n");
	}
}

int * ed_toint( struct Edge mx, int * ptr,int row,int select){
	if(mx.col == 0){
		printf("Err: ed_toint, edge matrix has 0 column\n");
		exit(1);
	}
	ptr = (int *)malloc(mx.col / 2 * sizeof(int));
	int i,j;
	if(select == 0){
		i = 0;
		j = 0;
	}else{
		i = 1;
		j = 0;
	}
	for(i; i < mx.col; i += 2){
		ptr[j] = ed_get(mx,row,i);
		//printf("lala:%d\n",ptr[j]);
		j++;
	}
	return ptr;
}

double ed_get(struct Edge mx, int row, int col){
	int i, j;
	for(i = 0; i <= mx.row; i++){
		for(j = 0; j <= mx.col; j++){
			if(i == row && j == col){
				return mx.grid[i * mx.col + col];
			}
		}
	}
}

struct Edge ed_init(struct Edge mx, int row, int col){
	mx.row = row;
	mx.col = col;
	//mx.num_edge = 0;

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

struct Edge ed_set(struct Edge mx, int row, int col, double val){
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

struct Edge ed_addc(struct Edge m1, struct Edge m2){
	struct Edge m3;
	if(m1.row != m2.row){
		printf("ERROR: mx_addc, two matrices have different numbers of rows, return an empty matrix\n");
		return m3;
	}else{
		int column = m1.col + m2.col;
		m3 = ed_init(m3,m1.row,column);
		int i, j;
		for(i = 0; i < m3.row; i++){
			for(j = 0; j < m3.col; j++){
				if(j < m1.col){
					m3 = ed_set(m3,i,j,m1.grid[i * m1.col + j]);
				}else{
					m3 = ed_set(m3,i,j,m2.grid[i * m2.col + j - m1.col]);
				}
			}
			j = 0;
		}
		return m3;
	}
}

struct Edge ed_addp(struct Edge mx, int x, int y, int z){
	struct Edge m1;
	m1 = ed_init(m1,4,1);
	m1 = ed_set(m1,0,0,x);
	m1 = ed_set(m1,1,0,y);
	m1 = ed_set(m1,2,0,z);
	m1 = ed_set(m1,3,0,1);

	mx = ed_addc(mx,m1);

	return mx;
}

struct Edge ed_adde(struct Edge mx, int x, int y, int z, int x1, int y1, int z1){
	mx = ed_addp(mx, x,y,z);
	mx = ed_addp(mx, x1,y1,z1);
	mx.num_edge = mx.col / 2;

	return mx;
}

void ed_export(struct Edge mx, struct Array arr){

}

