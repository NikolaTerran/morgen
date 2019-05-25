#include "engine.h"

struct Light light_init(double arc, double drc, double src,
                        int ambient_r, int ambient_g, int ambient_b,
                        int diffused_r, int diffused_g, int diffused_b,
                        int specular_r, int specular_g, int specular_b,
                        double light_x, double light_y, double light_z,
                        int shininess){
      struct Light lt;
      lt.drc = malloc(sizeof(double));
      lt.src = malloc(sizeof(double));
      lt.diffused_r = malloc(sizeof(int));
      lt.diffused_g = malloc(sizeof(int));
      lt.diffused_b = malloc(sizeof(int));
      lt.specular_r = malloc(sizeof(int));
      lt.specular_g = malloc(sizeof(int));
      lt.specular_b = malloc(sizeof(int));
      lt.light_x = malloc(sizeof(double));
      lt.light_y = malloc(sizeof(double));
      lt.light_z = malloc(sizeof(double));
      lt.shininess = malloc(sizeof(int));
      lt.arc = arc;
      lt.drc[0] = drc;
      lt.src[0] = src;
      lt.ambient_r = ambient_r;
      lt.ambient_g = ambient_g;
      lt.ambient_b = ambient_b;
      lt.diffused_r[0] = diffused_r;
      lt.diffused_g[0] = diffused_g;
      lt.diffused_b[0] = diffused_b;
      lt.specular_r[0] = specular_r;
      lt.specular_g[0] = specular_g;
      lt.specular_b[0] = specular_b;
      lt.light_x[0] = light_x;
      lt.light_y[0] = light_y;
      lt.light_z[0] = light_z;
      lt.shininess[0] = shininess;
      lt.size = 1;
      return lt;
}

struct Light light_append(){

}

struct Light light_rotate(){

}

double refect_vector(char dir, double nx, double ny, double nz, double lx, double ly, double lz){
  if(dir == 'x'){
    return 2 * lt_dot_pdt(nx,ny,nz,lx,ly,lz) * nx - lx;
  }else if(dir == 'y'){
    return 2 * lt_dot_pdt(nx,ny,nz,lx,ly,lz) * ny - ly;
  }else if(dir == 'z'){
    return 2 * lt_dot_pdt(nx,ny,nz,lx,ly,lz) * nz - lz;
  }
}

double lt_dot_pdt(double x, double y, double z, double x1, double y1, double z1){
	//double ok = x * VIEW_X + y * VIEW_Y + z * VIEW_Z;
	//printf("ok:%d\n",x * x1 + y * y1 + z * z1);

	return x * x1 + y * y1 + z * z1;

}
