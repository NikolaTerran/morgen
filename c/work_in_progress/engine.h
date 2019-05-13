#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

///////////////////tweak////////////////////////////
#define INIT_VALUE 0   //init value of EVERYTHING other than Array
#define t_step 0.1//drawing distance of curves
#define ERR_MARGIN 1   //error margin of circles
#define td_step 0.1   //drawing distance of 3d obj
#define td_axis 1      //axis of rotation of 3d obj         //0 == x // 1 == y // 2 == z//
#define THREAD 4      //parallel programming

#define ray_step 1  //step for ray tracing

//////////////////View vector/////////////////////////////
#define VIEW_X 0
#define VIEW_Y 0
#define VIEW_Z 1


///////////////////canvas////////////////////////////
#define X_MIN -250
#define X_MAX 251
#define Y_MIN -251
#define Y_MAX 250
#define ARR_INIT_R 255
#define ARR_INIT_G 255
#define ARR_INIT_B 255
#define ARR_INIT_Z 1000000

struct Layer{
	int *r;
	int *g;
	int *b;
	int *z;
};

struct Layer lay_init();
// struct Array arr_init(struct Array arr);
// struct Array arr_set(struct Array arr, int *x, int *y, int res, int color[]);
// void arr_push(struct Array arr, char * filename);

void canvas_init();
void canvas_push(char * filename);
void canvas_set_p(int *x,int *y,int res,int color[]);
void canvas_set_s(int x, int y, int z,int color[]);
///////////////////3d///////////////////////////////
struct Matrix mx_addsphere(struct Matrix mx, double x, double y, double z, double r);
struct Matrix mx_addtorus(struct Matrix mx, double x, double y, double z, double r, double d);
struct Matrix mx_addbox(struct Matrix mx, double x1, double y1, double z1,
						   				  double h, double l, double d);
///////////////////ray//////////////////////////////
struct Ray{
	double * l_x;
	double * l_y;
	double * l_z;
	double * l_dx;
	double * l_dy;
	double * l_dz;

	double * s_x;
	double * s_y;
	double * s_z;
	double * s_dx;
	double * s_dy;
	double * s_dz;

	double * f_x;
	double * f_y;
	double * f_z;
	double * f_dx;
	double * f_dy;
	double * f_dz;

	double * r;
	double * g;
	double * b;

	double * cx;
	double * cy;
};

struct Ray ray_init(struct Ray ray);
/////////////////////matrix//////////////////////////

              /////////////////////////////////////////
              ////mx functions use math row and col////
              /////////////////////////////////////////

struct Matrix{
	double * x;
	double * y;
	double * z;
	double * vx;
	double * vy;
	double * vz;


	//double * one;
	double * edge_id;
	int edge_num;

	char type;
		//type 'a' = point
		//type 'b' = edge
		//type 'c' = polygon

	int col;

};

struct Matrix mx_init_p(struct Matrix mx, int col);
void mx_print(struct Matrix m1);
void mx_printf(struct Matrix mx);
struct Matrix mx_iden(struct Matrix m1, int ba);\

struct Matrix mx_init(struct Matrix mx, int col);
struct Matrix mx_init_e(struct Matrix mx, int col);

int * mx_toint(struct Matrix mx, int *result, int row);

double mx_get(struct Matrix mx, int row, int col);
struct Matrix mx_set(struct Matrix mx, int row, int col, double val);
void mx_free(struct Matrix mx);


		//struct Matrix addedge(struct Matrix mx, double a, double b, double c, double d, double e, double f, double red, double green, double blue);

void mx_export(struct Matrix mx, int color[]);
void db_export(struct Matrix mx);

struct Matrix mx_copy(struct Matrix src, struct Matrix dst);

/////////////////transformation///////////////////////
struct Matrix mx_dilate(struct Matrix mx, double x,double y, double z);
struct Matrix mx_transform(struct Matrix mx, double x, double y, double z);
struct Matrix mx_rotate(struct Matrix, int axis, double radian);
struct Matrix mx_yrev(struct Matrix mx);
struct Matrix mx_addmatrix(struct Matrix src, struct Matrix dst);

/////////////////////curve////////////////////////////

struct Matrix mx_addbezier(struct Matrix mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
struct Matrix mx_addcircle(struct Matrix mx, double x, double y, double z, double r);
struct Matrix mx_addhermite(struct Matrix mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);


////////////////////general//////////////////////////
void initialize(int array[][X_MAX - X_MIN][3], int color[]);
void push(int array[][X_MAX - X_MIN][3],int file);
int* sys_random(int * buffer, int size);
void db(char * say,double a);


///////////////////line/////////////////////////////
void drawLine(struct Matrix mx, int color[3]);
struct Matrix mx_addedge(struct Matrix mx, double a, double b, double c, double d, double e, double f);
void scanLine(struct Matrix mx);
void drawLine_test(int x, int y, int z, int x1, int y1, int z1, int color[3]);
//////////////////point/////////////////////////////
void drawPoint(struct Matrix mx, int color[3]);
struct Matrix mx_addpoint(struct Matrix mx, double x, double y, double z);

//////////////////util//////////////////////////////
double dot_pdt(double x, double y, double z);
