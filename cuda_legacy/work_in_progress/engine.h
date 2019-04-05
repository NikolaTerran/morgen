#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

///////////////////tweak////////////////////////////
#define INIT_VALUE 0   //init value of matrices
#define t_step 0.1   //drawing distance of curves
#define ERR_MARGIN 1   //error margin of circles
#define td_step 0.1   //drawing distance of 3d obj
#define td_axis 1      //axis of rotation of 3d obj

///////////////////array////////////////////////////
#define X_MIN -250
#define X_MAX 250
#define Y_MIN -250
#define Y_MAX 250

#define ARR_R 255
#define ARR_G 255
#define ARR_B 255

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess){
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

struct Array{
	int * d_r;
	int * d_g;
	int * d_b;
};

__global__ void gp_array_set(int * d_r,int * d_g,int * d_b, int *x, int *y, int r, int g, int b);

struct Array array_init(struct Array arr);
void array_print(struct Array arr);
void array_push(struct Array arr, char * filename);
struct Array arr_set(struct Array arr,int x, int y, int color[3]);

///////////////////poly////////////////////////////

///////////////////line/////////////////////////////
struct Array drawLine(struct Array arr, struct Edge ed, int color[3]);
struct Array DL(struct Array arr, int x1, int y1, int x2, int y2, int color[3]);
struct Array cp_drawLine(struct Array arr, struct Edge ed, int color[3]);
///////////////////point////////////////////////////
struct Matrix{
	double *d_x;
	double *d_y;
	double *d_z;
	double *d_c;
	double *d_v;

	int col;
};

struct Point point_init(struct Point pt,double x, double y, double z);
/////////////////////edge matrix//////////////////////////

struct Edge{
	double * grid;
	int row;
	int col;
	int num_edge;
};

void ed_print(struct Edge m1);
void ed_printf(struct Edge mx);
struct Edge ed_iden(struct Edge m1, int ba);
struct Edge ed_init(struct Edge mx, int row, int col);
double ed_get(struct Edge mx, int row, int col);
struct Edge ed_set(struct Edge mx, int row, int col, double val);
struct Edge ed_mult(struct Edge m1, struct Matrix m2);
void ed_free(struct Edge mx);
struct Edge ed_addc(struct Edge m1, struct Edge m2);
struct Edge ed_qac(struct Edge mx, double arr[],int size);
struct Edge ed_rmc(struct Edge mx);
struct Edge ed_addp(struct Edge mx, int x, int y, int z);
		//struct Matrix addedge(struct Matrix mx, double a, double b, double c, double d, double e, double f, double red, double green, double blue);

void ed_export(struct Edge mx, struct Array arr);

struct Edge ed_adde(struct Edge mx, int x, int y, int z, int x1, int y1, int z1);
int * ed_toint( struct Edge mx, int * ptr,int row,int select);
double * ed_todouble(struct Edge ed, double * ptr,int row);
/////////////////transformation///////////////////////
struct Matrix mx_dilation(struct Matrix mx, double x,double y, double z);
struct Matrix mx_transform(struct Matrix mx, double x, double y, double z);
struct Matrix mx_rotate(struct Matrix, int axis, double radian);
struct Matrix mx_yrev(struct Matrix mx);


/////////////////////curve////////////////////////////
struct Edge add_circle(struct Edge mx, double x, double y, double z, double r);
struct Edge add_bezier(struct Edge mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
struct Edge add_hermite(struct Edge mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
////////////////////3d///////////////////////////////
struct Matrix add_sphere(struct Matrix mx, double x, double y, double z, double r);
struct Matrix add_torus(struct Matrix mx, double x, double y, double z, double r, double d, int axis);
struct Matrix add_box(struct Matrix mx, double x1, double y1, double z1,
										double h, double l, double w);

////////////////////general//////////////////////////
void initialize(int array[][X_MAX - X_MIN][3], int color[]);
void push(int array[][X_MAX - X_MIN][3],int file);
int* sys_random(int size);
void db(char * say,double a);
