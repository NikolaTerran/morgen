#include "engine.h"

void line_helper(int array[][500][3], int x1, int y1, int x2, int y2, int x3, int y3, int octants, int color[], double m){
	
	double slope;
		switch(octants){
			case 1: 
			while(x3 <= x2){
					slope = ((double)y1 - (double)y3)/((double)x3 - (double)x1);
					if(slope > m){
						//db("slope",slope);
					    //db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
						//y3 --;
					}else{
					    //db("slope",slope);
					    //db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
						y3 --;
					}
			}		
			break;
			case 2: //up right
			while(y3 >= y2){
					slope = ((double)y1 - (double)y3)/((double)x3 - (double)x1);
					if(slope > m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
						y3 --;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						//x3 ++;
						y3 --;
					}	
			}	
			break;
			case 3: //up left
			while(y3 >= y2){
					slope = ((double)y1 - (double)y3)/((double)x3 - (double)x1);
					if(slope < m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 --;
						y3 --;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						//x3 --;
						y3 --;
					}
			}
			break;
			case 4: //left up
			while(x3 >= x2){
					slope = ((double)y1 - (double)y3)/((double)x3 - (double)x1);
					if(slope < m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						
						x3 --;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						y3 --;
						x3 --;
					}
			}
			break;
			case 5: //left down
					if(slope > m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 --;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 --;
						y3 ++;
					}
			break;
			case 6: //down left
					if(slope < m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						y3 ++;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 --;
						y3 ++;
					}
			break;
			case 7: //down right
					if(slope > m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						y3 ++;
						
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
						y3 ++;
					}
			break;
			case 8: //right down
					if(slope < m){
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
					}else{
						//db("slope",slope);
						//db("y3",y3);
						//db("x3",x3);
						array[y3][x3][0] = color[0];
						array[y3][x3][1] = color[1];
						array[y3][x3][2] = color[2];
						x3 ++;
						y3 ++;
					}
			break;
		}
	}


int drawLine(int array[][500][3], int x1 , int y1, int x2, int y2, int color[]){
	int octants;
	
	if(x2 == x1 && y2 == y1){
				array[y1][x1][0] = color[0];
				array[y1][x1][1] = color[1];
				array[y1][x1][2] = color[2];
	}else{
				//{double m = 1;}
			double m = ((double)y1 - (double)y2) / ((double)x2 - (double)x1);
			//db("m",m);
			
				if(y2 <= y1){
					if(x2 >= x1){
						if( m <= 1 ){
							 octants = 1;
						}else{
							 octants = 2;
						}
					}else{
						if( m <= -1 ){
							 octants = 3;
						}else{
							 octants = 4;
						}
					}
				}else{
				   if(x2 < x1){
						if( m <= 1 ){
							 octants = 5;
						}else{
							 octants = 6;
						}
					}else{
						if( m <= -1 ){
							 octants = 7;
						}else{
							 octants = 8;
						}
					}
				}
				
				//db("octants",(double)octants);
				
				array[y1][x1][0] = color[0];
				array[y1][x1][1] = color[1];
				array[y1][x1][2] = color[2];
				//db("lol",(double)octants);
				switch(octants){
						case 1: line_helper(array,x1,y1,x2,y2,x1 + 1,y1 - 1,octants,color,m);
						break;
						case 2: line_helper(array,x1,y1,x2,y2,x1 + 1,y1 - 1,octants,color,m);
						break;
						case 3: line_helper(array,x1,y1,x2,y2,x1 - 1,y1 - 1,octants,color,m);
						break;
						case 4: line_helper(array,x1,y1,x2,y2,x1 - 1,y1 - 1,octants,color,m);//left up
						break;
						case 5: line_helper(array,x2,y2,x1,y1,x2 + 1,y2 - 1,1,color,m);//left down
						break;
						case 6: line_helper(array,x2,y2,x1,y1,x2 + 1,y2 - 1,2,color,m);//down left
						break;
						case 7: line_helper(array,x2,y2,x1,y1,x2 - 1,y2 - 1,3,color,m);//down right
						break;
						case 8: line_helper(array,x2,y2,x1,y1,x2 - 1,y2 - 1,4,color,m);// right down
						break;
						}
	}
}
