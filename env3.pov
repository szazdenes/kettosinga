#version 3.7;
global_settings { assumed_gamma 1.0}

#include "textures.inc"

sky_sphere {
    pigment {
       Blue_Sky
    }
}

camera {
	location <0, 0, 0.1>
	look_at <0, 0, 0>
	angle 100
	translate <0,7,30>
	rotate <85,0,90>
}

//light_source{ <300, 300, -1000> White }

/*camera {
	fisheye
	location <0, 0, 0.1>
	up y
	right 1.*x
	angle 180
	look_at <0, 0, 1>
	translate <0,0,0>
	rotate <0,0,0>
}*/

light_source {
	<0.0,0.0,0.0> color rgb <1.0, 1.0, 1.0>
	shadowless
}

//-------------------------inga parameters
#declare height = 20;
#declare grav = 9.81;
#declare time_step = 0.01;
#declare length1 = 9;
#declare length2 = 9;
#declare m1 = 1;
#declare m2 = 1;
#declare theta1_0 = 40;	//deg
#declare theta2_0 = 0;	//deg
#declare w1_0 = 0; //angular velocity
#declare w2_0 = 0;
//---------------------------------------

#include "env3.inc"
#include "inga.pov"

object{board}
union{
	object{walls}
	object{cover}
}
object{columns}
object{
	bench
	scale <1,1,0.3> rotate<90,0,0> translate< 0.00,-10.00,0.00>
}
object{
	bench
	scale <1,1,0.3> rotate<90,0,180> translate< 0.00,10.00,0.00>
}
object{
	bench
	scale <1,1,0.3> rotate<90,0,90> translate< 10.00,0.00,0.00>
}
object{
	bench
	scale <1,1,0.3> rotate<90,0,-90> translate< -10.00,0.00,0.00>
}
