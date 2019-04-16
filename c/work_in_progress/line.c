#include "engine.h"

int * global_x;
int * global_y;

int * global_xx;
int * global_yy;
int global_index;
int global_res;
int global_color[3];
//int global_major_axis_counter;


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
	            global_x[index]++;
			    if(check == 0){
			        global_y[index]++;
			    }else{
					global_y[index]--;
			    }
	            Error += dy2Mindx2;
	        }
	        // move on major axis only
	        else{
	            global_x[index]++;
	            Error += dy2;
	        }
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
		            global_y[index]++;
		            Error += dy2Mindx2;
		        }
	        // move on major axis only
	        else{
	            global_y[index]++;
	            Error += dy2;
	        }	 
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
	while(i < mx.col){
		global_x[j] = mx.x[i];
		global_y[j] = mx.y[i];
		j++; i++;
		global_x[j] = mx.x[i];
		global_y[j] = mx.y[i];
		j++; 
		global_x[j] = mx.x[i];
		global_y[j] = mx.y[i];
		j++; i++;
		global_x[j] = mx.x[i];
		global_y[j] = mx.y[i];
		j++;
		global_x[j] = mx.x[i];
		global_y[j] = mx.y[i];
		j++; i -= 2;
		global_x[j] = mx.x[i];
		global_y[j] = mx.y[i];
		j++; i++;
	}
}

void * drawLine_helper(void * arg){
	int index = (void *) arg;
	int index2 = index + 1;

	//for(i = 0; i < mx.col; i+=2){
		// printf("index:%d\n",index);
  //   	printf("x:%d ; y:%d ; x1:%d ; y1:%d\n",global_x[index],global_y[index],global_x[index+1],global_y[index+1]);
    //}

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

			global_x = malloc(3 * mx.col * sizeof(int));
			global_y = malloc(3 * mx.col * sizeof(int));
			
		 	//global_x = mx_toint(mx,global_x,1);
		 	//global_y = mx_toint(mx,global_y,2);
			poly_lines(mx);
			
		 	global_color[0] = color[0];
		 	global_color[1] = color[1];
		 	global_color[2] = color[2];

			global_res = 6 * mx.col;

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



/*
struct Array drawLine(struct Array arr, struct Edge ed, int color[3]){
	int * x;
	int * y;
	int * x1;
	int * y1;

	x = ed_toint(ed,x,0,0);
	y = ed_toint(ed,y,1,0);
	x1 = ed_toint(ed,x1,0,1);
	y1 = ed_toint(ed,x1,1,1);

	int * d_x;
	int * d_y;
	int * d_x1;
	int * d_y1;
	int * d_r;
	int * d_g;
	int * d_b;

	int edge_num = ed.col/2;

	int edge_size = edge_num * sizeof(int);
	int size = (X_MAX - X_MIN) * (Y_MAX - Y_MIN) * sizeof(int);


    gp_drawline<<<edge_num,1>>>(d_r, d_g, d_b, 
							    d_x, d_y, 
							    d_x1, d_y1, 
							    color[0],color[1],color[2]);

    return arr;
}
*/
