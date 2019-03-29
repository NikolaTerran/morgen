#include "engine.h"

__global__ void gp_drawline(int *r, int *g, int *b, int *d_x, int *d_y, int *d_x1, int *d_y1){
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    int dx = d_x1[index] - d_x[index];
    int dy = d_y1[index] - d_y[index];

    // if the X axis is the major axis
    if (abs(dx) >= abs(dy)){
        // if x2 < x1, flip the points to have fewer special cases
        if(dx < 0){
            dx *= -1;
            dy *= -1;
            int t = d_x[index];
            d_x[index] = d_x1[index];
            d_x1[index] = t;

            t = d_y[index];
            d_y[index] = d_y1[index];
            d_y1[index] = t;
        }
 
        // determine special cases
        if(dy > 0){
            arr = DLMA(arr, x1,y1, dx, dy, 0,'x', color);
        }
        else if (dy < 0){
         	arr = DLMA(arr, x1,y1, dx, -dy, 1,'x', color);
        }
        else{
            arr = DLSA(arr,x1,y1,dx,'x', color);
        }
    }
    // else the Y axis is the major axis
    else
    {
        // if y2 < y1, flip the points to have fewer special cases
        if (dy < 0)
        {
            dx *= -1;
            dy *= -1;
            int t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }
 
        // get the address of the pixel at (x1,y1)
 
        // determine special cases
        if (dx > 0){
         	  arr = DLMA(arr, x1,y1, dy, dx, 0,'y', color);
        }else if (dx < 0){
        	  arr = DLMA(arr, x1,y1, dy, -dx, 1,'y', color);
        }else{
              arr = DLSA(arr,x1,y1, dy,'y', color);
        }
    }
}

struct Array DLMA(
    struct Array arr,
    int x,
    int y,
    int dx,
    int dy,
    int check,
    char axis,
    int color[3]){
    // calculate some constants
    int dx2 = dx * 2;
    int dy2 = dy * 2;
    int dy2Mindx2 = dy2 - dx2;
 
    // calculate the starting error value
    int Error = dy2 - dx;
 
    // draw the first pixel
    arr = arr_set(arr,x,y,color);
 
    // loop across the major axis
    if(axis == 'x'){
	    while (dx--)
	    {
	        // move on major axis and minor axis
	        if (Error > 0)
	        {
	            x++;
		    if(check == 0){
		            y++;
		    }else{
			y--;
		    }
	            Error += dy2Mindx2;
	        }
	        // move on major axis only
	        else
	        {
	            x++;
	            Error += dy2;
	        }
	 
	        // draw the next pixel
	        arr = arr_set(arr,x,y,color);
	    }
	}else{
	    while (dx--)
	    {
	        // move on major axis and minor axis
	        if (Error > 0)
	        {
			if(check == 0){
	            x++;}else{x--;}
	            y++;
	            Error += dy2Mindx2;
	        }
	        // move on major axis only
	        else
	        {
	            y++;
	            Error += dy2;
	        }
	 
	        // draw the next pixel
	        arr = arr_set(arr,x,y,color);
	    }
	}
	return arr;
}


// Specialized Line Drawing optimized for horizontal or vertical lines
// X and Y are flipped for Y maxor axis lines, but the pixel writes are handled correctly due to
// minor and major axis pixel movement
struct Array DLSA(struct Array arr, int x, int y, int dx, char axis, int color[3]){
    // draw the first pixel
 	arr = arr_set(arr,x,y,color);
    // loop across the major axis and draw the rest of the pixels


    if(axis == 'x'){
	    while (dx--){
	    	x++;
        	arr = arr_set(arr,x,y,color);
    	}
    }else{
	    while (dx--){
	    	y++;
        	arr = arr_set(arr,x,y,color);
    	}
    }

    return arr;
}
 
// Draw an arbitrary line.  Assumes start and end point are within valid range
// pixels is a pointer to where the pixels you want to draw to start aka (0,0)
// pixelStride is the number of unsigned ints to get from one row of pixels to the next.
// Usually, that is the same as the width of the image you are drawing to, but sometimes is not.
struct Array DL(struct Array arr, int x1, int y1, int x2, int y2, int color[3]){
    // calculate our deltas
    int dx = x2 - x1;
    int dy = y2 - y1;


    // if the X axis is the major axis
    if (abs(dx) >= abs(dy)){
        // if x2 < x1, flip the points to have fewer special cases
        if (dx < 0){
            dx *= -1;
            dy *= -1;
            int t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }
 
        // determine special cases
        if(dy > 0){
            arr = DLMA(arr, x1,y1, dx, dy, 0,'x', color);
        }
        else if (dy < 0){
         	arr = DLMA(arr, x1,y1, dx, -dy, 1,'x', color);
        }
        else{
            arr = DLSA(arr,x1,y1,dx,'x', color);
        }
    }
    // else the Y axis is the major axis
    else
    {
        // if y2 < y1, flip the points to have fewer special cases
        if (dy < 0)
        {
            dx *= -1;
            dy *= -1;
            int t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }
 
        // get the address of the pixel at (x1,y1)
 
        // determine special cases
        if (dx > 0){
         	  arr = DLMA(arr, x1,y1, dy, dx, 0,'y', color);
        }else if (dx < 0){
        	  arr = DLMA(arr, x1,y1, dy, -dx, 1,'y', color);
        }else{
              arr = DLSA(arr,x1,y1, dy,'y', color);
        }
    }

    return arr;
}



struct Array drawLine(struct Array arr, struct Edge ed, int color[3]){
	int * x;
	int * y;
	int * x1;
	int * y1;

	x = ed_toint(ed,x,0,0);
	y = ed_toint(ed,y,1,0);
	x1 = ed_toint(ed,x1,0,1);
	y1 = ed_toint(ed,x1,1,1);

/*
	int * d_x;
	int * d_y;
	int * d_x1;
	int * d_y1;
	int * d_x2;
	int * d_y2;
/*
	cudaMalloc((void **)&d_x,mx.num_edge);
	cudaMalloc((void **)&d_y,mx.num_edge);
	cudaMalloc((void **)&d_x1,mx.num_edge);
	cudaMalloc((void **)&d_y1,mx.num_edge);
	//cudaMalloc((void **)&d_y1,mx.num_edge);

        cudaMemcpy(d_x,x,mx.num_edge,cudaMemcpyHostToDevice);
        cudaMemcpy(d_y,y,mx.num_edge,cudaMemcpyHostToDevice);
        cudaMemcpy(d_x1,x1,mx.num_edge,cudaMemcpyHostToDevice);
        cudaMemcpy(d_y1,y1,mx.num_edge,cudaMemcpyHostToDevice);
*/
	int i;
	for(i = 0; i < ed.col/2; i++){
		printf("x: %d  y: %d  x1: %d  y1: %d\n",x[i],y[i],x1[i],y1[i]);
		arr = DL(arr,x[i],y[i],x1[i],y1[i],color);
	}
	return arr;
}


/*
int main(void){
	int *a,*b,*c;		    //host copies of a,b,c
	
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
*/
