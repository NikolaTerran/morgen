#include "engine.h"

__global__ void add(int *a, int *b, int *c){
	c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

__global__ void gp_drawline(int *x, int *y, int *x1, int *y1, int ** x2, int ** y2){

}

void random_ints(int* x, int size)
{
	int i;
	for (i=0;i<size;i++) {
		x[i]=rand()%10;
	}
}

void drawLine(struct Array arr, struct Matrix mx, int color[3]){
	int octants;
	int * x;
	int * y;
	int * x1;
	int * y1;
	
	

	int **x2;
	int **y2;				//host copies of a,b,c
	int **d_x2;
	int **d_y2;         //device copies of a,b,c
	
	int size = N * sizeof(int);

	cudaMalloc((void **)&d_a,size);
	cudaMalloc((void **)&d_b,size);

	cudaMalloc((void **)&d_c,size);
	if(mx == x1 && y2 == y1){
				arr. = color[0];
				array[y1][x1][1] = color[1];
				array[y1][x1][2] = color[2];
	}else{
			//{double m = 1;}
		double m = ((double)y1 - (double)y2) / ((double)x2 - (double)x1);
		//db("m",m);
		
			if(y2 <= y1){
				if(x2 >= x1){
					if( m <= 1 ){
						 octants = 1;
					}else{
						 octants = 2;
					}
				}else{
					if( m <= -1 ){
						 octants = 3;
					}else{
						 octants = 4;
					}
				}
			}else{
			   if(x2 < x1){
					if( m <= 1 ){
						 octants = 5;
					}else{
						 octants = 6;
					}
				}else{
					if( m <= -1 ){
						 octants = 7;
					}else{
						 octants = 8;
					}
				}
			}
			
			//db("octants",(double)octants);
			
			array[y1][x1][0] = color[0];
			array[y1][x1][1] = color[1];
			array[y1][x1][2] = color[2];
			//db("lol",(double)octants);
		switch(octants){
				case 1: line_helper(array,x1,y1,x2,y2,x1 + 1,y1 - 1,octants,color,m);
				break;
				case 2: line_helper(array,x1,y1,x2,y2,x1 + 1,y1 - 1,octants,color,m);
				break;
				case 3: line_helper(array,x1,y1,x2,y2,x1 - 1,y1 - 1,octants,color,m);
				break;
				case 4: line_helper(array,x1,y1,x2,y2,x1 - 1,y1 - 1,octants,color,m);//left up
				break;
				case 5: line_helper(array,x2,y2,x1,y1,x2 + 1,y2 - 1,1,color,m);//left down
				break;
				case 6: line_helper(array,x2,y2,x1,y1,x2 + 1,y2 - 1,2,color,m);//down left
				break;
				case 7: line_helper(array,x2,y2,x1,y1,x2 - 1,y2 - 1,3,color,m);//down right
				break;
				case 8: line_helper(array,x2,y2,x1,y1,x2 - 1,y2 - 1,4,color,m);// right down
				break;
		}
	}
}


int main(void){
	int *a,*b,*c;					//host copies of a,b,c
	
	int *d_a,*d_b,*d_c;         //device copies of a,b,c
	
	int size = N * sizeof(int);

	cudaMalloc((void **)&d_a,size);
	cudaMalloc((void **)&d_b,size);
	cudaMalloc((void **)&d_c,size);

	//Alloc space for host copies of a,b,c and setup input values
	a = (int *)malloc(size); random_ints(a,N); 
	b = (int *)malloc(size); random_ints(b,N);
	c = (int *)malloc(size);

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);

	add<<<N,1>>>(d_a,d_b,d_c);
	cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

	int i;
	for(i = 0; i < N;i++){
		printf("a[%d]: %d\n",i,a[i]);
		printf("b[%d]: %d\n",i,b[i]);
		printf("c[%d]: %d\n",i,c[i]);
	}

	return 0;
}


void line_helper(int array[][500][3], int x1, int y1, int x2, int y2, int x3, int y3, int octants, int color[], double m){
	
	double slope;
		switch(octants){
			case 1: 
			while(x3 <= x2){
					slope = ((double)y1 - (double)y3)/((double)x3 - (double)x1);
					if(slope > m){
						//db("slope",slope);
					    //db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
						//y3 --;
					}else{
					    //db("slope",slope);
					    //db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
						y3 --;
					}
			}		
			break;
			case 2: //up right
			while(y3 >= y2){
					slope = ((double)y1 - (double)y3)/((double)x3 - (double)x1);
					if(slope > m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
						y3 --;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						//x3 ++;
						y3 --;
					}	
			}	
			break;
			case 3: //up left
			while(y3 >= y2){
					slope = ((double)y1 - (double)y3)/((double)x3 - (double)x1);
					if(slope < m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 --;
						y3 --;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						//x3 --;
						y3 --;
					}
			}
			break;
			case 4: //left up
			while(x3 >= x2){
					slope = ((double)y1 - (double)y3)/((double)x3 - (double)x1);
					if(slope < m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						
						x3 --;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						y3 --;
						x3 --;
					}
			}
			break;
			case 5: //left down
					if(slope > m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 --;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 --;
						y3 ++;
					}
			break;
			case 6: //down left
					if(slope < m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						y3 ++;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 --;
						y3 ++;
					}
			break;
			case 7: //down right
					if(slope > m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						y3 ++;
						
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
						y3 ++;
					}
			break;
			case 8: //right down
					if(slope < m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
						y3 ++;
					}
			break;
		}
	}


