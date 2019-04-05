#include "engine.h"

//using cuda to initiate canvas array

__global__ void gp_array_list_init(int *list, int val){

	list[blockIdx.x] = val;
	//printf("list[%d]:%d\n",blockIdx.x,list[blockIdx.x]);
}

__global__ void gp_array_set(int *d_r,int *d_g,int *d_b, int *d_x, int *d_y, int r, int g, int b){//int *d_r, int *d_g, int *d_b, int *x, int *y){
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	int x_lim = X_MAX - X_MIN;

	printf("d_r%d\n",d_r[index]);
	printf("d_y%d\n",d_y[index]);
	//int buffer = (d_y[index] > X_) ? d_y[index] : ok;
	//printf("buffer:%d\n",buffer);
	//printf("compare:%d\n",buffer > Y

	if(d_y[index] > Y_MAX || d_y[index] <= Y_MIN || d_x[index] >= X_MAX || d_x[index] < X_MIN){
		printf("Err: in arr, coordinate has exceded dimension\n");
                printf("Err: x->%d y->%d\n",d_x[index],d_y[index]);
                printf("Note: actual X_MAX is %d and Y_MIN is %d\n",X_MAX - 1, Y_MIN + 1);
        }else{
		//printf("index:%d\n",index);
                d_y[index] = 0 - d_y[index];
                d_r[(d_y[index] + Y_MAX) * x_lim + d_x[index] + X_MAX] = r;
                d_g[(d_y[index] + Y_MAX) * x_lim + d_x[index] + X_MAX] = g;
                d_b[(d_y[index] + Y_MAX) * x_lim + d_x[index] + X_MAX] = b;

		//printf("arr:%d\n",(y[index] + Y_MAX) * x_lim + x[index] + X_MAX);
		//printf("hello!\n");
        }
}

struct Array array_init(struct Array arr){
	int block = (X_MAX - X_MIN) * (Y_MAX - Y_MIN);
	int size = block * sizeof(int);
	//int * gp_arr_r;
	//int * gp_arr_g;
	//int * gp_arr_b;
	//arr.d_r = (int*)malloc(size);
	//arr.d_g = (int*)malloc(size);
	//arr.d_b = (int*)malloc(size);
	cudaMalloc((void **)&(arr.d_r),size);
	cudaMalloc((void **)&(arr.d_g),size);
	cudaMalloc((void **)&(arr.d_b),size);
	gp_array_list_init<<<block,1>>>(arr.d_r,ARR_R);
	gp_array_list_init<<<block,1>>>(arr.d_g,ARR_G);
	gp_array_list_init<<<block,1>>>(arr.d_b,ARR_B);
//	cudaMemcpy(arr.r, gp_arr_r, size, cudaMemcpyDeviceToHost);
//	cudaMemcpy(arr.g, gp_arr_g, size, cudaMemcpyDeviceToHost);
//	cudaMemcpy(arr.b, gp_arr_b, size, cudaMemcpyDeviceToHost);
//	cudaFree(gp_arr_r);
//	cudaFree(gp_arr_g);
//	cudaFree(gp_arr_b);
	return arr;
}
/*
struct Array arr_set(struct Array arr,int x, int y, int color[3]){
	int x_lim = X_MAX - X_MIN;

	if(y > Y_MAX || y <= Y_MIN || x >= X_MAX || x < X_MIN){
		printf("Err: in arr, coordinate has exceded dimension\n");
		printf("Err: x->%d y->%d\n",x,y);
		printf("Note: actual X_MAX is %d and Y_MIN is %d\n",X_MAX - 1, Y_MIN + 1);
	}else{
			y = 0 - y;
		arr.r[(y + Y_MAX) * x_lim + x + X_MAX] = color[0];
		arr.g[(y + Y_MAX) * x_lim + x + X_MAX] = color[1];
		arr.b[(y + Y_MAX) * x_lim + x + X_MAX] = color[2];
	}

	return arr;
}

/*
void array_print(struct Array arr){
	int size = (X_MAX - X_MIN) * (Y_MAX - Y_MIN);
	int i;
	for(i = 0;i < size; i++){
		printf("r[%d] = %d\n",i,arr.r[i]);
		printf("g[%d] = %d\n",i,arr.g[i]);
		printf("b[%d] = %d\n",i,arr.b[i]);
	}
}

*/
void array_push(struct Array arr, char * filename){
	int y_lim = Y_MAX - Y_MIN;
	int x_lim = X_MAX - X_MIN;

	char line[20];

	int * h_r;
	int * h_g;
	int * h_b;

        int block = (X_MAX - X_MIN) * (Y_MAX - Y_MIN);
        int size = block * sizeof(int);

	h_r = (int*)malloc(size);
	h_g = (int*)malloc(size);
	h_b = (int*)malloc(size);

        cudaMemcpy(h_r, arr.d_r, size, cudaMemcpyDeviceToHost);
        cudaMemcpy(h_g, arr.d_g, size, cudaMemcpyDeviceToHost);
        cudaMemcpy(h_b, arr.d_b, size, cudaMemcpyDeviceToHost);

	int i,j,file;
	file = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);

	snprintf(line, sizeof(line), "P3 %d %d 255\n",x_lim,y_lim);
	write (file, line, strlen(line));
	for(i = 0; i < y_lim; i++){
			for(j = 0; j < x_lim; j++){
				snprintf(line, sizeof(line), "%d %d %d\n", 
					h_r[i * y_lim + j], 
					h_g[i * y_lim + j], 
					h_b[i * y_lim + j]);
				write(file, line, strlen(line));
			} 
		}
}

