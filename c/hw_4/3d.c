#include "engine.h"

/*note
	torus matrix
	[cos@  @ sin@]   [rcos@ + R]
	[@     1   @ ] * [rsin@ + @]
	[-sin@ @     ]   [@        ]
*/

struct Matrix add_sphere(struct Matrix mx, double x, double y, double z, double r){
	double t = 0;
	struct Matrix trans;
	struct Matrix result;
	result = mx_init(4,0);
	//t += t_step * (2 * M_PI);
	while(t <= (2 * M_PI) + td_step){
		trans = circle(mx, 0 , 0 , 0 , r);
		trans = mx_rotate(trans,td_axis,t);
		result = mx_addc(result,trans);
		t += td_step;
	//	printf("t: %f\n",t);
	}
	result = mx_transform(result,x,y,z);
	mx = mx_addc(mx,result);
	//mx_print(trans);
	//trans = mx_transform(trans,x,y,z);
	//mx = mx_addc(mx,trans);
	return mx;
}

struct Matrix draw_poly(struct Matrix mx){
	return mx;
}

struct Matrix add_torus(struct Matrix mx, double x, double y, double z, double r, double d, int axis){
	double t = 0;
	struct Matrix trans;
	struct Matrix result;
	result = mx_init(4,0);
	//t += t_step * (2 * M_PI);
	double a = 0;
	double b = 0;
	double c = 0;

	if(axis == 0){
		b = d;
	}else if(axis == 1){
		a = d;
	}else{
		c = d;
	}
	while(t <= (2 * M_PI) + td_step){
		trans = circle(mx, a , b , c , r);
		trans = mx_rotate(trans,axis,t);
		result = mx_addc(result,trans);
		t += td_step;
	//	printf("t: %f\n",t);
	}
	result = mx_transform(result,x,y,z);
	mx = mx_addc(mx,result);

	return mx;
}

struct Matrix mx_addpoly(struct Matrix mx, double x1, double y1, double z1,
										   double x2, double y2, double z2,
										   double x3, double y3, double z3,
										   double v1, double v2, double v3){
	mx.x = realloc(mx.x,(mx.col + 3) * sizeof(double));
	mx.y = realloc(mx.y,(mx.col + 3) * sizeof(double));
	mx.z = realloc(mx.z,(mx.col + 3) * sizeof(double));
	mx.v = realloc(mx.v,(mx.col + 3) * sizeof(double));

	//mx.col += 3;
	mx.x[mx.col] = x1;
	mx.x[mx.col + 1] = x2;
	mx.x[mx.col + 2] = x3; 

	mx.y[mx.col] = y1;
	mx.y[mx.col + 1] = y2;
	mx.y[mx.col + 2] = y3;

	mx.z[mx.col] = y1;
	mx.z[mx.col + 1] = y2;
	mx.z[mx.col + 2] = y3;

	mx.v[mx.col] = v1;
	mx.v[mx.col + 1] = v2;
	mx.v[mx.col + 2] = v3;

	mx.col += 3;
}

struct Matrix mx_addbox(struct Matrix mx, double x1, double y1, double z1,
						   				  double h, double l, double d){
	if(mx.type != 'c'){ 
		printf("Error: mx_addbox, incomplatible matrix type\n");
		printf("Note: expected matrix type \'c\', but received matrix type \'%c\'\n",mx.type);
		exit(1);
	}

	int i;

	mx = addpoly(mx,x1,y1,z1, 
					x1,y1 + h,z1,
					x1,y1,z1 + d,
					);
/*
	mx = addpoly(mx,x1,y1,z1, 
					x1,y1 + h,z1,
					x1,y1,z1 + d,
					);

	mx = addpoly(mx,x1,y1,z1, 
					x1,y1 + h,z1,
					x1,y1,z1 + d,
					);

*/




	return mx;
}

/* wait for the implementation of points
struct Matrix add_box(struct Matrix mx, double p1, double p2, double p3, double p4,
										double p5, double p6, double p7, double p8){
	//mx = add_edge(mx,p1,p2);


	return mx;
}
*/
