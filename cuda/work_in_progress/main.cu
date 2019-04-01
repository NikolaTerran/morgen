#include "engine.h"

int main(void){
	struct Array arr1;
	arr1 = array_init(arr1);
	struct Array arr2;
	arr2 = array_init(arr2);

	struct Edge ed;
	ed = ed_init(ed,4,0);

	int color[3];
	color[0] = 0;
	color[1] = 0;
    color[2] = 0;

//    ed = ed_adde(ed,75,100,0,99,-249,0);
//    ed = ed_adde(ed,0,0,0,249,0,0);
//    ed = ed_adde(ed,0,0,0,-250,0,0);
/*    ed = ed_adde(ed,0,0,0,0,250,0);

    ed = ed_adde(ed,0,0,0,249,250,0);
    ed = ed_adde(ed,0,0,0,249,-249,0);
    ed = ed_adde(ed,0,0,0,-249,250,0);
    ed = ed_adde(ed,0,0,0,-250,-249,0);
*/
    ed = add_bezier(ed,0,0,100,200,200,100,249,250);
    ed = add_bezier(ed,0,0,-100,200,-200,100.1,-250,250);
//runtime calculation cpu vs gpu

	clock_t cp_start, cp_end, gp_start,gp_end;
	double cpu_time_used, gpu_time_used;
	

	gp_start = clock();
	    arr1 = drawLine(arr1,ed,color);
	gp_end = clock();
	gpu_time_used = ((double) (gp_end - gp_start)) / CLOCKS_PER_SEC;

	cp_start = clock();
	    arr2 = cp_drawLine(arr2,ed,color);
	cp_end = clock();
	cpu_time_used = ((double) (cp_end - cp_start)) / CLOCKS_PER_SEC;

   printf("cpu used: %f seconds\ngpu used: %f seconds\n",cpu_time_used,gpu_time_used);

	array_push(arr1,"gpu.ppm");
	array_push(arr2,"cpu.ppm");

	return 0;
}
