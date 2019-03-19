#include "engine.h"

/*note
	torus matrix
	[cos@  @ sin@]   [rcos@ + R]
	[@     1   @ ] * [rsin@ + @]
	[-sin@ @     ]   [@        ]
*/

struct Matrix sphere(struct Matrix mx, double x, double y, double z, double r){
	double t = 0;
	struct Matrix trans;
	struct Matrix result;
	result = mx_init(4,0);
	//t += t_step * (2 * M_PI);
	while(t <= (2 * M_PI) + td_step){
		trans = circle(mx, 0 , 0 , 0 , r);
		trans = mx_mult(mx_rotate(trans,td_axis,t),trans);
		result = mx_addc(result,trans);
		t += td_step;
		printf("t: %f\n",t);
	}
	result = mx_transform(result,x,y,z);
	mx = mx_addc(mx,result);
	mx_print(trans);
	//trans = mx_transform(trans,x,y,z);
	//mx = mx_addc(mx,trans);
	return mx;
}
