#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
///////////////////line/////////////////////////////
int drawLine(int array[][500][3], int x1, int y1, int x2, int y2, int color[]);
void line_helper(int array[][500][3], int x1, int y1, int x2, int y2, int x3, int y3, int octants, int color[], double m);


/////////////////////matrix//////////////////////////

struct Matrix{
	double * grid;
	int row;
	int col;
};

void mx_print(struct Matrix m1);
void mx_printf(struct Matrix mx);
struct Matrix mx_iden(struct Matrix m1, int ba);
struct Matrix mx_init(int row, int col);
double mx_get(struct Matrix mx, int row, int col);
struct Matrix mx_set(struct Matrix mx, int row, int col, double val);
struct Matrix mx_mult(struct Matrix m1, struct Matrix m2);
void mx_free(struct Matrix mx);
struct Matrix mx_addc(struct Matrix m1, struct Matrix m2);
struct Matrix mx_qac(struct Matrix mx, double arr[],int size);
struct Matrix mx_rmc(struct Matrix mx);
struct Matrix addpoint(struct Matrix mx, double a, double b, double c, double red, double green, double blue);
//struct Matrix addedge(struct Matrix mx, double a, double b, double c, double d, double e, double f, double red, double green, double blue);
struct Matrix addedge(struct Matrix mx, double a, double b, double c, double d, double e, double f);
void mx_export(struct Matrix mx);
struct Matrix mx_dilation(struct Matrix mx, double factor);
struct Matrix mx_transform(struct Matrix mx, double x, double y, double z);
struct Matrix mx_rotate(struct Matrix, char axis, double radian);
////////////////////general//////////////////////////
void initialize(int array[][500][3], int color[]);
void push(int array[][500][3],int file);
int* sys_random(int size);
void db(char * say,double a);



