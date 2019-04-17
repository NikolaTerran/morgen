#include "engine.h"

//array start with 1, because I hate math
//For bezier, p1 and p4 are endpoints. p2 and p3 are contral points
struct Matrix mx_addcircle(struct Matrix mx, double x, double y, double z, double r){
	if(mx.type =='b'){
		double t = 0;
		double xx = r * cos(t) + x;
		double yy = r * sin(t) + y;
		//t += t_step * (2 * M_PI);
		double xxx;
		double yyy;
		while(t <= (2 * M_PI) + t_step){
			xxx = r * cos(t) + x;
			yyy = r * sin(t) + y;
			mx = mx_addedge(mx,xx,yy,z,xxx,yyy,z);
			xx = xxx;
			yy = yyy;
			t = t + t_step * (2 * M_PI);
		}
		return mx;
	}else if(mx.type == 'a'){
		double t = 0;
		double xx = r * cos(t) + x;
		double yy = r * sin(t) + y;
		//t += t_step * (2 * M_PI);
		while(t <= (2 * M_PI) + t_step){
			xx = r * cos(t) + x;
			yy = r * sin(t) + y;
			mx = mx_addpoint(mx,xx,yy,z);

			t = t + t_step * (2 * M_PI);
		}
		return mx;
	}else if(mx.type == 'c'){
		double t = 0;
		double xx = r * cos(t) + x;
		double yy = r * sin(t) + y;
		//t += t_step * (2 * M_PI);
		while(t <=  M_PI + t_step){
			xx = r * cos(t) + x;
			yy = r * sin(t) + y;
			mx = mx_addpoint(mx,xx,yy,z);

			t = t + t_step * (2 * M_PI);
		}
		return mx;
	}else{
		printf("Error: mx_addcircle, matrix type note supported\n");
		exit(1);
	}
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

// The stupid way to do the bezier
struct Matrix mx_addbezier(struct Matrix mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
	double t = 0;
	double xx = x1;
	double yy = y1;
	double xxx;
	double yyy;
	while(t <= 1 + t_step){
		xxx = (1-t) * ((1-t) * ((1-t) * x1 + t * x2) + t * ((1-t) * x2 + t * x3)) + t * ((1-t) * ((1-t) * x2 + t * x3) + t * ((1-t) * x3 + t * x4));
		yyy = (1-t) * ((1-t) * ((1-t) * y1 + t * y2) + t * ((1-t) * y2 + t * y3)) + t * ((1-t) * ((1-t) * y2 + t * y3) + t * ((1-t) * y3 + t * y4));
		mx = mx_addedge(mx,xx,yy,0,xxx,yyy,0);
		xx = xxx;
		yy = yyy;
		t = t + t_step;
	}
	return mx;
}
//*/

struct Matrix mx_addhermite(struct Matrix mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
	double t = t_step;
	double xx = x1;
	double yy = y1;
	double xxx;
	double yyy;
	while(t <= 1 + t_step){
		xxx = x1 * (2 * pow(t,3) - 3 * pow(t,2) + 1) + x3 * (pow(t,3) -pow(t,2)) + x2 * (pow(t,3) - 2 * pow(t,2) + t) + x4 * (3 * pow(t,2) - 2 * pow(t,3));
		yyy = y1 * (2 * pow(t,3) - 3 * pow(t,2) + 1) + y3 * (pow(t,3) -pow(t,2)) + y2 * (pow(t,3) - 2 * pow(t,2) + t) + y4 * (3 * pow(t,2) - 2 * pow(t,3));
		mx = mx_addedge(mx,xx,yy,0,xxx,yyy,0);
		xx = xxx;
		yy = yyy;
		t += t_step;
	}

	return mx;
}
