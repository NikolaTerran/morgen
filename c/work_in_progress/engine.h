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
#define t_step 0.05   //drawing distance of curves
#define ERR_MARGIN 1   //error margin of circles
#define td_step 0.5   //drawing distance of 3d obj
#define td_axis 1      //axis of rotation of 3d obj
#define THREAD 4      //parallel programming

///////////////////canvas////////////////////////////
#define X_MIN -250
#define X_MAX 250
#define Y_MIN -250
#define Y_MAX 250
#define ARR_INIT_R 255
#define ARR_INIT_G 255
#define ARR_INIT_B 255

// struct Array arr_init(struct Array arr);
// struct Array arr_set(struct Array arr, int *x, int *y, int res, int color[]);
// void arr_push(struct Array arr, char * filename);

void canvas_init();
void canvas_push(char * filename);
void canvas_set(int *x,int *y,int res,int color[]);
///////////////////poly////////////////////////////

///////////////////line/////////////////////////////
int drawLine(int array[][500][3], int x1, int y1, int x2, int y2, int color[]);
void line_helper(int array[][500][3], int x1, int y1, int x2, int y2, int x3, int y3, int octants, int color[], double m);

///////////////////point////////////////////////////
struct Point{
	double x;
	double y;
	double z;
};

/////////////////////matrix//////////////////////////
              
              /////////////////////////////////////////
              ////mx functions use math row and col////
              /////////////////////////////////////////

struct Matrix{
	double * x;
	double * y;
	double * z;
	double * one;
	
	double * edge_id;
	int edge_num;

	char type;
		//type 'a' = point
		//type 'b' = edge
		//type 'c' = polygon

	int col;
	
};

void mx_print(struct Matrix m1);
void mx_printf(struct Matrix mx);
struct Matrix mx_iden(struct Matrix m1, int ba);\

struct Matrix mx_init(struct Matrix mx, int col);
struct Matrix mx_init_e(struct Matrix mx, int col);

int * mx_toint(struct Matrix mx, int result[], int row, int odd_even);
double mx_get(struct Matrix mx, int row, int col);
struct Matrix mx_set(struct Matrix mx, int row, int col, double val);
struct Matrix mx_mult(struct Matrix m1, struct Matrix m2);
void mx_free(struct Matrix mx);
struct Matrix mx_addc(struct Matrix m1, struct Matrix m2);
struct Matrix mx_qac(struct Matrix mx, double arr[],int size);
struct Matrix mx_rmc(struct Matrix mx);
struct Matrix addpoint(struct Matrix mx, double a, double b, double c, double red, double green, double blue);
		//struct Matrix addedge(struct Matrix mx, double a, double b, double c, double d, double e, double f, double red, double green, double blue);

void mx_export(struct Matrix mx, int arg);

struct Matrix mx_addedge(struct Matrix mx, double a, double b, double c, double d, double e, double f);


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



