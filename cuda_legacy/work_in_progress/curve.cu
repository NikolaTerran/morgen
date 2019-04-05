#include "engine.h"

/*
__global__ void gp_add_edge(double * d_grid, 
	    				    double * h_grid,
						    double *x, double *y, double z,
						    double *x1, double *y1,int col1,int col2,int row){
int index = blockIdx.x * blockDim.x + threadIdx.x;

int col_size = col1 + col2;

//
	if((index % col_size) < col1){
		//printf("index:%d\n",index);
		//printf("h_grid-index:%f\n",h_grid[index]);
		//printf("ola:%d\n",(index / col_size * col1) + index % col1);
		//printf("index:%d\n",index % 2);
		d_grid[index] = h_grid[(index / col_size * col1) + index % col1];
	    //d_grid[(index / col1) * col_size + index % col1] = h_grid[index];
	}else{
		//printf("lala:%d\n",index / col_size);

		if(index / col_size == 0){
			
		   if(index % 2 == 0){
  			   d_grid[index] = x[(index - col1) / 2];
		   }else{
		   	   d_grid[index] = x1[(index - col1) /2];
		   }
	
		}else if(index / col_size == 1){
		   if(index % 2 == 0){
  			   d_grid[index] = y[(index - col1) / 2];
		   }else{
		   	   d_grid[index] = y1[(index - col1) /2];
		   }
		}else if(index / col_size == 2){
			d_grid[index] = z;
		}else{
			d_grid[index] = 1;
		}
	}
//printf("index:%d\n",index);
}

struct Edge add_circle(struct Edge mx, double x, double y, double z, double r){
	double t = 0;
	double xx = r * cos(t) + x;
	double yy = r * sin(t) + y;
	//t += t_step * (2 * M_PI);
	double * x1;
	double * y1;
	double * x2;
	double * y2;

	int i;
	while(t <= (2 * M_PI) + t_step){
		double xxx = r * cos(t) + x;
		double yyy = r * sin(t) + y;
		//mx = ed_adde(mx,xx,yy,z,xxx,yyy,z);
		x1[i] = xx;
		y1[i] = yy;
		x2[i] = xxx;
		y2[i] = yyy;


		xx = xxx;
		yy = yyy;
		t = t + t_step * (2 * M_PI);
	}
	return mx;
}

/*I give up
struct Matrix bezier(struct Matrix mx, double x1, double y1, double x2, double y2, double x3. double y3, double x4, double y4){
	double t = 0;
	struct Matrix curve;
	curve = mx_init(4,4);
	mx_set(curve,0,0,1);
	mx_set(curve,1,3,1);
	mx_set(curve,2,0,-3);
	mx_set(curve,2,1,3);
	mx_set(curve,3,2,-3);
	mx_set(curve,3,3,3);

	
}
*/

/*
// The stupid way to do the bezier
struct Edge add_bezier(struct Edge mx, double x1, double y1, double x2, double y2, 
									   double x3, double y3, double x4, double y4){
	
	//printf("mx.col:%d\n",mx.col);

	double t = 0;
	int xx = x1;
	int yy = y1;
	double size = (1 + 2 * t_step)/t_step;

	//printf("size:%f\n",size);

	double d_size = size * sizeof(double);
	double col_size = mx.col * sizeof(double);
	int grid_size = (mx.row * mx.col) * sizeof(double);


	double * h_x;
	double * h_y;
	double * h_x1;
	double * h_y1;

	h_x = (double *)malloc(d_size);
	h_y = (double *)malloc(d_size);
	h_x1 = (double *)malloc(d_size);
	h_y1 = (double *)malloc(d_size);

	
	double * d_x;
	double * d_y;
	double * d_x1;
	double * d_y1;
	double * d_grid;
	double * h_grid;

	cudaMalloc((void **)&d_x,d_size);
	cudaMalloc((void **)&d_y,d_size);
	cudaMalloc((void **)&d_x1,d_size);
	cudaMalloc((void **)&d_y1,d_size);
	cudaMalloc((void **)&h_grid,grid_size);
	cudaMalloc((void **)&d_grid,(mx.col + 2 * size) * (mx.row) * sizeof(double));

	int i = 0;
	int malloc_size = (mx.col + size) * (mx.row) * sizeof(double);

	while(t <= 1 + t_step){
		double xxx = (1-t) * ((1-t) * ((1-t) * x1 + t * x2) + t * ((1-t) * x2 + t * x3)) + t * ((1-t) * ((1-t) * x2 + t * x3) + t * ((1-t) * x3 + t * x4));
		double yyy = (1-t) * ((1-t) * ((1-t) * y1 + t * y2) + t * ((1-t) * y2 + t * y3)) + t * ((1-t) * ((1-t) * y2 + t * y3) + t * ((1-t) * y3 + t * y4));
		//mx = ed_adde(mx,xx,yy,0,xxx,yyy,0);
		
		h_x[i] = xx;
		h_y[i] = yy;
		h_x1[i] = xxx;
		h_y1[i] = yyy;
		
		printf("h_x:%f\n",h_x[i]);
		printf("h_x1:%f\n",h_x1[i]);
		xx = xxx;
		yy = yyy;
		t = t + t_step;
		i++;
	}

    cudaMemcpy(d_x,h_x,d_size,cudaMemcpyHostToDevice);
    cudaMemcpy(d_y,h_y,d_size,cudaMemcpyHostToDevice);
    cudaMemcpy(d_x1,h_x1,d_size,cudaMemcpyHostToDevice);
    cudaMemcpy(d_y1,h_y1,d_size,cudaMemcpyHostToDevice);      
    cudaMemcpy(h_grid,mx.grid,grid_size,cudaMemcpyHostToDevice);
    //cudaMemcpy(d_grid,,col_size,cudaMemcpyHostToDevice);

    gp_add_edge<<<mx.col + 2 * size,mx.row>>>(d_grid,h_grid,
    									  d_x, d_y, 0,
						    			  d_x1, d_y1,mx.col,2 * size,mx.row);

    ed_free(mx);
    mx = ed_init(mx,mx.row,mx.col + (2 * size));

    cudaDeviceSynchronize();

    cudaMemcpy(mx.grid,d_grid,malloc_size,cudaMemcpyDeviceToHost);
    	ed_print(mx);
    //ed_print(mx);

	free(h_x);
	free(h_y);
	free(h_x1);
	free(h_y1);

	cudaFree(d_x);
	cudaFree(d_x1);
	cudaFree(d_y);
	cudaFree(d_y1);
	cudaFree(d_grid);
	cudaFree(h_grid);

	return mx;
}
//*/

/*
struct Edge add_hermite(struct Edge mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
	double t = t_step;
	double xx = x1;
	double yy = y1;
	while(t <= 1 + t_step){
		double xxx = x1 * (2 * pow(t,3) - 3 * pow(t,2) + 1) + x3 * (pow(t,3) -pow(t,2)) + x2 * (pow(t,3) - 2 * pow(t,2) + t) + x4 * (3 * pow(t,2) - 2 * pow(t,3));
		double yyy = y1 * (2 * pow(t,3) - 3 * pow(t,2) + 1) + y3 * (pow(t,3) -pow(t,2)) + y2 * (pow(t,3) - 2 * pow(t,2) + t) + y4 * (3 * pow(t,2) - 2 * pow(t,3));
		mx = ed_adde(mx,xx,yy,0,xxx,yyy,0);
		xx = xxx;
		yy = yyy;
		t += t_step;
	}
	return mx;
}
*/
