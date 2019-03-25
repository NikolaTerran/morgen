#include "engine.h"

int main(void){
	struct Array arr_1;
	arr_1 = array_init(arr_1);
	//array_print(arr_1);
	array_push(arr_1,"red.ppm");
	return 0;
}