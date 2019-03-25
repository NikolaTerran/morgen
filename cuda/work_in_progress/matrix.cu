#include "engine.h"

/////////////////////////////
//basic matrix manipulation//
/////////////////////////////

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
