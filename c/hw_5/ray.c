include "engine.h"

struct Ray ray_init(struct Ray ray){
	int lim = (X_MAX - X_MIN) * (Y_MAX - Y_MIN);
	int i;
	int y = Y_MAX;
	int x = X_MIN;

	ray.l_x = malloc(lim * sizeof(double));
	ray.l_y = malloc(lim * sizeof(double));
	ray.l_z = malloc(lim * sizeof(double));

	ray.s_x = malloc(lim * sizeof(double));
	ray.s_y = malloc(lim * sizeof(double));
	ray.s_z = malloc(lim * sizeof(double));

	ray.r_x = malloc(lim * sizeof(double));
	ray.r_y = malloc(lim * sizeof(double));
	ray.r_z = malloc(lim * sizeof(double));
	
	ray.l_dx = malloc(lim * sizeof(double));
	ray.l_dy = malloc(lim * sizeof(double));
	ray.l_dz = malloc(lim * sizeof(double));
	
	ray.s_dx = malloc(lim * sizeof(double));
	ray.s_dy = malloc(lim * sizeof(double));
	ray.s_dz = malloc(lim * sizeof(double));
	
	ray.r_dx = malloc(lim * sizeof(double));
	ray.r_dy = malloc(lim * sizeof(double));
	ray.r_dz = malloc(lim * sizeof(double));

	ray.r = malloc(lim * sizeof(int));
	ray.g = malloc(lim * sizeof(int));
	ray.b = malloc(lim * sizeof(int));
	
	ray.cx = malloc(lim * sizeof(int));
	ray.cy = malloc(lim * sizeof(int));
	

	for(i = 0; i < lim; i++){
		ray.l_x[i] = 0;
		ray.l_y[i] = 0;
		ray.l_z[i] = 0;

		ray.s_x[i] = 0;
		ray.s_y[i] = 0;
		ray.s_z[i] = 0;
		ray.s_dx[i] = 0;
		ray.s_dy[i] = 0;
		ray.s_dz[i] = 0;

		ray.r_x[i] = 0;
		ray.r_y[i] = 0;
		ray.r_z[i] = 0;
		ray.r_dx[i] = 0;
		ray.r_dy[i] = 0;
		ray.r_dz[i] = 0;

		if(x < X_MAX){
			ray.cx[i] = x;
			ray.cy[i] = y;
			x++;
		}else{
			x = X_MIN;
			y--;
			ray.cx[i] = x;
			ray.cy[i] = y;
			x++;
		}

	ray.l_dz[i] = ray_step;
	ray.l_dx[i] = (x - 0)/ray_step;
	ray.l_dy[i] = (y - 0)/ray_step;

	ray.r[i] = RAY_INIT_R;
	ray.g[i] = RAY_INIT_G;
	ray.b[i] = RAY_INIT_B;
	}
}