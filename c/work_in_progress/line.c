#include "engine.h"

/* random snippet
I = AKa + IpKl(N*L) + IpKs[(2N(N*L)-L)*V]
	*Specular Reflection is supposed to fade off quickly

*/

int seed;
int * global_x;
int * global_y;
int * global_z;
int * global_xx;
int * global_yy;
int global_index;
int global_res;
int global_color[3];
int global_size;

int * x_line;  // <--this is global
int * y_line;
int * x_line1;
int * y_line1;
int * x_line2;
int * y_line2;
//int * ;
//int * 1;
//int * 2;
//int global_major_axis_counter;

void int_print(int * x, int res){
	int i;
	for(i = 0;i < res; i++){
		printf("int:%d\n");
	}
}

struct Matrix mx_addedge(struct Matrix mx, double a, double b, double c, double d, double e, double f){
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

void DLMA(int index,int dx,int dy,int axis,int check){
    // calculate some constants
		int dx2 = dx * 2;
		int dy2 = dy * 2;
		int dy2Mindx2 = dy2 - dx2;

 		int index2 = index + 1;
    // calculate the starting error value
    int Error = dy2 - dx;
    // draw the first pixel
 		canvas_set_s(global_x[index], global_y[index], global_color);
    // loop across the major axis
    //0 is x, else is y
    if(axis == 0){
	    while (dx--){
	        // move on major axis and minor axis
					if(global_y[index] > Y_MAX || global_y[index] <= Y_MIN || global_x[index] >= X_MAX || global_x[index] < X_MIN){
						printf("out of bound\n");
						break;
					}

	        if (Error > 0){

					    if(check == 0){
					        global_y[index]++;
					    }else{
							    global_y[index]--;
					    }
	            Error += dy2Mindx2;
	        }
	        // move on major axis only
	        else{
	            Error += dy2;
	        }

					global_x[index]++;
	        // draw the next pixel


	        canvas_set_s(global_x[index], global_y[index], global_color);
	    }
	}else{
	    while(dx--){
				if(global_y[index] > Y_MAX || global_y[index] <= Y_MIN || global_x[index] >= X_MAX || global_x[index] < X_MIN){
					printf("out of bound\n");
					break;
				}
	        // move on major axis and minor axis
	        if (Error > 0){
						if(check == 0){
		          global_x[index]++;
		        }else{
		        	global_x[index]--;
		        }
		          Error += dy2Mindx2;
		      }
	        // move on major axis only
	        else{
	            Error += dy2;
	        }

					global_y[index]++;
	        // draw the next pixel
	        canvas_set_s(global_x[index], global_y[index], global_color);
	    }
	}
}

void DLSA(int index,int dx,int axis){
    // draw the first pixel
 	canvas_set_s(global_x[index], global_y[index], global_color);
    // loop across the major axis and draw the rest of the pixels
    if(axis == 0){
	    while (dx--){
				if(global_y[index] > Y_MAX || global_y[index] <= Y_MIN || global_x[index] >= X_MAX || global_x[index] < X_MIN){
					printf("out of bound\n");
					break;
				}
	    	global_x[index]++;
        	canvas_set_s(global_x[index], global_y[index], global_color);
    	}
    }else{
	    while (dx--){
				if(global_y[index] > Y_MAX || global_y[index] <= Y_MIN || global_x[index] >= X_MAX || global_x[index] < X_MIN){
					printf("out of bound\n");
					break;
				}
	    	global_y[index]++;
        	canvas_set_s(global_x[index], global_y[index], global_color);
    	}
    }
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
	//exit(0);
}

void * drawLine_helper(void * arg){
	int index = (void *) arg;
	int index2 = index + 1;

	while(1){
        if(index >= global_res){
        	break;
        }
        int dx = global_x[index2] - global_x[index];
        int dy = global_y[index2] - global_y[index];
				int dz = global_z[index2] - global_z[index];
      // if the X axis is the major axis
				int max = abs(dx);
				if(abs(dy) > max){
					max = abs(dy);
				}
				if(abs(dz) > max){
					max = abs(dz);
				}

     	if(max == abs(dx)){
         // if x2 < x1, flip the points to have fewer special cases
    	   if (dx < 0){
           dx *= -1; dy *= -1; dz *= -1;
           int t = global_x[index];
           global_x[index] = global_x[index2]; global_x[index2] = t;
           t = global_y[index];
           global_y[index] = global_y[index2]; global_y[index2] = t;
					 t = global_z[index];
           global_z[index] = global_z[index2]; global_z[index2] = t;
         }
         // determine special cases
         if(dy > 0){
             DLMA(index,dx,dy,0,0);
         }else if (dy < 0){
          	 DLMA(index,dx,-dy,0,1);
         }else{
             DLSA(index,dx,0);
         }
     }
     // else the Y axis is the major axis
     else if(max == abs(dy)){
         // if y2 < y1, flip the points to have fewer special cases
         if (dy < 0){
             dx *= -1;
             dy *= -1;
             int t = global_x[index];
             global_x[index] = global_x[index2]; global_x[index2] = t;
             t = global_y[index];
             global_y[index] = global_y[index2]; global_y[index2] = t;
         }
         // determine special cases
         if (dx > 0){
          	  DLMA(index,dy,dx,1,0);
         }else if (dx < 0){
         	  DLMA(index,dy,-dx,1,1);
         }else{
              DLSA(index,dy,1);
         }
     }else{

		 }
        index += 2 * THREAD;
        index2 += 2 * THREAD;
	}
	pthread_exit(NULL);
}

void drawLine(struct Matrix mx, int color[3]){
 	if(mx.type == 'b'){

			pthread_t thread_id[THREAD];
		 	int index[THREAD];

			global_x = malloc(mx.col * sizeof(int));
			global_y = malloc(mx.col * sizeof(int));

		 	global_x = mx_toint(mx,global_x,1);
		 	global_y = mx_toint(mx,global_y,2);

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

void DLMA_mod(int x, int y, int dx,int dy,int axis, int check_dir, int line){
    // calculate some constants
		int ddx;
		int ddy;
		int ddyMinddx;
		int Error;

		if("first line"){
			ddx = dx * 2;
			ddy = dy * 2;
			ddyMinddx = ddy - ddx;
	    Error = ddy - dx;
		}

		int * x_input;
		int * y_input;

		y_input = malloc(sizeof(int));
		x_input = malloc(sizeof(int));


    // loop across the major axis
    // 0 is x, else is y
		//assume input malloc is 1
		int size = 1;
		int j = 0;
		x_input[j] = x;
		y_input[j] = y;
		j++;
		//printf("firt x:%d\n",x_input[j]);
		//exit(0);
		size++;
		x_input = realloc(x_input,size * sizeof(int));
		y_input = realloc(y_input,size * sizeof(int));
		//linesize++;


    if(axis == 0){
			//printf("err:%d,errx:%d,step:%d\n",Error,ddyMinddx,ddy);
			//printf("dy:%d\n",dy);
	    while (dx--){//printf("err!\n");

	        // move on major axis and minor axis
	        if (Error > 0){

					    if(check_dir == 0){
					        y++;
					    }else{
							    y--;
					    }
	            Error += ddyMinddx;
	        }
	        // move on major axis only
	        else{
	            Error += ddy;
	        }
					x++;

					x_input[j] = x;
					y_input[j] = y;
					j++;
					size ++;
					x_input = realloc(x_input,size * sizeof(int));
					y_input = realloc(y_input,size * sizeof(int));
					//linesize++;
	        // draw the next pixel
	    }
		}else{
			//printf("err:%d,errx:%d,step:%d\n",Error,ddyMinddx,ddy);
	    while(dx--){
	        // move on major axis and minor axis
					//printf("ddy:%d,y:%d\n",dx,y);
	        if (Error > 0){
						if(check_dir == 0){
		          x++;
		        }else{
		        	x--;
		        }
		          Error += ddyMinddx;
		      }
	        // move on major axis only
	        else{
	            Error += ddy;
	        }

					y++;
					x_input[j] = x;
					y_input[j] = y;
					j++;

					//linesize++;
					size ++;
					x_input = realloc(x_input,size * sizeof(int));
	        y_input = realloc(y_input,size * sizeof(int));
	    }
	}
		//printf("input:%d\n",input[j - 1]);
		x_input[j] = X_MAX;
		y_input[j] = X_MAX;
		j++;
		//
		//printf("y_input:%d,,,,j:%d\n",y_input[j - 1],j);

		if(line == 0){
			x_line = malloc(j * sizeof(int));
			y_line = malloc(j * sizeof(int));
			//x_line = x_input;
			memcpy(x_line,x_input,j  * sizeof(int));
			memcpy(y_line,y_input,j  * sizeof(int));

			//y_line = y_input;
			//free(x_input);

		}else if(line == 1){
			x_line1 = malloc(j * sizeof(int));
			y_line1 = malloc(j * sizeof(int));
			memcpy(x_line1,x_input,j * sizeof(int));
			memcpy(y_line1,y_input,j * sizeof(int));
		}else if(line == 2){
			x_line2 = malloc(j * sizeof(int));
			y_line2 = malloc(j * sizeof(int));
			memcpy(x_line2,x_input,j * sizeof(int));
			memcpy(y_line2,y_input,j * sizeof(int));
		}

		free(x_input);
		free(y_input);
	//	printf("x_input:%d,,,,x_line:%d\n",x_input[0],x_line[0]);
}

void DLSA_mod(int x, int y, int dx,int axis, int line){
    // draw the first pixel

		int size = 1;
		int j = 0;

		int * x_input;
		int * y_input;

		x_input = malloc(size * sizeof(int));
		y_input = malloc(size * sizeof(int));
		//exit(0);
		x_input[j] = x;
		y_input[j] = y;
		j++;
		size++;
		x_input = realloc(x_input,size * sizeof(int));
		y_input = realloc(y_input,size * sizeof(int));
    // loop across the major axis and draw the rest of the pixels
		//exit(0);
		if(axis == 0){//printf("called!\n");
	    while(dx--){

					x++;
					x_input[j] = x;
					y_input[j] = y;
					j++;
					size++;
					x_input = realloc(x_input,size * sizeof(int));
					y_input = realloc(y_input,size * sizeof(int));
    	}
    }else{
			//printf("called!asdsad\n");
	    while (dx--){
	    	y++;
				//exit(0);
				x_input[j] = x;
				y_input[j] = y;
				j++;
				size++;
				x_input = realloc(x_input,size * sizeof(int));
				y_input = realloc(y_input,size * sizeof(int));

			}
    }
		//exit(0);
		x_input[j] = X_MAX;
		y_input[j] = X_MAX;
		j++;
		//printf("DLSA debugging:\n");
		// int lala = 0;
		// while(x_input[lala] != X_MAX){
		// 	printf("x: %d || y:%d\n",x_input[lala],y_input[lala]);
		// }
		//exit(0);
		if(line == 0){
			x_line = malloc(j * sizeof(int));
			y_line = malloc(j * sizeof(int));
			//x_line = x_input;
			memcpy(x_line,x_input,j * sizeof(int));
			memcpy(y_line,y_input,j * sizeof(int));

			//y_line = y_input;
			//free(x_input);

		}else if(line == 1){
			x_line1 = malloc(j * sizeof(int));
			y_line1 = malloc(j * sizeof(int));
			memcpy(x_line1,x_input,j * sizeof(int));
			memcpy(y_line1,y_input,j * sizeof(int));
		}else if(line == 2){
			x_line2 = malloc(j * sizeof(int));
			y_line2 = malloc(j * sizeof(int));
			memcpy(x_line2,x_input,j * sizeof(int));
			memcpy(y_line2,y_input,j * sizeof(int));
		}

		free(x_input);
		free(y_input);

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

	global_x = malloc(sizeof(int));
	global_y = malloc(sizeof(int));


	// while(y_line[odd] != X_MAX){
	// 	printf("x_line:%d, y_line:%d\n",x_line[odd],y_line[odd]);
	// 	odd++;
	// }
	// odd = 0;
	// while(y_line1[odd] != X_MAX){
	// 	printf("x_line1:%d, y_line1:%d\n",x_line1[odd],y_line1[odd]);
	// 	odd++;
	// }
	// odd = 0;
	// while(y_line2[odd] != X_MAX){
	// 	printf("y_line2:%d, x_line2:%d\n",x_line2[odd],y_line2[odd]);
	// 	odd++;
	// }
//	exit(0);

	//exit(0);

//int_size++;
//x[0] = 100;
 //x = realloc(x,int_size * sizeof(int));
 //exit(0);
	while(y_line[counter] != X_MAX){
		//printf("sdasd\n");
		// if(counter == 18){
		// 	printf("18:%d, 17:%d, 19:%d\n",y_line[18],y_line[17],y_line[19]);
		// 	//exit(0);
		// }
		//
		// if(counter == 18){
		// 	printf("16:%d, 15:%d, 14:%d\n",y_line[16],y_line[15],y_line[14]);
		// 	//exit(0);
		// }
		// if(counter == 18){
		// 	printf("13:%d, 12:%d, 11:%d\n",y_line[13],y_line[12],y_line[11]);
		// 	exit(0);
		// }

		if(counter != 0 && y_line[counter] != y_line[counter - 1]){
			//printf("wf\n");
			y[index] = y_line[counter];
			x[index] = x_line[counter];
			int_size++;
			index++;
			x = realloc(x,int_size * sizeof(int));
			y = realloc(y,int_size * sizeof(int));


		}else if(counter == 0){


			// printf("y:%d, x:%d\n",x_line[counter],y_line[counter]);

			y[index] = y_line[counter];
			x[index] = x_line[counter];
			//exit(0);
			int_size++;
			index++;

			x = realloc(x,int_size * sizeof(int));
			y = realloc(y,int_size * sizeof(int));
			//exit(0);
		}


		if(y_line[counter+1]==X_MAX){

			//printf("this!\n");
			y[index] = y_line[counter];
			x[index] = x_line[counter];

			int_size++;
			index++;
			//printf("fasdsadaut!\n");
			x = realloc(x,int_size * sizeof(int));
			y = realloc(y,int_size * sizeof(int));
			//printf("fasdsadaut!\n");
							if(y[index-2] == y[index-1]){
								//index--;
								//printf("x_index-2:%d, y_index-2:%d\n",x[index-2],y[index-2]);
								//printf("x_index-1:%d, y_index-1:%d\n",x[index-1],y[index-1]);

								y[index-2] = y[index-1];
								x[index-2] = x[index-1];
								index--;
							}
							//printf("fasdsadaut!\n");
		}
		//exit(0);
		counter++;
	}

	int_size = 1;
	counter = 0;

	//exit(0);
	while(y_line1[counter] != X_MAX){
		if(counter != 0 && y_line1[counter] != y_line1[counter - 1] ){
			y1[index1] = y_line1[counter];
			x1[index1] = x_line1[counter];
			int_size++;
			index1++;
			x1 = realloc(x1,int_size * sizeof(int));
			y1 = realloc(y1,int_size * sizeof(int));
	//		printf("y:%d, x:%d\n",y[index - 1],x[index - 1]);
				}else if(counter == 0){
					// printf("wf\n");
					// printf("y:%d, x:%d\n",x_line[counter],y_line[counter]);
					y1[index1] = y_line1[counter];
					x1[index1] = x_line1[counter];
					int_size++;
					index1++;
					x1 = realloc(x1,int_size * sizeof(int));
					y1 = realloc(y1,int_size * sizeof(int));
				}

				if(y_line1[counter+1]==X_MAX){
					y1[index1] = y_line1[counter];
					x1[index1] = x_line1[counter];
					int_size++;
					index1++;
					x1 = realloc(x1,int_size * sizeof(int));
					y1 = realloc(y1,int_size * sizeof(int));
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
		if(counter != 0 && y_line2[counter] != y_line2[counter - 1]){
			y2[index2] = y_line2[counter];
			x2[index2] = x_line2[counter];
			int_size++;
			index2++;
			x2 = realloc(x2,int_size * sizeof(int));
			y2 = realloc(y2,int_size * sizeof(int));
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
				int_size++;
				index2++;
				x2 = realloc(x2,int_size * sizeof(int));
				y2 = realloc(y2,int_size * sizeof(int));
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
					// if(check == index1 - 1){
					// 	y2[index2] = y_line2[counter];
					// 	x2[index2] = x_line2[counter];
					// 	int_size++;
					// 	index2++;
					// 	x2 = realloc(x2,int_size * sizeof(int));
					// 	y2 = realloc(y2,int_size * sizeof(int));
					// }
					// check++;

			}

		counter++;
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
				global_x[counter] = x[ok];
				global_y[counter] = y[ok];
				counter++;
				global_x[counter] = x1[la];
				global_y[counter] = y1[la];
				counter++;
				la = 0;
				break;
			}
			la++;
		}
		if(la != 0){
			while(oh < index2){
				if(y[ok] == y2[oh]){
					global_size += 2;
					global_x = realloc(global_x,global_size * sizeof(int));
					global_y = realloc(global_y,global_size * sizeof(int));
					global_x[counter] = x[ok];
					global_y[counter] = y[ok];
					counter++;
					global_x[counter] = x2[oh];
					global_y[counter] = y2[oh];
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

	// int test = 0;
	// // while(test < global_size){
	// // 	printf("global_x[test]:%d, global_y[test]:%d\n",global_x[test],global_y[test]);
	// // 	test++;
	// // }
	// printf("index2:%d\n",index);
	// while(test < index){
	// 	printf("xline:%d , yline:%d\n",x[test],y[test]);
	// 	//printf("xline2:%d , yline2:%d\n",x2[test],y2[test]);
	// 	//printf("xline1:%d , yline1:%d\n",x1[test],y1[test]);
	// 	test++;
	// }
	// test = 0;
	// while(test < index2){
	// 	//printf("xline:%d , yline:%d\n",x[test],y[test]);
	// 	printf("xline2:%d , yline2:%d\n",x2[test],y2[test]);
	// 	//printf("xline1:%d , yline1:%d\n",x1[test],y1[test]);
	// 	test++;
	// }
	// test =0;
	// while(test < index1){
	// 	//printf("xline:%d , yline:%d\n",x[test],y[test]);
	// 	//printf("xline2:%d , yline2:%d\n",x2[test],y2[test]);
	// 	printf("xline1:%d , yline1:%d\n",x1[test],y1[test]);
	// 	test++;
	// }
	//sleep(5);

	free(x);
	free(x1);
	free(x2);
	free(y1);
	free(y2);
	free(y);
	//exit(0);//return size;
}

void scanLine(struct Matrix mx){
	int top_y = Y_MIN;
	int mid_y = Y_MIN;
	int bot_y = Y_MAX;
	int top_x;
	int mid_x;
	int bot_x;
	int top_x1;
	int top_y1;
	int size = 0;
	int dx;
	int dx1;
	int dx2;
	int dy;
	int dy1;
	int dy2;
	int x1;
	int y1;
	int a = 0;
	int i;

	//FILE* file = fopen("/dev/urandom", "w+");
	for(i = 0; i < mx.col; i += 3){
		int * buffer;
		//while(){
		buffer = sys_random(buffer,3);
		//}

		buffer[0] = abs(buffer[0]  % 255);
		buffer[1] = abs(buffer[1]  % 255);
		buffer[2] = abs(buffer[2]  % 255);

		if(dot_pdt(mx.vx[a],mx.vy[a],mx.vz[a]) >= 0){
			//
			// printf("mx.y[i]:%f  %f   %f\n",mx.y[i], mx.y[i + 1], mx.y[i+2]);
			// printf("mx.x[i]:%f  %f   %f\n",mx.x[i], mx.x[i + 1], mx.x[i+2]);
			//sleep(3);
	if("get coord"){
			if(top_y < round(mx.y[i])){
				top_y = round(mx.y[i]);
				top_x = round(mx.x[i]);}
			if(top_y < round(mx.y[i + 1])){
				top_y = round(mx.y[i + 1]);
				top_x = round(mx.x[i + 1]);}
			if(top_y < round(mx.y[i + 2])){
				top_y = round(mx.y[i + 2]);
				top_x = round(mx.x[i + 2]);}
			if(bot_y > round(mx.y[i])){
				bot_y = round(mx.y[i]);
				bot_x = round(mx.x[i]);}
			if(bot_y > round(mx.y[i + 1])){
				//printf("?????\n");
				bot_y = round(mx.y[i + 1]);
				bot_x = round(mx.x[i + 1]);}
			if(bot_y > round(mx.y[i + 2])){
				//printf("lololoasdsad\n");
				//printf("round:mx.y:%f\n",mx.y[i+2]);
				bot_y = round(mx.y[i + 2]);
				bot_x = round(mx.x[i + 2]);}
				//printf("bbbbbbot_y:%d\n",bot_y);
			if(round(mx.y[i]) != bot_y && round(mx.y[i]) != top_y){
				mid_y = round(mx.y[i]);
				mid_x = round(mx.x[i]);}
			else if(round(mx.y[i + 1]) != bot_y && round(mx.y[i + 1]) != top_y){
				mid_y = round(mx.y[i + 1]);
				mid_x = round(mx.x[i + 1]);}
			else if(round(mx.y[i + 2]) != bot_y && round(mx.y[i + 2]) != top_y){
				mid_y = round(mx.y[i + 2]);
				mid_x = round(mx.x[i + 2]);}
				else if(round(mx.x[i]) != bot_x && round(mx.x[i]) != top_x){
					mid_y = round(mx.y[i]);
					mid_x = round(mx.x[i]);}
					else if(round(mx.x[i + 1]) != bot_x && round(mx.x[i + 1]) != top_x){
						mid_y = round(mx.y[i + 1]);
						mid_x = round(mx.x[i + 1]);}
						else if(round(mx.x[i + 2]) != bot_x && round(mx.x[i + 2]) != top_x){
							mid_y = round(mx.y[i + 2]);
							mid_x = round(mx.x[i + 2]);}
		}
			if("get dx"){
				dx = top_x - bot_x;
				dx1 = top_x - mid_x;
				dx2 = mid_x - bot_x;

				dy = top_y - bot_y;
				dy1 = top_y - mid_y;
				dy2 = mid_y - bot_y;
				//printf("dy2:%d\n",dy2);
			}


			if(abs(dx) >= abs(dy)){
			 // if x2 < x1, flip the points to have fewer special cases
			   x1 = bot_x;
				 y1 = bot_y;

			 	if (dx < 0){
					 dx *= -1; dy *= -1;
					 x1 = top_x;
					 y1 = top_y;
					// printf("nonono\n");
				 }
				 //printf("top_x:%d,bot_x:%d,top_y:%d,bot_y:%d\n",top_x,bot_x,top_y,bot_y);
				 if(dy > 0){
					 //printf("nonono\n");
						 DLMA_mod(x1,y1,dx,dy,0,0,0);
				 }else if (dy < 0){
	 					 DLMA_mod(x1,y1,dx,-dy,0,1,0);
				 }else{
						 DLSA_mod(x1,y1,dx,0,0);
				 }
	 	 	}
	  	// else the Y axis is the major axis
	  	else{
				x1 = bot_x;
				y1 = bot_y;
			 // if y2 < y1, flip the points to have fewer special cases
			 if (dy < 0){
				 dx *= -1; dy *= -1;
				 x1 = top_x;
				 y1 = top_y;
			 }
			 if (dx > 0){
						DLMA_mod(x1,y1,dy,dx,1,0,0);
			 }else if(dx < 0){
					  DLMA_mod(x1,y1,dy,-dx,1,1,0);
			 }else{
						DLSA_mod(x1,y1,dy,1,0);
			 }
	 		}




			if(abs(dx2) >= abs(dy2)){
			 // if x2 < x1, flip the points to have fewer special cases
			 		x1 = bot_x;
					y1 = bot_y;
				 if (dx2 < 0){
					 dx2 *= -1; dy2 *= -1;
					 x1 = mid_x;
					 y1 = mid_y;
				 }

				 //printf("top_x:%d,bot_x:%d,top_y:%d,bot_y:%d\n",top_x,bot_x,top_y,bot_y);
				 if(dy2 > 0){
					  // printf("dy222222:%d\n",dx2 > 0);
						 DLMA_mod(x1,y1,dx2,dy2,0,0,2);
				 }else if(dy2 < 0){
					 //	printf("dy222222:%d\n",dy2);
						 DLMA_mod(x1,y1,dx2,-dy2,0,1,2);
				 }else{
						 DLSA_mod(x1,y1,dx2,0,2);
				 }
			}
			else{
				x1 = bot_x;
				y1 = bot_y;
			 if (dy2 < 0){
				 dx2 *= -1; dy2 *= -1;
				 x1 = mid_x;
				 y1 = mid_y;
			 }
			 if (dx2 > 0){
				 //printf("run4\n");
				DLMA_mod(x1,y1,dy2,dx2,1,0,2);
			}else if(dx2 < 0){
				 //printf("dy2:%d,dx2:%d\n",dy2,dx2);
				DLMA_mod(x1,y1,dy2,-dx2,1,1,2);
			 }else{
				DLSA_mod(x1,y1,dy2,1,2);
			 }
			}


			if(abs(dx1) >= abs(dy1)){
			 // if x2 < x1, flip the points to have fewer special cases
			 	x1 = mid_x;
				y1 = mid_y;
				 if (dx1 < 0){
					 dx1 *= -1; dy1 *= -1;
					 x1 = top_x;
					 y1 = top_y;
				 }

				 //printf("top_x:%d,bot_x:%d,top_y:%d,bot_y:%d\n",top_x,bot_x,top_y,bot_y);
				 if(dy1 > 0){
						 DLMA_mod(x1,y1,dx1,dy1,0,0,1);
				 }else if(dy1 < 0){
						 DLMA_mod(x1,y1,dx1,-dy1,0,1,1);
				 }else{
					 //printf("x1:%d,y1:%d\n",x1,y1);
						 DLSA_mod(x1,y1,dx1,0,1);
				 }
			}
			else{
				// x1 = top_x;
				// y1 = top_y;
				x1 = mid_x;
				y1 = mid_y;
				 if (dy1 < 0){
					 dx1 *= -1; dy1 *= -1;
					 x1 = top_x;
					 y1 = top_y;
					 // x1 = mid_x;
					 // y1 = mid_y;
				 }
			 if (dx1 > 0){
				 //printf("this!\n" );
						DLMA_mod(x1,y1,dy1,dx1,1,0,1);
			 }else if(dx1 < 0){
				 		DLMA_mod(x1,y1,dy1,-dx1,1,1,1);
			 }else{
						DLSA_mod(x1,y1,dy1,1,1);
			 }
			}

		// 	printf("x_line:%d\n",x_line[0]);
		// exit(0);
			//
			// printf("top_x:%d,top_y:%d\n",top_x,top_y);
			// printf("mid_x:%d,mid_y:%d\n",mid_x,mid_y);
			// printf("bot_x:%d,bot_y:%d\n",bot_x,bot_y);
			// int ok = 0;
			// while(x_line[ok] != X_MAX){
			// 		printf("x_line: %d\n", x_line[ok]);
			// 		ok++;
			// }

			purification();


			//printf("fault?\n");

			int color[3];
			color[0] = buffer[0];//buffer[0] % 255;
			color[1] = buffer[1];//buffer[1] % 255;
			color[2] = buffer[2];//buffer[2] % 255;

			drawLine_mod(color);
				//exit(0);
			//canvas_push("this.ppm");
			int line_count = 0;
			int line_count1 = 0;
			int result_count = 0;
			//
			// printf("mx.x:%f,mx.y:%f\n",mx.x[0],mx.y[0]);
			// printf("mx.x:%f,mx.y:%f\n",mx.x[1],mx.y[1]);
			// printf("mx.x:%f,mx.y:%f\n",mx.x[2],mx.y[2]);


			 free(x_line);  // <--this is global
			 free(y_line);

			 free(x_line1);
			 free(y_line1);
			 free(y_line2);
			 free(x_line2);

			 top_y = Y_MIN;
			 mid_y = Y_MIN;
			 bot_y = Y_MAX;
		 //free(x_line2);
			// free(y_line2);

		}
		free(buffer);
		a++;
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
