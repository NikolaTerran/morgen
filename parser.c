#include "engine.h"


//////////////////////////////////////////////////////////////////
//How to use this parser:                                       //
//1. for rotation, x == 0, y == 1, z == other                   //
//////////////////////////////////////////////////////////////////


int main(int argc, char *argv[]){
    
    ////////////////file check//////////////////
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    ///////////////////////////////////////////
  
    //Matrix conf//////////////////////////////
    struct Matrix edge;
	edge = mx_init(4,0);
	//edge.row = 4;
	struct Matrix trans;
	//struct Matrix result;

    ///////////////////////////////////////////

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
   
    fp = fopen(argv[1], "r");
   
    if(fp == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }



    //Operations//////////////////////////////
    //all input changed to int////////////////
    while((nread = getline(&line, &len, fp)) != -1){
        if(!strcmp(line,"line\n")){
            if(nread = getline(&line, &len, fp) == -1){
                printf("ERR: need numbers\n");
                exit(1);
            }
            char * seg;
            double input[6];
	    	int i;
	    	for(i = 0; i < 6; i++){
	    		seg = strsep(&line," ");
    	  		input[i] = atoi(seg);
	    	}
	    	edge = addedge(edge,input[0],input[1],input[2],input[3],input[4],input[5]);
	    }else if(!strcmp(line,"ident\n")){
	    	trans = mx_iden(edge,1);
	    }else if(!strcmp(line,"scale\n")){
	        if(nread = getline(&line, &len, fp) == -1){
                printf("ERR: need numbers\n");
                exit(1);
            } 
            char * seg;
            double input[3];
	    	int i;
	    	for(i = 0; i < 3; i++){
	    		seg = strsep(&line," ");
    	  		input[i] = atoi(seg);
	    	}
	    	edge = mx_dilation(edge,input[0],input[1],input[2]);
	    }else if(!strcmp(line,"move\n")){
	        if(nread = getline(&line, &len, fp) == -1){
                printf("ERR: need numbers\n");
                exit(1);
            }
            char * seg;
            double input[3];
	    	int i;
	    	for(i = 0; i < 3; i++){
	    		seg = strsep(&line," ");
    	  		input[i] = atoi(seg);
	    	}
	    	edge = mx_transform(edge,input[0],input[1],input[2]);	    	
	    }else if(!strcmp(line,"rotate\n")){
	        if(nread = getline(&line, &len, fp) == -1){
                printf("ERR: need numbers\n");
                exit(1);
            }
            char * seg;
            double input[2];
	    	int i;
	    	for(i = 0; i < 2; i++){
	    		seg = strsep(&line," ");
    	  		input[i] = atoi(seg);
	    	}
	    	edge = mx_rotate(edge,input[0],input[1]);
	    }else if(!strcmp(line,"circle\n")){
	    	if(nread = getline(&line, &len, fp) == -1){
                printf("ERR: need numbers\n");
                exit(1);
            }
            char * seg;
            double input[4];
	    	int i;
	    	for(i = 0; i < 4; i++){
	    		seg = strsep(&line," ");
    	  		input[i] = atoi(seg);
	    	}
	    	edge = circle(edge,input[0],input[1],input[2],input[3]);
	    }else if(!strcmp(line,"hermite\n")){
	    	if(nread = getline(&line, &len, fp) == -1){
                printf("ERR: need numbers\n");
                exit(1);
            }
            char * seg;
            double input[8];
	    	int i;
	    	for(i = 0; i < 8; i++){
	    		seg = strsep(&line," ");
    	  		input[i] = atoi(seg);
	    	}
	    	edge = hermite(edge,input[0],input[1],input[2],input[3],input[4],input[5],input[6],input[7]);
	    }else if(!strcmp(line,"bezier\n")){	 
	    	if(nread = getline(&line, &len, fp) == -1){
                printf("ERR: need numbers\n");
                exit(1);
            }
            char * seg;
            double input[8];
	    	int i;
	    	for(i = 0; i < 8; i++){
	    		seg = strsep(&line," ");
    	  		input[i] = atoi(seg);
	    	}
	    	edge = bezier(edge,input[0],input[1],input[2],input[3],input[4],input[5],input[6],input[7]);

	    }else if(!strcmp(line,"yrev\n")){
	    	edge = mx_yrev(edge);

	    }else if(!strcmp(line,"apply\n")){
	    //	if(result.row !=){
		//    	result = edge;
		//    }else{

		//    }
	    //	struct Matrix edge;
		//	edge.row = 4;
	    }else if(!strcmp(line,"display\n")){
			
	    	/*
			int x, y;
			FILE *f;

			f = popen("display", "w");

			fprintf(f, "P3\n%d %d\n%d\n", 500, 500, MAX_COLOR);
			for ( y=0; y < 500; y++ ) {
			for ( x=0; x < 500; x++)
				fprintf(f, "%d %d %d ", s[x][y].red, s[x][y].green, s[x][y].blue);
				fprintf(f, "\n");
			}

			pclose(f);
			*/

	    }else if(!strcmp(line,"save\n")){

	    }

    }

    //result.row = 4;
    //result = mx_addc(result,edge);
	mx_export(edge);
	mx_free(edge);

    free(line);
    fclose(fp);
    exit(EXIT_SUCCESS);   

    return 0;
}
