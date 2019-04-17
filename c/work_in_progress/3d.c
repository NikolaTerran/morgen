#include "engine.h"

/*note
	torus matrix
	[cos@  @ sin@]   [rcos@ + R]
	[@     1   @ ] * [rsin@ + @]
	[-sin@ @     ]   [@        ]
*/

/* lighting

* in realistic images, object color is based on:
	0) the color and position of light sources
	1) the reflective properties of the object
	2)

*/


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
		double t = M_PI / 2;
		double step = M_PI * td_step;

		struct Matrix trans;
		struct Matrix trans1;
		struct Matrix result;

		trans = mx_init(trans,0);
		trans1 = mx_init(trans1,0);
		result = mx_init_p(result,0);

		double xx = r * cos(t);
		double yy = r * sin(t);
		//t += t_step * (2 * M_PI);


		while(t <= 3 * M_PI / 2 + t_step){
			xx = r * cos(t);
			yy = r * sin(t);
			trans = mx_addpoint(trans,xx,yy,0);
			trans1 = mx_addpoint(trans1,xx,yy,0);
			t = t + t_step * ( M_PI);
		}

		trans1 = mx_rotate(trans1,td_axis,step);
		int i;


		for(t = 0; t < 2 * M_PI ; t += td_step){
			int lim = result.col + (trans.col - 2) * 6;

			result.x = realloc(result.x,lim * sizeof(double));
			result.y = realloc(result.y,lim * sizeof(double));
			result.z = realloc(result.z,lim * sizeof(double));

			int i,j;
			i = result.col;
			j = 0;

			//printf("hi!\n");
			/* first polygon */

			result.x[i] = trans.x[j];
			result.y[i] = trans.y[j];
			result.z[i] = trans.z[j];


			i++; j++;

			result.x[i] = trans.x[j];
			result.y[i] = trans.y[j];
			result.z[i] = trans.z[j];

			i++;

			result.x[i] = trans1.x[j];
			result.y[i] = trans1.y[j];
			result.z[i] = trans1.z[j];

			i++;
			/* end of first polygon */

			while(i < lim - 3){
				result.x[i] = trans.x[j];
				result.y[i] = trans.y[j];
				result.z[i] = trans.z[j];

				i++;

				result.x[i] = trans1.x[j];
				result.y[i] = trans1.y[j];
				result.z[i] = trans1.z[j];

				i++; j++;

				result.x[i] = trans.x[j];
				result.y[i] = trans.y[j];
				result.z[i] = trans.z[j];

				i++;

				result.x[i] = trans.x[j];
				result.y[i] = trans.y[j];
				result.z[i] = trans.z[j];

				i++;

				result.x[i] = trans1.x[j];
				result.y[i] = trans1.y[j];
				result.z[i] = trans1.z[j];

				i++; j--;

				result.x[i] = trans1.x[j];
				result.y[i] = trans1.y[j];
				result.z[i] = trans1.z[j];

				i++; j++;

			}

			result.x[lim - 3] = trans.x[trans.col - 2];
			result.y[lim - 3] = trans.y[trans.col - 2];
			result.z[lim - 3] = trans.z[trans.col - 2];

			result.x[lim - 2] = trans1.x[trans.col - 2];
			result.y[lim - 2] = trans1.y[trans.col - 2];
			result.z[lim - 2] = trans1.z[trans.col - 2];

			result.x[lim - 1] = trans.x[trans.col - 1];
			result.y[lim - 1] = trans.y[trans.col - 1];
			result.z[lim - 1] = trans.z[trans.col - 1];


			trans = mx_rotate(trans,td_axis,step);
			trans1 = mx_rotate(trans1,td_axis,step);


			result.col = lim;


			//mx_print(trans);
		}
	//printf("result.col:%d\n",result.col);
//mx_print(result);
//		mx_export(result,color);
	//	printf("ok\n");
		mx = mx_addmatrix(result,mx);

		return mx;
	}else{
		printf("Error: mx_addsphere, matrix type not supported\n");
	}
}

struct Matrix mx_addpoly(struct Matrix mx){

}


struct Matrix draw_poly(struct Matrix mx){
	return mx;
}

struct Matrix mx_addtorus(struct Matrix mx, double x, double y, double z, double r, double d){
	if(mx.type == 'a'){
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
		//	printf("t: %printf("hi\n");f\n",t);
		}

		result = mx_transform(result,x,y,z);
		mx = mx_addmatrix(result,mx);


		mx_free(result);
		mx_free(trans);

		return mx;
	}else if(mx.type == 'c'){
					double t = M_PI / 2;
					double step = M_PI * td_step;

					struct Matrix trans;
					struct Matrix trans1;
					struct Matrix result;

					trans = mx_init(trans,0);
					trans1 = mx_init(trans1,0);
					result = mx_init_p(result,0);

					double xx;
					double yy;
					//t += t_step * (2 * M_PI);


					while(t <=  2 * M_PI){
						xx = r * cos(t) + d;
						yy = r * sin(t);
						trans = mx_addpoint(trans,xx,yy,0);
						trans1 = mx_addpoint(trans1,xx,yy,0);
						t = t + t_step * (M_PI);
						printf("t:%f\n",t);
					}

					trans1 = mx_rotate(trans1,td_axis,step);
					int i;

					//mx_print(trans);
					//mx_print(trans1);

					trans1 = mx_rotate(trans1,0,0.5);
					trans = mx_rotate(trans,0,0.5);

					db_export(trans);
					db_export(trans1);
					return mx;




					for(t = 0; t < 2 * M_PI ; t += td_step){
						int lim = result.col + (trans.col - 2) * 6;

						result.x = realloc(result.x,lim * sizeof(double));
						result.y = realloc(result.y,lim * sizeof(double));
						result.z = realloc(result.z,lim * sizeof(double));

						int i,j;
						i = result.col;
						j = 0;

						//printf("hi!\n");
						/* first polygon */

						while(i < lim){
							result.x[i] = trans.x[j];
							result.y[i] = trans.y[j];
							result.z[i] = trans.z[j];

							i++;

							result.x[i] = trans1.x[j];
							result.y[i] = trans1.y[j];
							result.z[i] = trans1.z[j];

							i++; j++;

							result.x[i] = trans.x[j];
							result.y[i] = trans.y[j];
							result.z[i] = trans.z[j];

							i++;

							result.x[i] = trans.x[j];
							result.y[i] = trans.y[j];
							result.z[i] = trans.z[j];

							i++;

							result.x[i] = trans1.x[j];
							result.y[i] = trans1.y[j];
							result.z[i] = trans1.z[j];

							i++; j--;

							result.x[i] = trans1.x[j];
							result.y[i] = trans1.y[j];
							result.z[i] = trans1.z[j];

							i++; j++;

						}

						trans = mx_rotate(trans,td_axis,step);
						trans1 = mx_rotate(trans1,td_axis,step);


						result.col = lim;


						//mx_print(trans);
					}
				//printf("result.col:%d\n",result.col);
			//mx_print(result);
			//		mx_export(result,color);
				//	printf("ok\n");
					mx = mx_addmatrix(result,mx);

					return mx;

	}else{
		printf("Error: mx_addtorus, matrix type not supported\n");

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
