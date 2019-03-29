#include "engine.h"

int main(void){
	struct Array arr1;
	arr1 = array_init(arr1);
	

	struct Edge ed;
	ed = ed_init(ed,4,0);
	//edge = ed_adde(edge,50,50,0,400,400,0);
	//edge = ed_adde(edge,100,100,0,450,450,0);
	//edge = ed_adde(edge,150,150,0,500,500,0);

	int color[3];
	color[0] = 0;
	color[1] = 255;
        color[2] = 0;
/*
    arr1 = DL(arr1,0,0,249,0,color);
    arr1 = DL(arr1,0,0,-250,0,color);
    arr1 = DL(arr1,0,0,0,250,color);
    arr1 = DL(arr1,0,0,0,-249,color);
*/
    ed = ed_adde(ed,0,0,0,0,-249,0);
    ed = ed_adde(ed,0,0,0,249,0,0);
    ed = ed_adde(ed,0,0,0,-250,0,0);
    ed = ed_adde(ed,0,0,0,0,250,0);

    ed = ed_adde(ed,0,0,0,249,250,0);
    ed = ed_adde(ed,0,0,0,249,-249,0);
    ed = ed_adde(ed,0,0,0,-249,250,0);
    ed = ed_adde(ed,0,0,0,-250,-249,0);

/*
    arr1 = DL(arr1,-250,0,249,250,color);
    arr1 = DL(arr1,-250,0,249,-249,color);
    arr1 = DL(arr1,0,250,-250,-249,color);
    arr1 = DL(arr1,0,250,249,-249,color);
    arr1 = DL(arr1,249,0,-250,250,color);
    arr1 = DL(arr1,249,0,-250,-249,color);
    arr1 = DL(arr1,0,-249,-250,250,color);
    arr1 = DL(arr1,0,-249,249,250,color);
*/
   arr1 = drawLine(arr1,ed,color);
	//arr_1 = arr_set(arr_1,50,50,color);
	//arr_1 = arr_set(arr_1,-50,50,color);
	//arr_1 = arr_set(arr_1,-50,-49,color);
	//arr_1 = arr_set(arr_1,50,-49,color);

	array_push(arr1,"image.ppm");
	return 0;
}
