#include "engine.h"

//array start with 1, because I hate math 
struct Matrix bezier(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
	//struct Matrix result;
	struct Matrix curve;
	//curve = mx_init(4,2);
	curve.row = 4;
	double t = 0;
	
	int xx = x1;
	int yy = x4;
	while(t < 1){
		int xxx = (1-t) * ((1-t) * ((1-t) * x1 + t * x2) + t * ((1-t) * x2 + t * x3)) + t * ((1-t) * ((1-t) * x2 + t * x3) + t * ((1-t) * x3 + t * x4));
		
		int yyy = (1-t) * ((1-t) * ((1-t) * y1 + t * y2) + t * ((1-t) * y2 + t * y3)) + t * ((1-t) * ((1-t) * y2 + t * y3) + t * ((1-t) * y3 + t * y4));
		curve = addedge(edge,xx,yy,0,xxx,yyy,0);
		xx = xxx;
		yy = yyy;
		t = t + 0.05;
	}
	return curve;
}
