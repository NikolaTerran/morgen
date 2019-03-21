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

struct Matrix add_box(struct Matrix mx, double x1, double y1, double z1,
										double h, double l, double w){
	mx = addedge(mx,x1    , y1    , z1    , x1 + w, y1    , z1    );
	mx = addedge(mx,x1    , y1    , z1    , x1    , y1 + h, z1    );
	mx = addedge(mx,x1    , y1    , z1    , x1    , y1    , z1 + l);
	mx = addedge(mx,x1    , y1    , z1 + l, x1 + w, y1    , z1 + l);
	mx = addedge(mx,x1    , y1    , z1 + l, x1    , y1 + h, z1 + l);
	mx = addedge(mx,x1 + w, y1    , z1 + l, x1 + w, y1    , z1	  );
	mx = addedge(mx,x1 + w, y1    , z1    , x1 + w, y1 + h, z1    );
	mx = addedge(mx,x1    , y1 + h, z1    , x1 + w, y1 + h, z1    );
	mx = addedge(mx,x1    , y1 + h, z1 + l, x1    , y1 + h, z1    );
	mx = addedge(mx,x1    , y1 + h, z1 + l, x1 + w, y1 + h, z1 + l);
	mx = addedge(mx,x1 + w, y1 + h, z1 + l, x1 + w, y1    , z1 + l);
	mx = addedge(mx,x1 + w, y1 + h, z1 + l, x1 + w, y1 + h, z1    );

	return mx;

}

/* wait for the implementation of points
struct Matrix add_box(struct Matrix mx, double p1, double p2, double p3, double p4,
										double p5, double p6, double p7, double p8){
	//mx = add_edge(mx,p1,p2);


	return mx;
}
*/