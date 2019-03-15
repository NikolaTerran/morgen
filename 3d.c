#include "engine.h"

/*note
	torus matrix
	[cos@  @ sin@]   [rcos@ + R]
	[@     1   @ ] * [rsin@ + @]
	[-sin@ @     ]   [@        ]
*/

struct Matrix sphere(struct Matrix mx, double x, double y, double z, double r){
	double t = 0;
	struct Matrix trans = mx_init(4,1);
	trans = mx_set(mx,0,0,x);
	trans = mx_set(mx,1,0,y);
	trans = mx_set(mx,2,0,z);
	trans = mx_set(mx,3,0,1);
	//t += t_step * (2 * M_PI);
	while(t <= (2 * M_PI) + td_step){
		mx = circle(mx, mx_get(trans,0,0) , mx_get(trans,1,0) , mx_get(trans,2,0), r);
		trans = mx_mult(mx_rotate(mx,td_axis,t),trans);
		t += td_step;
		printf("t: %f\n",t);
	}
	return mx;
}
