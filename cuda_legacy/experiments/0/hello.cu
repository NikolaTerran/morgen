#include <stdio.h>

//casual 50 million interger addition
#define N 50000000

__global__ void mykernel(void){
	
}

__global__ void add(int *a, int *b, int *c){
	c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

void random_ints(int* x, int size)
{
	int i;
	for (i=0;i<size;i++) {
		x[i]=rand()%N;
	}
}

int main(void){
	int *a,*b,*c;					//host copies of a,b,c
	
	int *d_a,*d_b,*d_c;         //device copies of a,b,c
	
	int size = N * sizeof(int) * 2;

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