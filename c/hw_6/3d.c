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
double cross_pdt(char cord, double x1, double y1, double z1, double x2, double y2, double z2){
	if(cord == 'x'){
		return y1 * z2 - z1 * y2;
	}else if(cord == 'y'){
		return z1 * x2 - x1 * z2;
	}else if(cord == 'z'){
		return x1 * y2 - y1 * x2;
	}else{
		printf("cross_pdt: what the hell?\n");
		exit(1);
	}

}

double dot_pdt(double x, double y, double z){
	//double ok = x * VIEW_X + y * VIEW_Y + z * VIEW_Z;
	//printf("ok:%f\n",ok);
	return x * VIEW_X + y * VIEW_Y + z * VIEW_Z;

}

void db_dot_pdt(double x, double y, double z){
	printf("db: dot_pdt: %f\n",x * VIEW_X + y * VIEW_Y + z * VIEW_Z);

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
	}
	else if(mx.type == 'c'){
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

		while(t <= 3 * M_PI / 2 + t_step){
			xx = r * cos(t);
			yy = r * sin(t);
			trans = mx_addpoint(trans,xx,yy,0);
			trans1 = mx_addpoint(trans1,xx,yy,0);
			t = t + t_step * ( M_PI);
		}

		trans1 = mx_rotate(trans1,td_axis,step);
		int i , j;
		int a;

		double vx1,vy1,vz1,vx2,vy2,vz2;

		for(t = 0; t < M_PI * 2; t += step){
			int lim = result.col + (trans.col - 2) * 6;
			int vlim = result.col / 3 + (trans.col - 2) * 2;



			result.x = realloc(result.x,lim * sizeof(double));
			result.y = realloc(result.y,lim * sizeof(double));
			result.z = realloc(result.z,lim * sizeof(double));

			result.vx = realloc(result.vx,vlim * sizeof(double));
			result.vy = realloc(result.vy,vlim * sizeof(double));
			result.vz = realloc(result.vz,vlim * sizeof(double));


			i = result.col;
			a = i / 3;
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

			vx1 = result.x[i - 1] - result.x[i - 3];
			vx2 = result.x[i - 2] - result.x[i - 3];
			vy1 = result.y[i - 1] - result.y[i - 3];
			vy2 = result.y[i - 2] - result.y[i - 3];
			vz1 = result.z[i - 1] - result.z[i - 3];
			vz2 = result.z[i - 2] - result.z[i - 3];

			result.vx[a] = cross_pdt('x',vx2,vy2,vz2,vx1,vy1,vz1);
			result.vy[a] = cross_pdt('y',vx2,vy2,vz2,vx1,vy1,vz1);
			result.vz[a] = cross_pdt('z',vx2,vy2,vz2,vx1,vy1,vz1);
		//	db_dot_pdt(result.vx[a],result.vy[a],result.vz[a]);

			a++;
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

				vx1 = result.x[i - 1] - result.x[i - 3];
				vx2 = result.x[i - 2] - result.x[i - 3];
				vy1 = result.y[i - 1] - result.y[i - 3];
				vy2 = result.y[i - 2] - result.y[i - 3];
				vz1 = result.z[i - 1] - result.z[i - 3];
				vz2 = result.z[i - 2] - result.z[i - 3];

				result.vx[a] = cross_pdt('x',vx1,vy1,vz1,vx2,vy2,vz2);
				result.vy[a] = cross_pdt('y',vx1,vy1,vz1,vx2,vy2,vz2);
				result.vz[a] = cross_pdt('z',vx1,vy1,vz1,vx2,vy2,vz2);
		//		db_dot_pdt(result.vx[a],result.vy[a],result.vz[a]);
				a++;

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

				vx1 = result.x[i - 1] - result.x[i - 3];
				vx2 = result.x[i - 2] - result.x[i - 3];
				vy1 = result.y[i - 1] - result.y[i - 3];
				vy2 = result.y[i - 2] - result.y[i - 3];
				vz1 = result.z[i - 1] - result.z[i - 3];
				vz2 = result.z[i - 2] - result.z[i - 3];

			result.vx[a] = cross_pdt('x',vx2,vy2,vz2,vx1,vy1,vz1);
			result.vy[a] = cross_pdt('y',vx2,vy2,vz2,vx1,vy1,vz1);
			result.vz[a] = cross_pdt('z',vx2,vy2,vz2,vx1,vy1,vz1);
	//db_dot_pdt(result.vx[a],result.vy[a],result.vz[a]);
				a++;

			//	printf("dot:%f\n",dot_pdt(result.vx[a],result.vy[a],result.vz[a]));
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

			vx1 = result.x[lim  - 1] - result.x[lim  - 3];
			vx2 = result.x[lim  - 2] - result.x[lim  - 3];
			vy1 = result.y[lim  - 1] - result.y[lim  - 3];
			vy2 = result.y[lim  - 2] - result.y[lim  - 3];
			vz1 = result.z[lim  - 1] - result.z[lim  - 3];
			vz2 = result.z[lim  - 2] - result.z[lim  - 3];

			 result.vx[vlim - 1] = cross_pdt('x',vx1,vy1,vz1,vx2,vy2,vz2);
			 result.vy[vlim - 1] = cross_pdt('y',vx1,vy1,vz1,vx2,vy2,vz2);
			 result.vz[vlim - 1] = cross_pdt('z',vx1,vy1,vz1,vx2,vy2,vz2);
		//	 db_dot_pdt(result.vx[vlim - 1],result.vy[vlim - 1],result.vz[vlim - 1]);
			trans = mx_rotate(trans,td_axis,step);
			trans1 = mx_rotate(trans1,td_axis,step);


			result.col = lim;


			//mx_print(trans);
		}


		result = mx_transform(result, x,y,z);
		mx = mx_addmatrix(result,mx);

		return mx;
	}
	else{
		printf("Error: mx_addsphere, matrix type not supported\n");
	}

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

	}
	else if(mx.type == 'c'){
					double t = 0;
					double step = M_PI * td_step;

					struct Matrix trans;
					struct Matrix trans1;
					struct Matrix result;

					trans = mx_init(trans,0);
					trans1 = mx_init(trans1,0);
					result = mx_init_p(result,0);

					double xx;
					double yy;
					//t += t_step * double vx1,vy1,vz1,vx2,vy2,vz2;(2 * M_PI);

					double step1 = t_step * M_PI;
					while(t <= 2 * M_PI +  2 * step1){
						xx = r * cos(t) + d;
						yy = r * sin(t);
						trans = mx_addpoint(trans,xx,yy,0);
						trans1 = mx_addpoint(trans1,xx,yy,0);
						t = t + step1;
					}

					double vx1,vy1,vz1,vx2,vy2,vz2;
					trans1 = mx_rotate(trans1,td_axis,step);

					//mx_print(trans);
					//mx_print(trans1);
					int lim,vlim;
					int i,j,a;

					for(t = 0; t < 2 * M_PI ; t += td_step){
						lim = result.col + (trans.col - 2) * 6;
						vlim = result.col / 3 + (trans.col - 2) * 2;

						result.x = realloc(result.x,lim * sizeof(double));
						result.y = realloc(result.y,lim * sizeof(double));
						result.z = realloc(result.z,lim * sizeof(double));

						result.vx = realloc(result.vx,vlim * sizeof(double));
						result.vy = realloc(result.vy,vlim * sizeof(double));
						result.vz = realloc(result.vz,vlim * sizeof(double));


						i = result.col;
						j = 0;
						a = i / 3;
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

							vx1 = result.x[i - 1] - result.x[i - 3];
							vx2 = result.x[i - 2] - result.x[i - 3];
							vy1 = result.y[i - 1] - result.y[i - 3];
							vy2 = result.y[i - 2] - result.y[i - 3];
							vz1 = result.z[i - 1] - result.z[i - 3];
							vz2 = result.z[i - 2] - result.z[i - 3];


							result.vx[a] = cross_pdt('x',vx2,vy2,vz2,vx1,vy1,vz1);
							result.vy[a] = cross_pdt('y',vx2,vy2,vz2,vx1,vy1,vz1);
							result.vz[a] = cross_pdt('z',vx2,vy2,vz2,vx1,vy1,vz1);

							a++;

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

							vx1 = result.x[i - 1] - result.x[i - 3];
							vx2 = result.x[i - 2] - result.x[i - 3];
							vy1 = result.y[i - 1] - result.y[i - 3];
							vy2 = result.y[i - 2] - result.y[i - 3];
							vz1 = result.z[i - 1] - result.z[i - 3];
							vz2 = result.z[i - 2] - result.z[i - 3];


						result.vx[a] = cross_pdt('x',vx1,vy1,vz1,vx2,vy2,vz2);
						result.vy[a] = cross_pdt('y',vx1,vy1,vz1,vx2,vy2,vz2);
						result.vz[a] = cross_pdt('z',vx1,vy1,vz1,vx2,vy2,vz2);
						  a++;

						}

						trans = mx_rotate(trans,td_axis,step);
						trans1 = mx_rotate(trans1,td_axis,step);



						result.col = lim;

						//result = mx_rotate(result,0,0.5);
						//db_export(result);
						//return mx;

						//mx_print(trans);
					}

					result = mx_transform(result,x,y,z);
				//printf("result.col:%d\n",result.col);
			//mx_print(result);
			//		mx_export(result,color);
				//	printf("ok\n");
					mx = mx_addmatrix(result,mx);

					return mx;

	}
	else{
		printf("Error: mx_addtorus, matrix type not supported\n");

	}
}

struct Matrix mx_addbox(struct Matrix mx, double x1, double y1, double z1,
						   				                    double h, double l, double d){
	if(mx.type == 'c'){

		int i,j,a;
		struct Matrix result;
		result = mx_init_p(result,36);

		int set[108];

//1
		set[0] = x1;
		set[1] = y1;
		set[2] = z1;

		set[3] = x1 + l;
		set[4] = y1;
		set[5] = z1;

		set[6] = x1;
		set[7] = y1 + h;
		set[8] = z1;
//1

//2
		set[9] = x1;
		set[10] = y1 + h;
		set[11] = z1;

		set[12] = x1 + l;
		set[13] = y1;
		set[14] = z1;

		set[15] = x1 + l;
		set[16] = y1 + h;
		set[17] = z1;
//2

//3
		set[18] = x1;
		set[19] = y1;
		set[20] = z1;

		set[21] = x1;
		set[22] = y1 + h;
		set[23] = z1 + d;

		set[24] = x1;
		set[25] = y1;
		set[26] = z1 + d;
//3

//4
		set[27] = x1;
		set[28] = y1;
		set[29] = z1;

		set[30] = x1;
		set[31] = y1 + h;
		set[32] = z1;

		set[33] = x1;
		set[34] = y1 + h;
		set[35] = z1 + d;
//4

//5
		set[36] = x1;
		set[37] = y1;
		set[38] = z1;

		set[39] = x1;
		set[40] = y1;
		set[41] = z1 + d;

		set[42] = x1 + l;
		set[43] = y1;
		set[44] = z1 + d;
//5

//6
		set[45] = x1;
		set[46] = y1;
		set[47] = z1;

		set[48] = x1 + l;
		set[49] = y1;
		set[50] = z1 + d;

		set[51] = x1 + l;
		set[52] = y1;
		set[53] = z1;
//6

//7
		set[54] = x1;
		set[55] = y1 + h;
		set[56] = z1;

		set[57] = x1 + l;
		set[58] = y1 + h;
		set[59] = z1;

		set[60] = x1;
		set[61] = y1 + h;
		set[62] = z1 + d;
//7

//8
		set[63] = x1;
		set[64] = y1 + h;
		set[65] = z1 + d;

		set[66] = x1 + l;
		set[67] = y1 + h;
		set[68] = z1;

		set[69] = x1 + l;
		set[70] = y1 + h;
		set[71] = z1 + d;
//8

//9
		set[72] = x1 + l;
		set[73] = y1;
		set[74] = z1;

		set[75] = x1 + l;
		set[76] = y1;
		set[77] = z1 + d;

		set[78] = x1 + l;
		set[79] = y1 + h;
		set[80] = z1;
//9

//10
		set[81] = x1 + l;
		set[82] = y1 + h;
		set[83] = z1;

		set[84] = x1 + l;
		set[85] = y1;
		set[86] = z1 + d;

		set[87] = x1 + l;
		set[88] = y1 + h;
		set[89] = z1 + d;
//10

//11
		set[90] = x1 + l;
		set[91] = y1;
		set[92] = z1 + d;

		set[93] = x1;
		set[94] = y1;
		set[95] = z1 + d;

		set[96] = x1 + l;
		set[97] = y1 + h;
		set[98] = z1 + d;
//11

//12
		set[99] = x1 + l;
		set[100] = y1 + h;
		set[101] = z1 + d;

		set[102] = x1;
		set[103] = y1;
		set[104] = z1 + d;

		set[105] = x1;
		set[106] = y1 + h;
		set[107] = z1 + d;
//6

		double vx1,vy1,vz1,vx2,vy2,vz2;

		j = 0;
		a = 0;

		//printf("mx.col:%d\n",result.col);

		for(i = 0; i < 36; i++){

			result.x[i] = set[j];
			result.y[i] = set[j + 1];
			result.z[i] = set[j + 2];

			i++;  j += 3;

			result.x[i] = set[j];
			result.y[i] = set[j + 1];
			result.z[i] = set[j + 2];

			i++; 	j += 3;

			result.x[i] = set[j];
			result.y[i] = set[j + 1];
			result.z[i] = set[j + 2];

			//i++;
				j += 3;
		//	printf("i:%d\n",i);
			vx1 = result.x[i] - result.x[i - 2];
			vx2 = result.x[i - 1] - result.x[i - 2];
			vy1 = result.y[i] - result.y[i - 2];
			vy2 = result.y[i - 1] - result.y[i - 2];
			vz1 = result.z[i] - result.z[i - 2];
			vz2 = result.z[i - 1] - result.z[i - 2];

			result.vx[a] = cross_pdt('x',vx1,vy1,vz1,vx2,vy2,vz2);
			result.vy[a] = cross_pdt('y',vx1,vy1,vz1,vx2,vy2,vz2);
			result.vz[a] = cross_pdt('z',vx1,vy1,vz1,vx2,vy2,vz2);
			a++;
		//	i--;

		}

		//printf("??\n");
		mx = mx_addmatrix(result,mx);

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
