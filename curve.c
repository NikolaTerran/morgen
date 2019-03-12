#include "engine.h"

//array start with 1, because I hate math 
//For bezier, p1 and p4 are endpoints. p2 and p3 are contral points
struct Matrix circle(struct Matrix mx, double x, double y, double z, double r){
	double t = 0;
	double xx = r * cos(t) + x;
	double yy = r * sin(t) + y;
	//t += t_step * (2 * M_PI);
	while(t <= (2 * M_PI) + ERR_MARGIN){
		double xxx = r * cos(t) + x;
		double yyy = r * sin(t) + y;
		mx = addedge(mx,xx,yy,z,xxx,yyy,z);
		xx = xxx;
		yy = yyy;
		t = t + t_step * (2 * M_PI);
	}
	return mx;
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
struct Matrix bezier(struct Matrix mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
	double t = 0;
	int xx = x1;
	int yy = y1;
	while(t <= 1){
		double xxx = (1-t) * ((1-t) * ((1-t) * x1 + t * x2) + t * ((1-t) * x2 + t * x3)) + t * ((1-t) * ((1-t) * x2 + t * x3) + t * ((1-t) * x3 + t * x4));
		double yyy = (1-t) * ((1-t) * ((1-t) * y1 + t * y2) + t * ((1-t) * y2 + t * y3)) + t * ((1-t) * ((1-t) * y2 + t * y3) + t * ((1-t) * y3 + t * y4));
		mx = addedge(mx,xx,yy,0,xxx,yyy,0);
		xx = xxx;
		yy = yyy;
		t = t + t_step;
	}
	return mx;
}
//*/

struct Matrix hermite(struct Matrix mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
	double t = 0;
	int xx = x1;
	int yy = y1;
//	f(p_0,v_0,v_1,p_1,t) = p_0(2 t^3-3 t^2+1)+v_1(t^3-t^2)+v_0(t^3-2 t^2+t)+p_1(3 t^2-2 t^3)
}
