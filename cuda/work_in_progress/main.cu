#include "engine.h"

int main(void){
	struct Array arr_1;
	arr_1 = array_init(arr_1);
	

	struct Matrix edge;
	edge = mx_init(edge,4,0);
	edge = mx_adde(edge,250,250,0,400,400,0);

	int * i;
	i = mx_rowtoint(edge,i,0);

	int j;
	for(j = 0; j < edge.col; j++){
		printf("i:%d\n",i[j]);
	}
	array_push(arr_1,"image.ppm");
	return 0;
}