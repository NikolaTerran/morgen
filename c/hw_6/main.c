#include "engine.h"

/*random snipet
	filling in polygons by drawing successive horizontal or vertial lines
	* find bottom, top && middle vertices
	* y:by -> ty;
	* y += 1
*/

/*random snippet #2
  I = Ambient + Diffuse + Specular
  Ambient
    * reflects ambient light equally in all directions
    A: color of ambient light
      (grayscale or rgb)
    Ka: constant of ambient reflection
      (0,1 or 3[0,1] values)

    Ambient = AKa

  Diffuse reflection
  * Ip : color of point light sources
  * Kd : constant of diffuse reflection
  * REFLECTS LIGHT from a single point source(p)
    equally in all directions.

  * Diffuse reflections is inversly proportional to 0 (cos0)
  * cos0 = N(vector)

  *cos0 = n(vector) * L(vector)

*/

int main(){
printf("Please read README.md first\n");
printf("Please also read the commit message\n");

canvas_init();

struct Matrix point;
point = mx_init(point,0);


int color[3];
color[0] = 0;
color[1] = 0;
color[2] = 0;

struct Matrix poly;
poly = mx_init_p(poly,0);

//poly = mx_addsphere(poly,0,0,0,200);

poly = mx_addsphere(poly,120,150,0,75);
poly = mx_addtorus(poly,0,-100,0,50,100);
//poly = mx_rotate(poly,0,0.5);

poly = mx_addbox(poly,-200,100,0,100,100,100);
poly = mx_rotate(poly,0,0.5);
poly = mx_rotate(poly,1,0.5);
mx_export(poly,color);


//mx_export(edge,"ok.ppm");

printf("hi\n");
canvas_push("hi.ppm");

return 0;


}
