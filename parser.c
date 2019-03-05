#include "engine.h"

int main(int argc, char *argv[]){

printf("donno how to do this yet\n");
	
    char c[1000];
    FILE *fp;
    if(argc < 2){
    	printf("Need a file name\n");
    	exit(1);
    }else if ((fp = fopen(argv[1], "r")) == NULL){
        printf("Error! opening file");
        exit(1);         
    }

    char buffer[100] = "";
    int line = 1;

    int fcn = 0;
	
    while(fgets(buffer, sizeof buffer, fp)){  
        char et[100] = "\n";                 
        if (line == 1){                     
            //printf ("%d : %s ", line, buffer);  
    			fcn = 1;
    		}
        else{
            if(sscanf (buffer, "%s", et) != 1){ 
               fprintf (stderr, "error: invalid conversion, line %d\n", line);
                return 1;
            }
            sscanf(buffer, "%s", et);
            printf("%d : %s\n", line, et); 
        }
        line++;                             
    }


    if (fp != stdin) fclose (fp); 

    return 0;






















}
