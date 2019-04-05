#include "engine.h"
/*
__global__ void gp_pxassign(int *d_r, int *d_g, int *d_b, int d_x, int d_y,int r, int g, int b){
	if(d_y > Y_MAX ||
	   d_y <= Y_MIN ||
	   d_x >= X_MAX ||
	   d_x < X_MIN){
		printf("Err: in arr, coordinate has exceded dimension\n");
		printf("Err: x->%d y->%d\n",d_x,d_y);
		printf("Note: actual X_MAX is %d and Y_MIN is %d\n",X_MAX - 1, Y_MIN + 1);
	}else{
		int arr_index = (d_y + Y_MAX) * (X_MAX - X_MIN) + d_x + X_MAX;
		d_y = 0 - d_y;
		d_r[arr_index] = r;
		d_g[arr_index] = g;
		d_b[arr_index] = b;
	}
}

__global__ void gp_DLMA(int *d_r, int *d_g, int *d_b, 
						int x , int y, int dx, int dy, 
						int check, char axis, 
						int r, int g, int b){
    int dx2 = dx * 2;
    int dy2 = dy * 2;
    int dy2Mindx2 = dy2 - dx2;
 
    int Error = dy2 - dx;

 	__syncthreads();
    gp_pxassign<<<1,1>>>(d_r,d_g,d_b,x,y,r,g,b);
 	__syncthreads();
    
    if(axis == 'x'){
	    while (dx--){
	        if (Error > 0){
	            x++;
			    if(check == 0){
			        y++;
			    }else{
				    y--;
			    }
	            Error += dy2Mindx2;
	        }else{
	            x++;
	            Error += dy2;
	        }
	 		__syncthreads();
	        gp_pxassign<<<1,1>>>(d_r,d_g,d_b,x,y,r,g,b);
	        __syncthreads();
	    }
	}else{
	    while (dx--){
	        if (Error > 0){
				if(check == 0){
		            x++;
		        }else{
		        	x--;
		        }
		        y++;
		        Error += dy2Mindx2;
		    }else{
	            y++;
	            Error += dy2;
	        }
	 		__syncthreads();
	        gp_pxassign<<<1,1>>>(d_r,d_g,d_b,x,y,r,g,b);
	        __syncthreads();
	    }
	}
}	

__global__ void gp_DLSA(int *d_r,int *d_g, int *d_b,
						int x, int y, int dx, char axis, 
						int r, int g, int b){
	__syncthreads();
    gp_pxassign<<<1,1>>>(d_r,d_g,d_b,x,y,r,g,b);
    __syncthreads();

    if(axis == 'x'){
	    while (dx--){
	    	x++;
        	__syncthreads();
		    gp_pxassign<<<1,1>>>(d_r,d_g,d_b,x,y,r,g,b);
		    __syncthreads();
    	}
    }else{
	    while (dx--){
	    	y++;
        	__syncthreads();
    		gp_pxassign<<<1,1>>>(d_r,d_g,d_b,x,y,r,g,b);
    		__syncthreads();
    	}
    }
}

__global__ void gp_drawline(int *d_r, int *d_g, int *d_b, 
							int *d_x, int *d_y, 
							int *d_x1, int *d_y1, int red, int green, int blue){
    int index = blockIdx.x; //* blockDim.x + threadIdx.x;
    int dx = d_x1[index] - d_x[index];
    int dy = d_y1[index] - d_y[index];

    int check;
    int axis;

    if (abs(dx) >= abs(dy)){
    	axis = 'x';
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
        if(dy > 0){
        	__syncthreads();
        	gp_DLMA<<<1,1>>>(d_r,d_g,d_b,d_x[index],d_y[index],dx,dy,0,'x',red,green,blue);
        	__syncthreads();
       	}else if(dy < 0){
       		__syncthreads();
       		gp_DLMA<<<1,1>>>(d_r,d_g,d_b,d_x[index],d_y[index],dx,-dy,1,'x',red,green,blue);
       		__syncthreads();
       	}else{
            __syncthreads();
       		gp_DLSA<<<1,1>>>(d_r,d_g,d_b,d_x[index],d_y[index],dx,'x',red,green,blue);
       		__syncthreads();
        }
    
    }else{
        if (dy < 0){
            dx *= -1;
            dy *= -1;
            int t = d_x[index];
            d_x[index] = d_x1[index];
            d_x1[index] = t;

			t = d_y[index];
            d_y[index] = d_y1[index];
            d_y1[index] = t;
        }
        if (dx > 0){
         	__syncthreads();
        	gp_DLMA<<<1,1>>>(d_r,d_g,d_b,d_x[index],d_y[index],dy,dx,0,'y',red,green,blue);
        	__syncthreads();
        }else if (dx < 0){
        	__syncthreads();
        	gp_DLMA<<<1,1>>>(d_r,d_g,d_b,d_x[index],d_y[index],dy,-dx,1,'y',red,green,blue);
        	__syncthreads();
        }else{
            __syncthreads();
       		gp_DLSA<<<1,1>>>(d_r,d_g,d_b,d_x[index],d_y[index],dy,'y',red,green,blue);
       		__syncthreads();
        }
    }
}



struct Array cp_drawLine(struct Array arr, struct Edge ed, int color[3]){
	int * x;
	int * y;
	int * x1;
	int * y1;

	x = ed_toint(ed,x,0,0);
	y = ed_toint(ed,y,1,0);
	x1 = ed_toint(ed,x1,0,1);
	y1 = ed_toint(ed,x1,1,1);

    int i;
	for(i = 0; i < ed.col/2; i++){
	// 	printf("x: %d  y: %d  x1: %d  y1: %d\n",x[i],y[i],x1[i],y1[i]);
	 	arr = DL(arr,x[i],y[i],x1[i],y1[i],color);
	}

    return arr;
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

*/

/*
struct Array drawLine(struct Array arr, struct Edge ed, int color[3]){
	int * x;
	int * y;
	int * x1;
	int * y1;

	x = ed_toint(ed,x,0,0);
	y = ed_toint(ed,y,1,0);
	x1 = ed_toint(ed,x1,0,1);
	y1 = ed_toint(ed,x1,1,1);

	int * d_x;
	int * d_y;
	int * d_x1;
	int * d_y1;
	int * d_r;
	int * d_g;
	int * d_b;

	int edge_num = ed.col/2;

	int edge_size = edge_num * sizeof(int);
	int size = (X_MAX - X_MIN) * (Y_MAX - Y_MIN) * sizeof(int);


    gp_drawline<<<edge_num,1>>>(d_r, d_g, d_b, 
							    d_x, d_y, 
							    d_x1, d_y1, 
							    color[0],color[1],color[2]);

    return arr;
}
*/
