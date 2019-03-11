#include "engine.h"

//this is probably the stupidest way to do it, but I'm braindead whenever I'm dealing with math
//array start with 1, because I hate math 

struct Matrix bezier(struct Matrix mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
	//struct Matrix result;
	//struct Matrix curve;
	//curve = mx_init(4,2);
	//curve.row = 4;
	double t = t_step;
	
	int xx = x1;
	int yy = x4;
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

struct Matrix hermite(struct Matrix mx, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
	//f(p_0,v_0,v_1,p_1,t) = p_0(2 t^3-3 t^2+1)+v_1(t^3-t^2)+v_0(t^3-2 t^2+t)+p_1(3 t^2-2 t^3)
}
