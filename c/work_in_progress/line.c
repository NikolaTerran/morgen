#include "engine.h"

/* random snippet
I = AKa + IpKl(N*L) + IpKs[(2N(N*L)-L)*V]
	*Specular Reflection is supposed to fade off quickly

*/
int global_db;
int seed;
int * global_x;
int * global_y;
int * global_z;

int * global_xx;
int * global_yy;
int * global_zz;

int global_index;
int global_res;
int global_color[3];
int global_size;

int * x_line;  // <--this is global
int * y_line;
int * z_line;
int * x_line1;
int * y_line1;
int * z_line1;
int * x_line2;
int * y_line2;
int * z_line2;
//int *
//int * 1;
//int * 2;
//int global_major_axis_counter;

void int_print(int * x, int res){
	int i;
	for(i = 0;i < res; i++){
		printf("int:%d\n");
	}
}

struct Matrix mx_addedge(struct Matrix mx, double a, double b, double c,
												 double d, double e, double f){
	/*if(mx.type != 'b'){
		printf("Err: mx_addedge, incompatible matrix type, force quitting the program\n");
		exit(1);
	}*/

	mx.edge_num += 1;
	mx.col += 2;

	mx.x = realloc(mx.x,mx.col * sizeof(double));
	mx.y = realloc(mx.y,mx.col * sizeof(double));
	mx.z = realloc(mx.z,mx.col * sizeof(double));
 	//mx.one = realloc(mx.one,mx.col * sizeof(double));

 	mx.x[mx.col - 2] = a;
 	mx.y[mx.col - 2] = b;
 	mx.z[mx.col - 2] = c;
 	//mx.one[mx.col - 2] = 1;
 	mx.x[mx.col - 1] = d;
 	mx.y[mx.col - 1] = e;
 	mx.z[mx.col - 1] = f;
 	//mx.one[mx.col - 1] = 1;

 	return mx;
}

void poly_lines(struct Matrix mx){
	int i = 0;
	int j = 0;
	int a = 0;

	while(i < mx.col){
		//printf("poly_lines: vx:%f ,vy:%f ,vz:%f\n",mx.vx[a],mx.vy[a],mx.vz[a]);
		if(dot_pdt(mx.vx[a],mx.vy[a],mx.vz[a]) >= 0){
			//printf("pos\n");
			global_x = realloc(global_x, 3 * (j + 2) * sizeof(int));
			global_y = realloc(global_y, 3 * (j + 2) * sizeof(int));
			global_x[j] = round(mx.x[i]);
			global_y[j] = round(mx.y[i]);
			j++; i++;
			global_x[j] = round(mx.x[i]);
			global_y[j] = round(mx.y[i]);
			j++;
			global_x[j] = round(mx.x[i]);
			global_y[j] = round(mx.y[i]);
			j++; i++;
			global_x[j] = round(mx.x[i]);
			global_y[j] = round(mx.y[i]);
			j++;
			global_x[j] = round(mx.x[i]);
			global_y[j] = round(mx.y[i]);
			j++; i -= 2;
			global_x[j] = round(mx.x[i]);
			global_y[j] = round(mx.y[i]);
			j++; i += 3; a++;
			global_size += 3;
			//printf("a:%d\n",a);
		}else{
			//printf("neg\n");
			i += 3;
			a++;
		}
	}

}

void * drawLine_helper(void * arg){
	int index = (void *) arg;
	int index2 = index + 1;

	while(1){
			if(index >= global_res){
				break;
			}
		 //printf("index2:%d,,,index:%d\n",index2,index);
		 /*
		 if(global_y[index] > Y_MAX || global_y[index] <= Y_MIN || global_x[index] >= X_MAX || global_x[index] < X_MIN ||
		    global_y[index2] > Y_MAX || global_y[index2] <= Y_MIN || global_x[index2] >= X_MAX || global_x[index2] < X_MIN){
		 }else{*/
				 int i, dx, dy, dz, abx, aby, abz, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
				 if("assignment"){
				 dx = global_x[index2] - global_x[index];
				 dy = global_y[index2] - global_y[index];
				 dz = global_z[index2] - global_z[index];
				 x_inc = (dx < 0) ? -1 : 1;
				 abx = abs(dx);
				 y_inc = (dy < 0) ? -1 : 1;
				 aby = abs(dy);
				 z_inc = (dz < 0) ? -1 : 1;
				 abz = abs(dz);
				 dx2 = abx * 2;
				 dy2 = aby * 2;
				 dz2 = abz * 2;
			 }
				 if ((abx >= aby) && (abx >= abz)) {
						 canvas_set_s(global_x[index],global_y[index],global_z[index],global_color);
						 err_1 = dy2 - abx;
						 err_2 = dz2 - abx;
						 for (i = 0; i < abx; i++) {

								 if (err_1 > 0) {
										 global_y[index] += y_inc;
										 err_1 -= dx2;
								 }
								 if (err_2 > 0) {
										 global_z[index] += z_inc;
										 err_2 -= dx2;
								 }
								 err_1 += dy2;
								 err_2 += dz2;
								 global_x[index] += x_inc;
								 canvas_set_s(global_x[index],global_y[index],global_z[index],global_color);
						 }
				 } else if ((aby >= abx) && (aby >= abz)) {
					 canvas_set_s(global_x[index],global_y[index],global_z[index],global_color);
						 err_1 = dx2 - aby;
						 err_2 = dz2 - aby;
						 for (i = 0; i < aby; i++) {

								 if (err_1 > 0) {
										 global_x[index] += x_inc;
										 err_1 -= dy2;
								 }
								 if (err_2 > 0) {
										 global_z[index] += z_inc;
										 err_2 -= dy2;
								 }
								 err_1 += dx2;
								 err_2 += dz2;
								 global_y[index] += y_inc;
								 canvas_set_s(global_x[index],global_y[index],global_z[index],global_color);
						 }
				 } else {
					 canvas_set_s(global_x[index],global_y[index],global_z[index],global_color);
						 err_1 = dy2 - abz;
						 err_2 = dx2 - abz;
						 for (i = 0; i < abz; i++) {

								 if (err_1 > 0) {
										 global_y[index] += y_inc;
										 err_1 -= dz2;
								 }
								 if (err_2 > 0) {
										 global_x[index] += x_inc;
										 err_2 -= dz2;
								 }
								 err_1 += dy2;
								 err_2 += dx2;
								 global_z[index] += z_inc;
								 canvas_set_s(global_x[index],global_y[index],global_z[index],global_color);
						 }
				 }
				 index += 2 * THREAD;
		     index2 += 2 * THREAD;
	 		//}
	}
	pthread_exit(NULL);
}

void drawLine(struct Matrix mx, int color[3]){
 	if(mx.type == 'b'){

			//

			pthread_t thread_id[THREAD];
		 	int index[THREAD];

			global_x = malloc(mx.col * sizeof(int));
			global_y = malloc(mx.col * sizeof(int));
			global_z = malloc(mx.col * sizeof(int));

		 	global_x = mx_toint(mx,global_x,1);
		 	global_y = mx_toint(mx,global_y,2);
			global_z = mx_toint(mx,global_z,3);


		 	global_color[0] = color[0];
		 	global_color[1] = color[1];
		 	global_color[2] = color[2];


			global_res = 2 * mx.edge_num;

			int i;

			// for(i = 0; i < mx.col; i+=2){
			// 	printf("x:%d ; y:%d ; x1:%d ; y1:%d\n",global_x[i],global_y[i],global_x[i+1],global_y[i+1]);
			// }

		 	for(i = 0; i < THREAD; i++){
				index[i] = i * 2;
				pthread_create(&thread_id[i], NULL, drawLine_helper, (void*)index[i]);
			}

			for(i = 0; i < THREAD; i++){
				pthread_join(thread_id[i], NULL);
			}


			free(global_x);
			free(global_y);
			free(global_z);

	}else if(mx.type == 'c'){
			pthread_t thread_id[THREAD];
		 	int index[THREAD];
		 	//global_x = mx_toint(mx,global_x,1);
		 	//global_y = mx_toint(mx,global_y,2);
			global_size = 0;
			poly_lines(mx);

		 	global_color[0] = color[0];
		 	global_color[1] = color[1];
		 	global_color[2] = color[2];

			global_res =  2 * global_size;

			int i;

			// for(i = 0; i < mx.col; i+=2){
			// 	printf("x:%d ; y:%d ; x1:%d ; y1:%d\n",global_x[i],global_y[i],global_x[i+1],global_y[i+1]);
			// }

		 	for(i = 0; i < THREAD; i++){
				index[i] = i * 2;
				pthread_create(&thread_id[i], NULL, drawLine_helper, (void*)index[i]);
			}
			for(i = 0; i < THREAD; i++){
				pthread_join(thread_id[i], NULL);
			}


			//free(global_x);
			//free(global_y);
	}else{
	 		printf("Error: drawLine, only edge matrix was supported, force exit.\n");
 		exit(1);
	}
}

void drawLine_mod(int color[3]){
	pthread_t thread_id[THREAD];
	int index[THREAD];
	//global_size = 0;
	//poly_lines(mx);
	global_color[0] = color[0];
	global_color[1] = color[1];
	global_color[2] = color[2];

	global_res = global_size;
	int i;

	for(i = 0; i < THREAD; i++){
		index[i] = i * 2;
		pthread_create(&thread_id[i], NULL, drawLine_helper, (void*)index[i]);
	}
	for(i = 0; i < THREAD; i++){
		pthread_join(thread_id[i], NULL);
	}

	global_size = 0;
	free(global_x);
	free(global_y);
	free(global_z);
}

int* sys_random(int * buffer, int size){

	buffer = malloc(sizeof(int) * size);
	//printf("gotit!\n");
	//printf("initiating...this may take several minites\n");
	FILE* file = fopen("/dev/urandom", "r");
	//printf("gotit!\n");
	fread(buffer, sizeof(int), size ,file);
	//printf("gotit!\n");
	fclose(file);

	return buffer;
}

void purification(){
	int counter = 0;
	int odd = 0;
 	int int_size = 1;
	int index = 0;
	int index1 = 0;
	int index2 = 0;
	int size = 0;

	int *x = malloc(int_size * sizeof(int));
	int *y = malloc(int_size * sizeof(int));	//free(global_x);
	int *x1 = malloc(int_size * sizeof(int));
	int *y1 = malloc(int_size * sizeof(int));
	int *x2 = malloc(int_size * sizeof(int));
	int *y2 = malloc(int_size * sizeof(int));
	int *z = malloc(int_size * sizeof(int));
	int *z1 = malloc(int_size * sizeof(int));
	int *z2 = malloc(int_size * sizeof(int));

	global_x = malloc(sizeof(int));
	global_y = malloc(sizeof(int));
	global_z = malloc(sizeof(int));



  counter = 0;

	while(y_line[counter] != X_MAX){

		if(counter != 0 && y_line[counter] != y_line[counter - 1]){
			//printf("wf\n");
			y[index] = y_line[counter];
			x[index] = x_line[counter];
			z[index] = z_line[counter];
			int_size++;
			index++;
			x = realloc(x,int_size * sizeof(int));
			y = realloc(y,int_size * sizeof(int));
			z = realloc(z,int_size * sizeof(int));

		}else if(counter == 0){


			// printf("y:%d, x:%d\n",x_line[counter],y_line[counter]);

			y[index] = y_line[counter];
			x[index] = x_line[counter];
			z[index] = z_line[counter];
			int_size++;
			index++;

			x = realloc(x,int_size * sizeof(int));
			y = realloc(y,int_size * sizeof(int));
			z = realloc(z,int_size * sizeof(int));
		}




		if(y_line[counter+1]==X_MAX){

			//printf("this!\n");
			y[index] = y_line[counter];
			x[index] = x_line[counter];
			z[index] = z_line[counter];
			int_size++;
			index++;
			//printf("fasdsadaut!\n");
			x = realloc(x,int_size * sizeof(int));
			y = realloc(y,int_size * sizeof(int));
			z = realloc(z,int_size * sizeof(int));
			//printf("fasdsadaut!\n");
							if(y[index-2] == y[index-1]){

								y[index-2] = y[index-1];
								x[index-2] = x[index-1];
								index--;
							}
							//printf("fasdsadaut!\n");
		}

		counter++;
	}




	int_size = 1;
	counter = 0;


	while(y_line1[counter] != X_MAX){
		if(counter != 0 && y_line1[counter] != y_line1[counter - 1] ){
			y1[index1] = y_line1[counter];
			x1[index1] = x_line1[counter];
			z1[index1] = z_line1[counter];
			int_size++;
			index1++;
			x1 = realloc(x1,int_size * sizeof(int));
			y1 = realloc(y1,int_size * sizeof(int));
			z1 = realloc(z1,int_size * sizeof(int));
	//		printf("y:%d, x:%d\n",y[index - 1],x[index - 1]);
				}else if(counter == 0){
					// printf("wf\n");
					// printf("y:%d, x:%d\n",x_line[counter],y_line[counter]);
					y1[index1] = y_line1[counter];
					x1[index1] = x_line1[counter];
					z1[index1] = z_line1[counter];
					int_size++;
					index1++;
					x1 = realloc(x1,int_size * sizeof(int));
					y1 = realloc(y1,int_size * sizeof(int));
					z1 = realloc(z1,int_size * sizeof(int));
				}

				if(y_line1[counter+1]==X_MAX){
					y1[index1] = y_line1[counter];
					x1[index1] = x_line1[counter];
					z1[index1] = z_line1[counter];
					int_size++;
					index1++;
					x1 = realloc(x1,int_size * sizeof(int));
					y1 = realloc(y1,int_size * sizeof(int));
					z1 = realloc(z1,int_size * sizeof(int));
					if(y1[index1-2] == y1[index1-1]){
						//index--;
						//printf("x_index-2:%d, y_index-2:%d\n",x[index-2],y[index-2]);
						//printf("x_index-1:%d, y_index-1:%d\n",x[index-1],y[index-1]);
						y1[index1-2] = y1[index1-1];
						x1[index1-2] = x1[index1-1];
						index1--;
					}
				}

		counter++;
	}


	int_size = 1;
	counter = 0;


	while(y_line2[counter] != X_MAX){
		 if(index == index1){
		 	//printf("hahaha!\n");
			break;
		 }
		if(counter != 0 && y_line2[counter] != y_line2[counter - 1]){
			y2[index2] = y_line2[counter];
			x2[index2] = x_line2[counter];
			z2[index2] = z_line2[counter];
			int_size++;
			index2++;
			x2 = realloc(x2,int_size * sizeof(int));
			y2 = realloc(y2,int_size * sizeof(int));
			z2 = realloc(z2,int_size * sizeof(int));
	//		printf("y:%d, x:%d\n",y[index - 1],x[index - 1]);
			}else if(counter == 0){

				int check = 0;
				while(check < index1){
					//printf("y1[check]:%d  lin2%d\n",y1[check],y_line2[counter]);
					if(y1[check] == y_line2[counter]){
					//	printf("y2[counter]:%d\n",y_line2[counter]);
						while(y_line2[counter + 1] == y_line2[counter]){
							//printf("y2 counter+1:%d,,y2 counter:%d\n",y2[counter+1],y2[counter]);
							counter++;
						}
						counter++;
					//	printf("y2[counter]:%d\n",y_line2[counter]);
						break;
					}
					check++;
				}
				y2[index2] = y_line2[counter];
				x2[index2] = x_line2[counter];
				z2[index2] = z_line2[counter];
				int_size++;
				index2++;
				x2 = realloc(x2,int_size * sizeof(int));
				y2 = realloc(y2,int_size * sizeof(int));
				z2 = realloc(z2,int_size * sizeof(int));


				// printf("wf\n");
				// printf("y:%d, x:%d\n",x_line[counter],y_line[counter]);

			}

			if(y_line2[counter+1]==X_MAX){
				int check = 0;
				while(check < index1){
					//printf("y2[index2]:%d   y1:check:%d\n",y2[index2 -1],y1[check]);
					if(y1[check] == y2[index2 - 1]){
						index2--;
						break;
					}
					check++;
				}

			}

		counter++;
	}



if(global_db >= 123){
	printf("index:%d   index1:%d\n",index,index1);

	counter = 0;
		while(y_line[counter] != X_MAX){
			printf("x:%d , y:%d , z:%d\n",x_line[counter],y_line[counter],z_line[counter]);
			counter++;
		}
		printf("x:%d , y:%d , z:%d\n",x_line[counter],y_line[counter],z_line[counter]);
		counter = 0;
		while(y_line1[counter] != X_MAX){
			printf("x1:%d , y1:%d , z1:%d\n",x_line1[counter],y_line1[counter],z_line1[counter]);
			counter++;
		}
		printf("x1:%d , y1:%d , z1:%d\n",x_line1[counter],y_line1[counter],z_line1[counter]);
		counter = 0;
		while(y_line2[counter] != X_MAX){
			printf("x2:%d , y2:%d , z2:%d\n",x_line2[counter],y_line2[counter],z_line2[counter]);
			counter++;
		}
	printf("x2:%d , y2:%d , z2:%d\n",x_line2[counter],y_line2[counter],z_line2[counter]);
		printf("purged!\n");



	int i = 0;
		while(i < index){
			printf("x:%d , y:%d , z:%d\n",x[i],y[i],z[i]);
			i++;
		}
		i = 0;
		while(i < index1){
			printf("x1:%d , y1:%d , z1:%d\n",x1[i],y1[i],z1[i]);
			i++;
		}
printf("index2:%d\n",index2);
				i = 0;
				while(i < index2){
					printf("x2:%d , y2:%d , z2:%d\n",x2[i],y2[i],z2[i]);
					i++;
				}

	exit(0);
}




	int ok;

	ok = 0;
	int la = 0;
	int oh = 0;
	global_size = 0;
	counter = 0;



	while(ok < index){
		//printf("ok!:%d\n",ok);
		while(la < index1){
			if(y[ok] == y1[la]){
				global_size += 2;
				global_x = realloc(global_x,global_size * sizeof(int));
				global_y = realloc(global_y,global_size * sizeof(int));
				global_z = realloc(global_z,global_size * sizeof(int));
				global_x[counter] = x[ok];
				global_y[counter] = y[ok];
				global_z[counter] = z[ok];
				counter++;
				global_x[counter] = x1[la];
				global_y[counter] = y1[la];
				global_z[counter] = z1[la];
				counter++;
				la = 0;
				break;
			}
			la++;
		}
		if(la != 0){
			while(oh < index2){
				//printf("sawdad!\n");
				if(y[ok] == y2[oh]){
					global_size += 2;
					global_x = realloc(global_x,global_size * sizeof(int));
					global_y = realloc(global_y,global_size * sizeof(int));
					global_z = realloc(global_z,global_size * sizeof(int));
					global_x[counter] = x[ok];
					global_y[counter] = y[ok];
					global_z[counter] = z[ok];
					counter++;
					global_x[counter] = x2[oh];
					global_y[counter] = y2[oh];
					global_z[counter] = z2[oh];
					counter++;
					oh = 0;
					la = 0;

					break;
				}
				oh++;
			}
		}


		ok++;
	}

	free(x);
	free(x1);
	free(x2);
	free(y1);
	free(y2);
	free(y);
	free(z1);
	free(z2);
	free(z);


	global_db++;
	 //return size;
}



void scanLine(struct Matrix mx){
	global_db = 0;
	int top_y = Y_MIN;
	int mid_y = Y_MIN;
	int bot_y = Y_MAX;
	int top_x;
	int mid_x;
	int bot_x;
	int top_z;
	int mid_z;
	int bot_z;
	int size = 0;
	int dx;
	int dx1;
	int dx2;
	int dy;
	int dy1;
	int dy2;
	int dz;
	int dz1;
	int dz2;
	int x1;
	int y1;
	int z1;
	int a = 0;
	int i;
	int j;
  int abx, aby, abz, x_inc, y_inc, z_inc, err_1, err_2;

	//FILE* file = fopen("/dev/urandom", "w+");
	for(i = 0; i < mx.col; i += 3){

		//printf("jjjjjjjjjjjjj:%d\n",j);
		int * buffer;
		//while(){
		buffer = sys_random(buffer,3);
		//}

		buffer[0] = abs(buffer[0]  % 255);
		buffer[1] = abs(buffer[1]  % 255);
		buffer[2] = abs(buffer[2]  % 255);

		//printf("dddddddddddot:%d\n",dot_pdt(mx.vx[a],mx.vy[a],mx.vz[a]));
		if(dot_pdt(mx.vx[a],mx.vy[a],mx.vz[a]) >= 0){

			if("get coord"){
			if(top_y < round(mx.y[i])){
				top_y = round(mx.y[i]);
				top_x = round(mx.x[i]);
				top_z = round(mx.z[i]);}
			if(top_y < round(mx.y[i + 1])){
				top_y = round(mx.y[i + 1]);
				top_x = round(mx.x[i + 1]);
				top_z = round(mx.z[i + 1]);}
			if(top_y < round(mx.y[i + 2])){
				top_y = round(mx.y[i + 2]);
				top_x = round(mx.x[i + 2]);
				top_z = round(mx.x[i + 2]);}
			if(bot_y > round(mx.y[i])){
				bot_y = round(mx.y[i]);
				bot_x = round(mx.x[i]);
				bot_z = round(mx.z[i]);}
			if(bot_y > round(mx.y[i + 1])){
				//printf("?????\n");
				bot_y = round(mx.y[i + 1]);
				bot_x = round(mx.x[i + 1]);
				bot_z = round(mx.z[i + 1]);}
			if(bot_y > round(mx.y[i + 2])){
				//printf("lololoasdsad\n");
				//printf("round:mx.y:%f\n",mx.y[i+2]);
				bot_y = round(mx.y[i + 2]);
				bot_x = round(mx.x[i + 2]);
			bot_z = round(mx.z[i + 2]);}
				//printf("bbbbbbot_y:%d\n",bot_y);
			if(round(mx.y[i]) != bot_y && round(mx.y[i]) != top_y){
				mid_y = round(mx.y[i]);
				mid_x = round(mx.x[i]);
			mid_z = round(mx.z[i]);}
			else if(round(mx.y[i + 1]) != bot_y && round(mx.y[i + 1]) != top_y){
				mid_y = round(mx.y[i + 1]);
				mid_x = round(mx.x[i + 1]);
			mid_z = round(mx.z[i + 1]);}
			else if(round(mx.y[i + 2]) != bot_y && round(mx.y[i + 2]) != top_y){
				mid_y = round(mx.y[i + 2]);
				mid_x = round(mx.x[i + 2]);
			mid_z = round(mx.z[i + 2]);}
				else if(round(mx.x[i]) != bot_x && round(mx.x[i]) != top_x){
					mid_y = round(mx.y[i]);
					mid_x = round(mx.x[i]);
				mid_z = round(mx.z[i]);}
					else if(round(mx.x[i + 1]) != bot_x && round(mx.x[i + 1]) != top_x){
						mid_y = round(mx.y[i + 1]);
						mid_x = round(mx.x[i + 1]);
					mid_z = round(mx.z[i + 1]);}
						else if(round(mx.x[i + 2]) != bot_x && round(mx.x[i + 2]) != top_x){
							mid_y = round(mx.y[i + 2]);
							mid_x = round(mx.x[i + 2]);
						mid_z = round(mx.z[i + 2]);}
						else if(round(mx.z[i]) != bot_z && round(mx.z[i]) != top_z){
							mid_y = round(mx.y[i ]);
							mid_x = round(mx.x[i ]);
						mid_z = round(mx.z[i ]);}
						else if(round(mx.z[i + 1]) != bot_z && round(mx.z[i + 1]) != top_z){
							mid_y = round(mx.y[i + 1]);
							mid_x = round(mx.x[i + 1]);
						mid_z = round(mx.z[i + 1]);}
						else if(round(mx.z[i + 2]) != bot_z && round(mx.z[i + 2]) != top_z){
							mid_y = round(mx.y[i + 2]);
							mid_x = round(mx.x[i + 2]);
						mid_z = round(mx.z[i + 2]);}
		}

			x_line = malloc(sizeof(int));
			y_line = malloc(sizeof(int));
			z_line = malloc(sizeof(int));
			if("assignment"){
				dx = top_x - bot_x;
				dy = top_y - bot_y;
				dz = top_z - bot_z;
				x_inc = (dx < 0) ? -1 : 1;
				abx = abs(dx);
				y_inc = (dy < 0) ? -1 : 1;
				aby = abs(dy);
				z_inc = (dz < 0) ? -1 : 1;
				abz = abs(dz);
				dx2 = abx * 2;
				dy2 = aby * 2;
				dz2 = abz * 2;
				x1 = bot_x;
				y1 = bot_y;
				z1 = bot_z;

			}
			if ((abx >= aby) && (abx >= abz)) {
					x_line[0] = x1;
					y_line[0] = y1;
					z_line[0] = z1;


					//canvas_set_s(global_x[index],global_y[index],global_z[index],global_color);
					err_1 = dy2 - abx;
					err_2 = dz2 - abx;
					for (j = 0; j < abx; j++) {
							x_line = realloc(x_line,(j + 2) * sizeof(int));
							y_line = realloc(y_line,(j + 2) * sizeof(int));
							z_line = realloc(z_line,(j + 2) * sizeof(int));
							if (err_1 > 0) {
									y1 += y_inc;
									err_1 -= dx2;
							}
							if (err_2 > 0) {
									z1 += z_inc;
									err_2 -= dx2;
							}
							err_1 += dy2;
							err_2 += dz2;
							x1 += x_inc;
							x_line[j + 1] = x1;
							y_line[j + 1] = y1;
							z_line[j + 1] = z1;
					}
					x_line[abx] = X_MAX;
					y_line[abx] = X_MAX;
					z_line[abx] = X_MAX;
			} else if ((aby >= abx) && (aby >= abz)) {
					x_line[0] = x1;
					y_line[0] = y1;
					z_line[0] = z1;
					err_1 = dx2 - aby;
					err_2 = dz2 - aby;
					for (j = 0; j < aby; j++) {
							x_line = realloc(x_line,(j + 2) * sizeof(int));
							y_line = realloc(y_line,(j + 2) * sizeof(int));
							z_line = realloc(z_line,(j + 2) * sizeof(int));
							if (err_1 > 0) {
									x1 += x_inc;
									err_1 -= dy2;
							}
							if (err_2 > 0) {
									z1 += z_inc;
									err_2 -= dy2;
							}
							err_1 += dx2;
							err_2 += dz2;
							y1 += y_inc;
							x_line[j + 1] = x1;
							y_line[j + 1] = y1;
							z_line[j + 1] = z1;
					}
					x_line[aby] = X_MAX;
					y_line[aby] = X_MAX;
					z_line[aby] = X_MAX;
			} else {
				x_line[0] = x1;
				y_line[0] = y1;
				z_line[0] = z1;

					err_1 = dy2 - abz;
					err_2 = dx2 - abz;
					for (j = 0; j < abz; j++) {
						x_line = realloc(x_line,(j + 2) * sizeof(int));
						y_line = realloc(y_line,(j + 2) * sizeof(int));
						z_line = realloc(z_line,(j + 2) * sizeof(int));
							if (err_1 > 0) {
									y1 += y_inc;
									err_1 -= dz2;
							}
							if (err_2 > 0) {
									x1 += x_inc;
									err_2 -= dz2;
							}
							err_1 += dy2;
							err_2 += dx2;
							z1 += z_inc;
							x_line[j + 1] = x1;
							y_line[j + 1] = y1;
							z_line[j + 1] = z1;
					}
					x_line[abz] = X_MAX;
					y_line[abz] = X_MAX;
					z_line[abz] = X_MAX;
			}
			x_line1 = malloc(sizeof(int));
			y_line1 = malloc(sizeof(int));
			z_line1 = malloc(sizeof(int));

			if("assignment"){
				dx = top_x - mid_x;
				dy = top_y - mid_y;
				dz = top_z - mid_z;
				x_inc = (dx < 0) ? -1 : 1;
				abx = abs(dx);
				y_inc = (dy < 0) ? -1 : 1;
				aby = abs(dy);
				z_inc = (dz < 0) ? -1 : 1;
				abz = abs(dz);
				dx2 = abx * 2;
				dy2 = aby * 2;
				dz2 = abz * 2;
				x1 = mid_x;
				y1 = mid_y;
				z1 = mid_z;
			}
			if ((abx >= aby) && (abx >= abz)) {


					x_line1[0] = x1;
					y_line1[0] = y1;
					z_line1[0] = z1;
					//canvas_set_s(global_x[index],global_y[index],global_z[index],global_color);
					err_1 = dy2 - abx;
					err_2 = dz2 - abx;
					for (j = 0; j < abx; j++) {
							x_line1 = realloc(x_line1,(j + 2) * sizeof(int));
							y_line1 = realloc(y_line1,(j + 2) * sizeof(int));
							z_line1 = realloc(z_line1,(j + 2) * sizeof(int));
							if (err_1 > 0) {
									y1 += y_inc;
									err_1 -= dx2;
							}
							if (err_2 > 0) {
									z1 += z_inc;
									err_2 -= dx2;
							}
							err_1 += dy2;
							err_2 += dz2;
							x1 += x_inc;
							x_line1[j + 1] = x1;
							y_line1[j + 1] = y1;
							z_line1[j + 1] = z1;
					}
					x_line1[abx] = X_MAX;
					y_line1[abx] = X_MAX;
					z_line1[abx] = X_MAX;
			} else if ((aby >= abx) && (aby >= abz)) {
					x_line1[0] = x1;
					y_line1[0] = y1;
					z_line1[0] = z1;
					err_1 = dx2 - aby;
					err_2 = dz2 - aby;
					for (j = 0; j < aby; j++) {
							x_line1 = realloc(x_line1,(j + 2) * sizeof(int));
							y_line1 = realloc(y_line1,(j + 2) * sizeof(int));
							z_line1 = realloc(z_line1,(j + 2) * sizeof(int));
							if (err_1 > 0) {
									x1 += x_inc;
									err_1 -= dy2;
							}
							if (err_2 > 0) {
									z1 += z_inc;
									err_2 -= dy2;
							}
							err_1 += dx2;
							err_2 += dz2;
							y1 += y_inc;
							x_line1[j + 1] = x1;
							y_line1[j + 1] = y1;
							z_line1[j + 1] = z1;
					}
					x_line1[aby] = X_MAX;
					y_line1[aby] = X_MAX;
					z_line1[aby] = X_MAX;
			} else {
				x_line1[0] = x1;
				y_line1[0] = y1;
				z_line1[0] = z1;
					err_1 = dy2 - abz;
					err_2 = dx2 - abz;
					for (j = 0; j < abz; j++) {
						x_line1 = realloc(x_line1,(j + 2) * sizeof(int));
						y_line1 = realloc(y_line1,(j + 2) * sizeof(int));
						z_line1 = realloc(z_line1,(j + 2) * sizeof(int));
							if (err_1 > 0) {
									y1 += y_inc;
									err_1 -= dz2;
							}
							if (err_2 > 0) {
									x1 += x_inc;
									err_2 -= dz2;
							}
							err_1 += dy2;
							err_2 += dx2;
							z1 += z_inc;
							x_line1[j + 1] = x1;
							y_line1[j + 1] = y1;
							z_line1[j + 1] = z1;
					}
					x_line1[abz] = X_MAX;
					y_line1[abz] = X_MAX;
					z_line1[abz] = X_MAX;
			}

			x_line2 = malloc(sizeof(int));
			y_line2 = malloc(sizeof(int));
			z_line2 = malloc(sizeof(int));
			if("assignment"){
				dx = mid_x - bot_x;
				dy = mid_y - bot_y;
				dz = mid_z - bot_z;
				x_inc = (dx < 0) ? -1 : 1;
				abx = abs(dx);
				y_inc = (dy < 0) ? -1 : 1;
				aby = abs(dy);
				z_inc = (dz < 0) ? -1 : 1;
				abz = abs(dz);
				dx2 = abx * 2;
				dy2 = aby * 2;
				dz2 = abz * 2;
				x1 = bot_x;
				y1 = bot_y;
				z1 = bot_z;
			}
			if ((abx >= aby) && (abx >= abz)) {



					x_line2[0] = x1;
					y_line2[0] = y1;
					z_line2[0] = z1;
					//canvas_set_s(global_x[index],global_y[index],global_z[index],global_color);
					err_1 = dy2 - abx;
					err_2 = dz2 - abx;
					for (j = 0; j < abx; j++) {
							x_line2 = realloc(x_line2,(j + 2) * sizeof(int));
							y_line2 = realloc(y_line2,(j + 2) * sizeof(int));
							z_line2 = realloc(z_line2,(j + 2) * sizeof(int));
							if (err_1 > 0) {
									y1 += y_inc;
									err_1 -= dx2;
							}
							if (err_2 > 0) {
									z1 += z_inc;
									err_2 -= dx2;
							}
							err_1 += dy2;
							err_2 += dz2;
							x1 += x_inc;
							x_line2[j + 1] = x1;
							y_line2[j + 1] = y1;
							z_line2[j + 1] = z1;
					}
					x_line2[abx] = X_MAX;
					y_line2[abx] = X_MAX;
					z_line2[abx] = X_MAX;
			} else if ((aby >= abx) && (aby >= abz)) {
					x_line2[0] = x1;
					y_line2[0] = y1;
					z_line2[0] = z1;
					err_1 = dx2 - aby;
					err_2 = dz2 - aby;
					for (j = 0; j < aby; j++) {
							x_line2 = realloc(x_line2,(j + 2) * sizeof(int));
							y_line2 = realloc(y_line2,(j + 2) * sizeof(int));
							z_line2 = realloc(z_line2,(j + 2) * sizeof(int));
							if (err_1 > 0) {
									x1 += x_inc;
									err_1 -= dy2;
							}
							if (err_2 > 0) {
									z1 += z_inc;
									err_2 -= dy2;
							}
							err_1 += dx2;
							err_2 += dz2;
							y1 += y_inc;
							x_line2[j + 1] = x1;
							y_line2[j + 1] = y1;
							z_line2[j + 1] = z1;
					}
					x_line2[aby] = X_MAX;
					y_line2[aby] = X_MAX;
					z_line2[aby] = X_MAX;
			} else {
			//	printf("bot_y:%d\n",bot_y);
				x_line2[0] = x1;
				y_line2[0] = y1;
				z_line2[0] = z1;
					err_1 = dy2 - abz;
					err_2 = dx2 - abz;
					for (j = 0; j < abz; j++) {
						x_line2 = realloc(x_line2,(j + 2) * sizeof(int));
						y_line2 = realloc(y_line2,(j + 2) * sizeof(int));
						z_line2 = realloc(z_line2,(j + 2) * sizeof(int));
							if (err_1 > 0) {
									y1 += y_inc;
									err_1 -= dz2;
							}
							if (err_2 > 0) {
									x1 += x_inc;
									err_2 -= dz2;
							}
							err_1 += dy2;
							err_2 += dx2;
							z1 += z_inc;
							x_line2[j + 1] = x1;
							y_line2[j + 1] = y1;
							z_line2[j + 1] = z1;
					}
					x_line2[abz] = X_MAX;
					y_line2[abz] = X_MAX;
					z_line2[abz] = X_MAX;
			}
//

if(global_db >= 123){
printf("top_x:%d , mid_x:%d , bot_x:%d\n",top_x,mid_x,bot_x);
printf("top_y:%d , mid_y:%d , bot_y:%d\n",top_y,mid_y,bot_y);
printf("top_z:%d , mid_z:%d , bot_z:%d\n",top_z,mid_z,bot_z);
}

			purification();

			int color[3];
			color[0] = buffer[0];//buffer[0] % 255;
			color[1] = buffer[1];//buffer[1] % 255;
			color[2] = buffer[2];//buffer[2] % 255;

			drawLine_mod(color);

		 free(x_line);  // <--this is global
		 free(y_line);
		 free(z_line);
		 free(x_line1);
		 free(y_line1);
		 free(z_line1);
		 free(y_line2);
		 free(x_line2);
		 free(z_line2);

		 top_y = Y_MIN;
		 mid_y = Y_MIN;
		 bot_y = Y_MAX;
		}
		free(buffer);
		a++;
		//printf("j:%d\n",j);
	}

}


void drawLine_test(int x, int y, int z, int x1, int y1, int z1, int color[3]){
    int i, dx, dy, dz, abx, aby, abz, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
    dx = x1 - x;
    dy = y1 - y;
    dz = z1 - z;
    x_inc = (dx < 0) ? -1 : 1;
    abx = abs(dx);
    y_inc = (dy < 0) ? -1 : 1;
    aby = abs(dy);
    z_inc = (dz < 0) ? -1 : 1;
    abz = abs(dz);
    dx2 = abx * 2;
    dy2 = aby * 2;
    dz2 = abz * 2;
		global_x = malloc(2 * sizeof(int));
		global_y = malloc(2 * sizeof(int));
		global_z = malloc(2 * sizeof(int));
		global_x[0] = x;
		global_y[0] = y;
		global_z[0] = z;
		int index = 0;
    if ((abx >= aby) && (abx >= abz)) {
			  canvas_set_s(global_x[index],global_y[index],global_z[index],color);
        err_1 = dy2 - abx;
        err_2 = dz2 - abx;
        for (i = 0; i < abx; i++) {

            if (err_1 > 0) {
                global_y[index] += y_inc;
                err_1 -= dx2;
            }
            if (err_2 > 0) {
                global_z[index] += z_inc;
                err_2 -= dx2;
            }
            err_1 += dy2;
            err_2 += dz2;
            global_x[index] += x_inc;
						canvas_set_s(global_x[index],global_y[index],global_z[index],color);
        }
    } else if ((aby >= abx) && (aby >= abz)) {
			canvas_set_s(global_x[index],global_y[index],global_z[index],color);
        err_1 = dx2 - aby;
        err_2 = dz2 - aby;
        for (i = 0; i < aby; i++) {

            if (err_1 > 0) {
                global_x[index] += x_inc;
                err_1 -= dy2;
            }
            if (err_2 > 0) {
                global_z[index] += z_inc;
                err_2 -= dy2;
            }
            err_1 += dx2;
            err_2 += dz2;
            global_y[index] += y_inc;
						canvas_set_s(global_x[index],global_y[index],global_z[index],color);
        }
    } else {
			canvas_set_s(global_x[index],global_y[index],global_z[index],color);
        err_1 = dy2 - abz;
        err_2 = dx2 - abz;
        for (i = 0; i < abz; i++) {

            if (err_1 > 0) {
                global_y[index] += y_inc;
                err_1 -= dz2;
            }
            if (err_2 > 0) {
                global_x[index] += x_inc;
                err_2 -= dz2;
            }
            err_1 += dy2;
            err_2 += dx2;
            global_z[index] += z_inc;
						canvas_set_s(global_x[index],global_y[index],global_z[index],color);
        }
    }

}

/*
if("legacy"){
// struct Array DLMA(
//     struct Array arr,
//     int x,
//     int y,
//     int dx,
//     int dy,
//     int check,
//     char axis,
//     int color[3]){
//     // calculate some constants
//     int dx2 = dx * 2;
//     int dy2 = dy * 2;
//     int dy2Mindx2 = dy2 - dx2;

//     // calculate the starting error value
//     int Error = dy2 - dx;

//     // draw the first pixel
//     arr = arr_set(arr,x,y,color);

//     // loop across the major axis
//     if(axis == 'x'){
// 	    while (dx--)
// 	    {
// 	        // move on major axis and minor axis
// 	        if (Error > 0)
// 	        {
// 	            x++;
// 		    if(check == 0){
// 		            y++;
// 		    }else{
// 			y--;
// 		    }
// 	            Error += dy2Mindx2;
// 	        }
// 	        // move on major axis only
// 	        else
// 	        {
// 	            x++;
// 	            Error += dy2;
// 	        }

// 	        // draw the next pixel
// 	        arr = arr_set(arr,x,y,color);
// 	    }
// 	}else{
// 	    while (dx--)
// 	    {
// 	        // move on major axis and minor axis
// 	        if (Error > 0)
// 	        {
// 			if(check == 0){
// 	            x++;}else{x--;}
// 	            y++;
// 	            Error += dy2Mindx2;
// 	        }
// 	        // move on major axis only
// 	        else
// 	        {
// 	            y++;
// 	            Error += dy2;
// 	        }

// 	        // draw the next pixel
// 	        arr = arr_set(arr,x,y,color);
// 	    }
// 	}
// 	return arr;
// }


// // Specialized Line Drawing optimized for horizontal or vertical lines
// // X and Y are flipped for Y maxor axis lines, but the pixel writes are handled correctly due to
// // minor and major axis pixel movement
// struct Array DLSA(struct Array arr, int x, int y, int dx, char axis, int color[3]){
//     // draw the first pixel
//  	arr = arr_set(arr,x,y,color);
//     // loop across the major axis and draw the rest of the pixels


//     if(axis == 'x'){
// 	    while (dx--){
// 	    	x++;
//         	arr = arr_set(arr,x,y,color);
//     	}
//     }else{
// 	    while (dx--){
// 	    	y++;
//         	arr = arr_set(arr,x,y,color);
//     	}
//     }

//     return arr;
// }

// // Draw an arbitrary line.  Assumes start and end point are within valid range
// // pixels is a pointer to where the pixels you want to draw to start aka (0,0)
// // pixelStride is the number of unsigned ints to get from one row of pixels to the next.
// // Usually, that is the same as the width of the image you are drawing to, but sometimes is not.
// struct Array DL(struct Array arr, int x1, int y1, int x2, int y2, int color[3]){
//     // calculate our deltas
//     int dx = x2 - x1;
//     int dy = y2 - y1;


//     // if the X axis is the major axis
//     if (abs(dx) >= abs(dy)){
//         // if x2 < x1, flip the points to have fewer special cases
//         if (dx < 0){
//             dx *= -1;
//             dy *= -1;
//             int t = x1;
//             x1 = x2;
//             x2 = t;

//             t = y1;
//             y1 = y2;
//             y2 = t;
//         }

//         // determine special cases
//         if(dy > 0){
//             arr = DLMA(arr, x1,y1, dx, dy, 0,'x', color);
//         }
//         else if (dy < 0){
//          	arr = DLMA(arr, x1,y1, dx, -dy, 1,'x', color);
//         }
//         else{
//             arr = DLSA(arr,x1,y1,dx,'x', color);
//         }
//     }
//     // else the Y axis is the major axis
//     else
//     {
//         // if y2 < y1, flip the points to have fewer special cases
//         if (dy < 0)
//         {
//             dx *= -1;
//             dy *= -1;
//             int t = x1;
//             x1 = x2;
//             x2 = t;

//             t = y1;
//             y1 = y2;
//             y2 = t;
//         }

//         // get the address of the pixel at (x1,y1)

//         // determine special cases
//         if (dx > 0){
//          	  arr = DLMA(arr, x1,y1, dy, dx, 0,'y', color);
//         }else if (dx < 0){
//         	  arr = DLMA(arr, x1,y1, dy, -dx, 1,'y', color);
//         }else{
//               arr = DLSA(arr,x1,y1, dy,'y', color);
//         }
//     }

//     return arr;
// }



// /*
// struct Array drawLine(struct Array arr, struct Edge ed, int color[3]){
// 	int * x;
// 	int * y;
// 	int * x1;
// 	int * y1;
//
// 	x = ed_toint(ed,x,0,0);
// 	y = ed_toint(ed,y,1,0);
// 	x1 = ed_toint(ed,x1,0,1);
// 	y1 = ed_toint(ed,x1,1,1);
//
// 	int * d_x;
// 	int * d_y;
// 	int * d_x1;
// 	int * d_y1;
// 	int * d_r;
// 	int * d_g;
// 	int * d_b;
//
// 	int edge_num = ed.col/2;
//
// 	int edge_size = edge_num * sizeof(int);
// 	int size = (X_MAX - X_MIN) * (Y_MAX - Y_MIN) * sizeof(int);
//
//
//     gp_drawline<<<edge_num,1>>>(d_r, d_g, d_b,
// 							    d_x, d_y,
// 							    d_x1, d_y1,
// 							    color[0],color[1],color[2]);
//
//     return arr;
// }

}
*/
