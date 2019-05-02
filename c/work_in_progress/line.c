#include "engine.h"

/* random snippet
I = AKa + IpKl(N*L) + IpKs[(2N(N*L)-L)*V]
	*Specular Reflection is supposed to fade off quickly

*/
int seed;
int * global_x;
int * global_y;
int * global_xx;
int * global_yy;
int global_index;
int global_res;
int global_color[3];
int global_size;

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
	    	global_x[index]++;
        	canvas_set_s(global_x[index], global_y[index], global_color);
    	}
    }else{
	    while (dx--){
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
      // if the X axis is the major axis
     	if(abs(dx) >= abs(dy)){
         // if x2 < x1, flip the points to have fewer special cases
    	   if (dx < 0){
           dx *= -1; dy *= -1;
           int t = global_x[index];
           global_x[index] = global_x[index2]; global_x[index2] = t;
           t = global_y[index];
           global_y[index] = global_y[index2]; global_y[index2] = t;
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
     else{
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

void drawLine_mod(int *x, int *y, int size, int color[3]){
	pthread_t thread_id[THREAD];
	int index[THREAD];
	global_x = x;
	global_y = y;
	//global_size = 0;
	//poly_lines(mx);
	global_color[0] = color[0];
	global_color[1] = color[1];
	global_color[2] = color[2];

	global_res = size;
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
}

int* sys_random(int * buffer, int size){

	buffer = malloc(sizeof(int) * size );
	//printf("initiating...this may take several minites\n");
	FILE* file = fopen("/dev/urandom", "r");
	fread(buffer, sizeof(int), size ,file);
	fclose(file);

	return buffer;
}

int* DLMA_mod(int *input,int x, int y, int dx,int dy,int axis, int check_dir){
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
    // draw the first pixel
    // loop across the major axis
    // 0 is x, else is y

		//assume input realloc is 2
		int size = 2;
		int j = 0;
		input[j] = x;
		j++;
		input[j] = y;
		j++;
		size += 2;
		input = realloc(input,size * sizeof(int));

		//linesize++;

    if(axis == 0){
	    while (dx--){
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

					input[j] = x;
					j++;
					input[j] = y;
					j++;
					size += 2;
					input = realloc(input,size * sizeof(int));

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
					input[j] = x;
					j++;
					input[j] = y;
					j++;
					;
					//linesize++;
					size += 2;
					input = realloc(input,size * sizeof(int));
	        // draw the next pixel
	    }
	}
		//printf("input:%d\n",input[j - 1]);
		input[j] = X_MAX;
		printf("input:%d,,,,j:%d\n",input[j - 1],j);
		return input;
}

int* DLSA_mod(int *input,int x, int y, int dx,int axis){
    // draw the first pixel
		int size = 2;
		int j = 0;
		input[j] = x;
		j++;
		input[j] = y;
		j++;
		size += 2;
		input = realloc(input,size * sizeof(int));
		;
    // loop across the major axis and draw the rest of the pixels
    if(axis == 0){
	    while(dx--){
					x++;
					input[j] = x;
					j++;
					input[j] = y;
					j++;
					size += 2;
					input = realloc(input,size * sizeof(int));
					;
    	}
    }else{
	    while (dx--){
	    	y++;
				input[j] = x;
				j++;
				input[j] = y;
				j++;
				size += 2;
				input = realloc(input,size * sizeof(int));
				;
    	}
    }
		input[j] = X_MAX;
		return input;
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

	int *line;
	int *line1;
	int *line2;

	int *x;
	int *y;

	int x1;
	int y1;

	int a = 0;
	int i;

	for(i = 0; i < 3; i += 3){
		int * buffer;
		buffer = sys_random(buffer,3);

		buffer[0] = abs(buffer[0]  % 255);
		buffer[1] = abs(buffer[1]  % 255);
		buffer[2] = abs(buffer[2]  % 255);

		if(dot_pdt(mx.vx[a],mx.vy[a],mx.vz[a]) >= 0){

			line = malloc(2 * sizeof(int));
			line1 = malloc(2 * sizeof(int));
			line2 = malloc(2 * sizeof(int));

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
			if(round(mx.y[i + 1]) != bot_y && round(mx.y[i + 1]) != top_y){
				mid_y = round(mx.y[i + 1]);
				mid_x = round(mx.x[i + 1]);}
			if(round(mx.y[i + 2]) != bot_y && round(mx.y[i + 2]) != top_y){
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

			//printf("top_x:%d,top_y:%d\n",top_x,top_y);
			//printf("mid_x:%d,mid_y:%d\n",mid_x,mid_y);
			//printf("bot_x:%d,bot_y:%d\n",bot_x,bot_y);

			// if the X axis is the major axis

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
						 line = DLMA_mod(line,x1,y1,dx,dy,0,0);
				 }else if (dx < 0){
	 					 line = DLMA_mod(line,x1,y1,dy,-dx,0,1);
				 }else{
						 line = DLSA_mod(line,x1,y1,dx,0);
				 }
	 	 	}
	  	// else the Y axis is the major axis
	  	else{

			 // if y2 < y1, flip the points to have fewer special cases
			 if (dy < 0){
				 dx *= -1; dy *= -1;
				 int t = top_x;
				 top_x = bot_x; bot_x = t;
				 t = top_y;
				 top_y = bot_y; bot_y = t;
			 }
			 if (dx > 0){

						line = DLMA_mod(line,bot_x,bot_y,dy,dx,1,0);
			 }else if(dx < 0){
				 printf("calld?\n");
			 }else{
						line = DLSA_mod(line,top_y,top_x,dy,1);
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
				 if(dx2 > 0){
						 line2 = DLMA_mod(line2,x1,y1,dx2,dy2,0,0);
				 }else if(dx2 < 0){

						 line2 = DLMA_mod(line2,x1,y1,dx2,-dy2,0,1);
				 }else{
						 line2 = DLSA_mod(line2,x1,y1,dx2,0);
				 }
			}
			else{
			 if (dy2 < 0){
				 dx2 *= -1; dy2 *= -1;
				 int t = mid_x;
				 mid_x = bot_x; bot_x = t;
				 t = mid_y;
				 mid_y = bot_y; bot_y = t;
			 }
			 if (dx2 > 0){
				 //printf("run4\n");
				line2 = DLMA_mod(line2,bot_x,bot_y,dy2,dx2,1,0);
			 }else if(dx2 < 0){
				 //printf("dy2:%d,dx2:%d\n",dy2,dx2);
				line2 = DLMA_mod(line2,bot_x,bot_y,dy2,-dx2,1,1);
			 }else{
				line2 = DLSA_mod(line2,bot_y,bot_x,dy2,1);
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
						 line1 = DLMA_mod(line1,x1,y1,dx1,dy1,0,0);
				 }else if (dx1 < 0){
					 printf("called?\n");
						 line1 = DLMA_mod(line1,x1,y1,dy1,-dx1,0,1);
				 }else{
						 line1 = DLSA_mod(line1,mid_x,mid_y,dx1,0);
				 }
			}
			else{
			 if (dy1 < 0){
				 dx1 *= -1; dy2 *= -1;
				 int t = mid_x;
				 mid_x = top_x; top_x = t;
				 t = mid_y;
				 mid_y = top_y; top_y = t;
			 }
			 if (dx > 0){
						line1 = DLMA_mod(line1,mid_x,mid_y,dy1,dx1,1,0);
			 }else if(dx < 0){
				 		line1 = DLMA_mod(line1,mid_x,mid_y,dy1,-dx1,1,1);
			 }else{
						line1 = DLSA_mod(line1,mid_y,mid_x,dy1,1);
			 }
			}


			int color[3];
			color[0] = buffer[0];//buffer[0] % 255;
			color[1] = buffer[1];//buffer[1] % 255;
			color[2] = buffer[2];//buffer[2] % 255;


			//canvas_push("this.ppm");
			int line_count = 0;
			int line_count1 = 0;
			int result_count = 0;

			int xy_size = 4;
			x = malloc( xy_size * sizeof(int));
			y = malloc( xy_size * sizeof(int));

			if(line2[line_count + 2] == X_MAX){
				printf("lol\n");
				/*
				while(line2[line_count1] != X_MAX){
				x[result_count] = line[line_count];
				line_count++;
				y[result_count] = line[line_count];
				result_count++; line_count++;
				x[result_count] = line2[line_count1];
				line_count1++;
				y[result_count] = line2[line_count1];
				result_count++; line_count1++;
				xy_size += 4;
				x = realloc(x, xy_size * sizeof(int));
				y = realloc(y, xy_size * sizeof(int));
			}

				line_count1 = 0;

				while(line1[line_count1] != X_MAX){
				x[result_count] = line[line_count];
				line_count++;
				y[result_count] = line[line_count];
				result_count++; line_count++;
				x[result_count] = line1[line_count1];
				line_count1++;
				y[result_count] = line1[line_count1];
				result_count++; line_count1++;
				xy_size += 4;
				x = realloc(x, xy_size * sizeof(int));
				y = realloc(y, xy_size * sizeof(int));
			}
			 	*/
		 }else if(line1[line_count + 2] == X_MAX){
			 printf("lala\n");
		 }


			int ok = 0;
			//printf(":%d\n",);
			//exit(0);


			printf("bot_x:%d,bot_y:%d\n",bot_x,bot_y);

			while(line2[ok] != X_MAX){
				printf("line2 x:%d,y:%d\n",line2[ok],line2[ok+1]);
				ok+=2;
			}
			ok = 0;

			printf("mid_x:%d,mid_y:%d\n",mid_x,mid_y);
			while(line1[ok] != X_MAX){
				printf("line1 x:%d,y:%d\n",line1[ok],line1[ok+1]);
				ok+=2;
			}
			printf("top_x:%d,top_y:%d\n",top_x,top_y);
			ok = 0;
			while(line[ok] != X_MAX){
				printf("line x:%d, y:%d\n",line[ok],line[ok + 1]);
				ok+=2;
			}
			// while(ok < xy_size){
			// 	printf("x:%d, y:%d\n",x[ok],y[ok]);
			// 	ok++;
			// }

			ok = 0;
			printf("mx.x:%f,mx.y:%f\n",mx.x[0],mx.y[0]);
			printf("mx.x:%f,mx.y:%f\n",mx.x[1],mx.y[1]);
			printf("mx.x:%f,mx.y:%f\n",mx.x[2],mx.y[2]);

			//exit(0);

		//	drawLine_mod(x,y,xy_size - 10,color);
			//canvas_push("hi.ppm");

			//exit(0);
			// while(line1[j] != X_MAX){
			// 	//printf(":%d\n",);
			// 	printf("x:%d , y:%d\n",line1[j],line1[j+1]);
			// 	j += 2;
			// }

			free(line);
			free(line1);
			free(line2);
			free(x);
			free(y);
			if(a == 10){
				//exit(0);
			}

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
