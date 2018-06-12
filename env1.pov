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
	translate <0,5,20>
	rotate <100,0,45>
}

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
#declare height = 14.25;
#declare grav = 9.81;
#declare time_step = 0.01;
#declare length1 = 7;
#declare length2 = 7;
#declare m1 = 1;
#declare m2 = 1;
#declare theta1_0 = 40;	//deg
#declare theta2_0 = 0;	//deg
#declare w1_0 = 0; //angular velocity
#declare w2_0 = 0;
//---------------------------------------

#include "env1.inc"
#include "inga.pov"

union{
	object{coloumns}
	object{dome}    
	rotate 30*z
}             
object{board}
