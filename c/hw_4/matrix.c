#include "engine.h"

/////////////////////////////
//basic matrix manipulation//
/////////////////////////////

/*random snippet
	
	T
	|\
	| \
	|  \ M
	|  /
	| /
	|/
	B
	
	y: By -> Ty
	x0 is on BT
	x1 is on BM or on MT
	(x0,y) -> (x1,y)

	x0: Bx -> Tx; x0 += (Tx - Bx)/(Ty - By)
	x1: Bx -> Mx; x1 += (Mx - Bx)/(My - By)
	x1: Mx -> Tx; x1 += (Tx - Mx)/(Ty - My)
	
	z_buffering
	maintain a 2d array of z-values
	that corresponds to our 2d array of pixels (screen)
	when we plot pixels, check the new z-value against what is currently in the z-buffer
*/

int * mx_toint(struct Matrix mx, int *result, int row){
	int i;
	for(i = 0;i < mx.col;i++){
		result[i] = mx_get(mx, row, i + 1);
	}
	return result;	
}

/*
struct Matrix mx_mult(struct Matrix m1, struct Matrix m2){
	if(m2.type != 'b'){
		int i;
		for(i; i < m2.col;i++){
			m2.x[i] = 
			m2.y[i] = 
			m2.z[i] = 
		}
		
	}else{
		printf("Error: mx_mult, matrix type not supported\n");
		exit(1);
	}
}
*/

void mx_print(struct Matrix mx){
	int i;
	for(i = 0; i < mx.col; i++){
		printf("[%f] ",mx.x[i]);
	}
	printf("\n");
	for(i = 0; i < mx.col; i++){
		printf("[%f] ",mx.y[i]);
	}
	printf("\n");
	for(i = 0; i < mx.col; i++){
		printf("[%f] ",mx.z[i]);
	}
	printf("\n");
	for(i = 0; i < mx.col; i++){
		printf("[%f] ",mx.one[i]);
	}
	printf("\n");
}

//mx_print but will free the mx instance
void mx_printf(struct Matrix mx){

	//mx_free(mx);
}

//init default 4 row point matrix
struct Matrix mx_init(struct Matrix mx, int col){

	mx.col = col;
	mx.type = 'a';

	mx.x = malloc (col * sizeof(double));
	mx.y = malloc (col * sizeof(double));
	mx.z = malloc (col * sizeof(double));
	mx.one = malloc (col * sizeof(double));

	int i;
	for(i = 0; i < col; i++){
		mx.x[i] = INIT_VALUE; 
		mx.y[i] = INIT_VALUE; 
		mx.z[i] = INIT_VALUE; 
		mx.one[i] = 1; 
	}

	return mx;
}

struct Matrix mx_init_e(struct Matrix mx, int col){

	mx.col = col;
	mx.type = 'b';
	mx.edge_num = 0;

	mx.x = malloc (col * sizeof(double));
	mx.y = malloc (col * sizeof(double));
	mx.z = malloc (col * sizeof(double));
	mx.one = malloc (col * sizeof(double));

	int i;
	for(i = 0; i < col; i++){
		mx.x[i] = INIT_VALUE; 
		mx.y[i] = INIT_VALUE; 
		mx.z[i] = INIT_VALUE; 
		mx.one[i] = 1; 
	}

	return mx;
}

//actual math input
double mx_get(struct Matrix mx, int row, int col){
 	if(row == 0 || col == 0){
 		printf("Error: mx_get array start with 1\n");
 	}else if(row == 1){
 		return mx.x[col - 1];
 	}else if(row == 2){
 		return mx.y[col - 1];
 	}else if(row == 3){
 		return mx.z[col - 1];
 	}else if(row == 4){
		return mx.one[col - 1];
 	}else{
 		printf("Err: mx_get, invalid row_num, returning 0\n");
 		return 0;
 	}
 }

struct Matrix mx_set(struct Matrix mx, int row, int col, double val){
 	if(row == 0 || col == 0){
 		printf("Error: mx_set array start with 1\n");
 	}else if(row == 1){
 		mx.x[col - 1] = val;
 	}else if(row == 2){
 		mx.y[col - 1] = val;
 	}else if(row == 3){
 		mx.z[col - 1] = val;
 	}else if(row == 4){
		printf("Warning: mx_set, modifying constant row\n");
		mx.one[col - 1] = val;	
 	}else{
 		printf("Err: mx_row, invalid row_num, returning original matrix\n");
 		return mx;
 	}
 	return mx;
 }

// struct Matrix mx_mult(struct Matrix m1, struct Matrix m2){
// 	struct Matrix m3;
// 	m3 = mx_init(m1.row,m2.col);
// 	int i,j,k,l,c;
// 	double * arr;
// 	double * brr;
// 	double s = 0;
// 	k = 0;
// 	l = 0;

// 	for(i = 0; i < m3.row; i++){
// 		for(j = 0; j < m3.col; j++){
// 			for(k = 0; k < m1.col; k++){
// 				s += mx_get(m1,i,k) * mx_get(m2,k,j);
// 			}
// 			/*	arr[k] = mx_get(m1,i,k);
// 			}
// 			//for(l = 0; l < m2.row; l++){
// 				brr[l] = mx_get(m2,l,j);
// 			/*}
// 			for(c = 0; c < )
// 			*/
// 			m3 = mx_set(m3,i,j,s);
// 			s = 0;
// 		}
// 	}

// 	return m3;
// }

// struct Matrix mx_iden(struct Matrix m1, int ba){
// 	struct Matrix m2;
// 	if(ba == 0){
// 		m2 = mx_init(m1.col,m1.col);	
// 	}else{
// 		m2 = mx_init(m1.row,m1.row);
// 	}
// 	int i;
// 	for(i = 0; i < m2.row;  i++){
// 		m2 = mx_set(m2, i, i, 1.0);
// 	}
// 	return m2;
// }

// struct Matrix mx_addc(struct Matrix m1, struct Matrix m2){
// 	struct Matrix m3;
// 	if(m1.row != m2.row){
// 		printf("ERROR: mx_addc, two matrices have different numbers of rows, return an empty matrix\n");
// 		return m3;
// 	}else{
	
// 		int column = m1.col + m2.col;
// 		m3 = mx_init(m1.row,column);
// 		int i, j;
// 		for(i = 0; i < m3.row; i++){
// 			for(j = 0; j < m3.col; j++){
			
// 				if(j < m1.col){
				
// 					m3 = mx_set(m3,i,j,m1.grid[i * m1.col + j]);
// 				}else{
// 					m3 = mx_set(m3,i,j,m2.grid[i * m2.col + j - m1.col]);
// 				}	
// 			}
// 			j = 0;
// 		}
	
// 		return m3;
// 	}
// }

// //qac = quick add column
// struct Matrix mx_qac(struct Matrix mx, double arr[], int size){
// 	struct Matrix mw,my;
// 	mw = mx_init(size,1);
// 	int i;
// 	for(i = 0; i < size; i++){
// 		mw = mx_set(mw,i,0,arr[i]);
// 	}
	
// 	my = mx_addc(mx,mw);
// 	//mx_free(mw);
// 	//mx_free(mx);
// 	return my;
// }

// //buggy
// void mx_free(struct Matrix mx){
// 	/*
// 	free(mx.grid);
// 	*/
// }

//defaut edge Matrix

struct Matrix mx_copy(struct Matrix src, struct Matrix dst){
	if(src.type == 'b'){
		dst = mx_init_e(dst,src.col);
		int i;
		for(i = 0; i < src.col;i ++){
			dst.x[i] = src.x[i];
			dst.y[i] = src.y[i];
			dst.z[i] = src.z[i];

			i++;

			dst.x[i] = src.x[i];
			dst.y[i] = src.y[i];
			dst.z[i] = src.z[i];

			dst.edge_num ++;
		}
	}
	return dst;
}

void mx_export(struct Matrix mx, int color[]){
	if(mx.type == 'a'){

	}else if(mx.type == 'b'){
		drawLine(mx,color);
	}else if(mx.type == 'c'){
		drawLine(mx,color);
	}
}

// struct Matrix addpoint(struct Matrix mx, double a, double b, double c, double red, double green, double blue){
// 	double arr[7];
// 	arr[0] = a;
// 	arr[1] = b;
// 	arr[2] = c;
// 	arr[3] = red;
// 	arr[4] = green;
// 	arr[5] = blue;
// 	arr[6] = 1;
// 	mx = mx_qac(mx, arr, 7);
// 	return mx;
// }

// struct Matrix mx_rmc(struct Matrix mx){
// 	int i, j;
// 	struct Matrix my;
// 	int col = mx.col - 1;
// 	my = mx_init(mx.row,col);
// 	for(i = 0; i < my.row; i++){
// 		for(j = 0; j < my.col; j++){
// 			my = mx_set(my,i,j,mx_get(mx,i,j + 1));
// 		}
// 	}
// 	return my;
// }

// //never use point matrix for this
// //if arg == 1 --> psudo 3d enabled
// void mx_export(struct Matrix mx, int arg){
// 	int fd, i, j , k;
// 	int y_lim = Y_MAX - Y_MIN;
// 	int x_lim = X_MAX - X_MIN;
// 	int array[y_lim][x_lim][3];
// 	int rgb[3];
// 	rgb[0] = 255;
// 	rgb[1] = 255;
// 	rgb[2] = 255;
// 	initialize(array,rgb);
// 	fd = open("image.ppm", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	
// 	//initialize color
// 		rgb[0] = 0;
// 		rgb[1] = 0;
// 		rgb[2] = 0;
// 	if(arg == 1){
// 		while(mx.col >= 1){
// 			/*
// 			drawLine(array,0,0,500,0,rgb);
// 			drawLine(array,0,0,500,500,rgb);
// 			*/
// 			if((int)mx_get(mx,3,0) == 0 && (int)mx_get(mx,3,1)){
// 				drawLine(array, (int)mx_get(mx,0,0), (int)mx_get(mx,1,0), (int)mx_get(mx,0,1), (int)mx_get(mx,1,1), rgb);
// 				mx = mx_rmc(mx);
// 				mx = mx_rmc(mx);
// 			}else{
// 				drawLine(array, round(mx_get(mx,0,0))
						
// 						 + round(mx_get(mx,2,0)/2)
					
// 								,
// 								round(mx_get(mx,1,0))
						
// 						 - round(mx_get(mx,2,0)/4)
					
// 								,
// 								round(mx_get(mx,0,1))
						
// 						 + round(mx_get(mx,2,1)/2)
					
// 								,
// 								round(mx_get(mx,1,1))
						
// 						 - round(mx_get(mx,2,1)/4)
					
// 								,
// 								 rgb);
// 				mx = mx_rmc(mx);
// 				mx = mx_rmc(mx);
// 			}
		
// 		}
// 	}else{
// 			while(mx.col >= 1){
// 			/*
// 			drawLine(array,0,0,500,0,rgb);
// 			drawLine(array,0,0,500,500,rgb);
// 			*/
// 			if((int)mx_get(mx,3,0) == 0 && (int)mx_get(mx,3,1)){
// 				drawLine(array, (int)mx_get(mx,0,0), (int)mx_get(mx,1,0), (int)mx_get(mx,0,1), (int)mx_get(mx,1,1), rgb);
// 				mx = mx_rmc(mx);
// 				mx = mx_rmc(mx);
// 			}else{
// 				drawLine(array, round(mx_get(mx,0,0))
						
// 						// + round(mx_get(mx,2,0)/2)
					
// 								,
// 								round(mx_get(mx,1,0))
						
// 						// - round(mx_get(mx,2,0)/4)
					
// 								,
// 								round(mx_get(mx,0,1))
						
// 						// + round(mx_get(mx,2,1)/2)
					
// 								,
// 								round(mx_get(mx,1,1))
						
// 						// - round(mx_get(mx,2,1)/4)
					
// 								,
// 								 rgb);
// 				mx = mx_rmc(mx);
// 				mx = mx_rmc(mx);
// 			}
		
// 		}
// 	}
	
// 	push(array,fd);
// }
