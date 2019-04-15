#include "engine.h"

/*note
	torus matrix
	[cos@  @ sin@]   [rcos@ + R]
	[@     1   @ ] * [rsin@ + @]
	[-sin@ @     ]   [@        ]
*/

struct Matrix sphere_helper(struct Matrix src, struct Matrix src2, struct Matrix dst){
		//mx_print(src);

		int lim = dst.col + (src.col - 2) * 2;

		printf("lim:%d\n",lim);
		dst.x = (int *)realloc(dst.x,lim);
		dst.y = (int *)realloc(dst.y,lim);
		dst.z = (int *)realloc(dst.z,lim);
		
		
		
		int i = dst.col;
		int j = 0;
		
		dst.x[i] = src.x[j];
		dst.y[i] = src.y[j];
		dst.z[i] = src.z[j];
		
		i++; j++;
		
		dst.x[i] = src.x[j];
		dst.y[i] = src.y[j];
		dst.z[i] = src.z[j];			
		
		i++;
		
		dst.x[i] = src2.x[j];
		dst.y[i] = src2.y[j];
		dst.z[i] = src2.z[j];
		
		i++;
		
		for(i; i < lim; i++){

		dst.x[i] = src.x[j];
		dst.y[i] = src.y[j];
		dst.z[i] = src.z[j];
		
		i++; 
		
		dst.x[i] = src2.x[j];
		dst.y[i] = src2.y[j];
		dst.z[i] = src2.z[j];			
		
		i++; j++;
		
		dst.x[i] = src.x[j];
		dst.y[i] = src.y[j];
		dst.z[i] = src.z[j];
			
		i++;

		dst.x[i] = src.x[j];
		dst.y[i] = src.y[j];
		dst.z[i] = src.z[j];
		
		i++;
		
		dst.x[i] = src2.x[j];
		dst.y[i] = src2.y[j];
		dst.z[i] = src2.z[j];
		
		i++; j--;
		
		dst.x[i] = src2.x[j];
		dst.y[i] = src2.y[j];
		dst.z[i] = src2.z[j];

		j++;
		}
		
		dst.x[i] = src.x[j];
		dst.y[i] = src.y[j];
		dst.z[i] = src.z[j];
		
		i++;
		
		dst.x[i] = src2.x[j];
		dst.y[i] = src2.y[j];
		dst.z[i] = src2.z[j];
		
		i++; j++;

		dst.x[i] = src2.x[j];
		dst.y[i] = src2.y[j];
		dst.z[i] = src2.z[j];		
		
		printf("i:%d\n , lim:%d\n",i,lim);
		dst.col = lim;
		mx_print(dst);
	 	return dst;	
}



struct Matrix mx_addsphere(struct Matrix mx, double x, double y, double z, double r){
	if(mx.type == 'a'){
		double t = 0;
			
		double step = M_PI * td_step;

		struct Matrix trans;
		struct Matrix result;
		trans  = mx_init(trans,0);
		result = mx_init(result,0);

		trans = mx_addcircle(trans, 0 , 0 , 0 , r);
		result = mx_addmatrix(trans,result);
		t += step;
		
		while(t <  M_PI){
			trans = mx_rotate(trans,td_axis,step);
			result = mx_addmatrix(trans,result);	

			t += step;
		}
		result = mx_transform(result,x,y,z);
		mx = mx_addmatrix(result,mx);
		mx_free(result);
		mx_free(trans);

		return mx;
	}else if(mx.type == 'c'){
		double t = 0;	
		double step = M_PI * td_step;

		struct Matrix trans;
		struct Matrix trans1;
		
		struct Matrix result;


		return mx;
	}else{
		printf("Error: mx_addsphere, matrix type not supported\n");
	}
}

struct Matrix draw_poly(struct Matrix mx){
	return mx;
}

struct Matrix mx_addtorus(struct Matrix mx, double x, double y, double z, double r, double d){
	if(mx.type = 'a'){
		double t = 0;
		double step = M_PI * td_step;
		struct Matrix trans;
		struct Matrix result;
		result = mx_init(result,0);
		trans = mx_init(trans,0);
		
		trans = mx_addcircle(trans, x + d , y , z , r);
		result = mx_addmatrix(trans,result);
		t += step;
		
		
		while(t < 2 * M_PI){
			
			trans = mx_rotate(trans,td_axis,step);
			result = mx_addmatrix(trans,result);
			t += step;
		//	printf("t: %f\n",t);
		}
		
		result = mx_transform(result,x,y,z);
		mx = mx_addmatrix(result,mx);
		
		
		mx_free(result);
		mx_free(trans);

		return mx;
	}
}

/*
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
*/
struct Matrix mx_addbox(struct Matrix mx, double x1, double y1, double z1,
						   				  double h, double l, double d){
	if(mx.type == 'c'){ 

		int i;

		// mx = addpoly(mx,x1,y1,z1, 
		// 				x1,y1 + h,z1,
		// 				x1,y1,z1 + d,
		// 				);

		// mx = addpoly(mx,x1,y1,z1, 
		// 				x1,y1 + h,z1,
		// 				x1,y1,z1 + d,
		// 				);

		// mx = addpoly(mx,x1,y1,z1, 
		// 				x1,y1 + h,z1,
		// 				x1,y1,z1 + d,
		// 				);

		return mx;
	}else if(mx.type == 'b'){

		mx = mx_addedge(mx,x1    , y1    , z1    , x1 + d, y1    , z1    );
		mx = mx_addedge(mx,x1    , y1    , z1    , x1    , y1 + h, z1    );
		mx = mx_addedge(mx,x1    , y1    , z1    , x1    , y1    , z1 + l);
		mx = mx_addedge(mx,x1    , y1    , z1 + l, x1 + d, y1    , z1 + l);
		mx = mx_addedge(mx,x1    , y1    , z1 + l, x1    , y1 + h, z1 + l);
		mx = mx_addedge(mx,x1 + d, y1    , z1 + l, x1 + d, y1    , z1	  );
		mx = mx_addedge(mx,x1 + d, y1    , z1    , x1 + d, y1 + h, z1    );
		mx = mx_addedge(mx,x1    , y1 + h, z1    , x1 + d, y1 + h, z1    );
		mx = mx_addedge(mx,x1    , y1 + h, z1 + l, x1    , y1 + h, z1    );
		mx = mx_addedge(mx,x1    , y1 + h, z1 + l, x1 + d, y1 + h, z1 + l);
		mx = mx_addedge(mx,x1 + d, y1 + h, z1 + l, x1 + d, y1    , z1 + l);
		mx = mx_addedge(mx,x1 + d, y1 + h, z1 + l, x1 + d, y1 + h, z1    );

		return mx;
	}
}

/* wait for the implementation of points
struct Matrix add_box(struct Matrix mx, double p1, double p2, double p3, double p4,
										double p5, double p6, double p7, double p8){
	//mx = add_edge(mx,p1,p2);


	return mx;
}
*/
