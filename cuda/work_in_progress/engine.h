#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

///////////////////tweak////////////////////////////
#define INIT_VALUE 0   //init value of matrices
#define t_step 0.05   //drawing distance of curves
#define ERR_MARGIN 1   //error margin of circles
#define td_step 0.5   //drawing distance of 3d obj
#define td_axis 1      //axis of rotation of 3d obj

///////////////////array////////////////////////////
#define X_MIN -250
#define X_MAX 250
#define Y_MIN -250
#define Y_MAX 250

#define ARR_R 255
#define ARR_G 255
#define ARR_B 255

struct Array{
	int * r;
	int * g;
	int * b;
};

struct Array array_init(struct Array arr);
void array_print(struct Array arr);
void array_push(struct Array arr, char * filename);
struct Array arr_set(struct Array arr,int x, int y, int color[3]);

///////////////////poly////////////////////////////

///////////////////line/////////////////////////////
int drawLine(int array[][500][3], int x1, int y1, int x2, int y2, int color[]);
void line_helper(int array[][500][3], int x1, int y1, int x2, int y2, int x3, int y3, int octants, int color[], double m);

struct Array DL(struct Array arr, int x1, int y1, int x2, int y2, int color[3]);
///////////////////point////////////////////////////
struct Point{
	double x;
	double y;
	double z;
	double cons;
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
void mx_free(struct Edge mx);
struct Edge ed_addc(struct Edge m1, struct Edge m2);
struct Edge ed_qac(struct Edge mx, double arr[],int size);
struct Edge ed_rmc(struct Edge mx);
struct Edge ed_addp(struct Edge mx, int x, int y, int z);
		//struct Matrix addedge(struct Matrix mx, double a, double b, double c, double d, double e, double f, double red, double green, double blue);

void ed_export(struct Edge mx, struct Array arr);

struct Edge ed_adde(struct Edge mx, int x, int y, int z, int x1, int y1, int z1);
int * ed_toint( struct Edge mx, int * ptr,int row,int select);

/////////////////transformation///////////////////////
struct Matrix mx_dilation(struct Matrix mx, double x,double y, double z);
struct Matrix mx_transform(struct Matrix mx, double x, double y, double z);
struct Matrix mx_rotate(struct Matrix, int axis, double radian);
struct Matrix mx_yrev(struct Matrix mx);


/////////////////////curve////////////////////////////

struct Matrix bezier(struct Matrix mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
struct Matrix circle(struct Matrix mx, double x, double y, double z, double r);
struct Matrix hermite(struct Matrix mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

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
