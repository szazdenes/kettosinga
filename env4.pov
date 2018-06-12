#version 3.7;
global_settings { assumed_gamma 1.0}

#include "textures.inc"
#include "colors.inc" 

sky_sphere {
    pigment {
       Blue_Sky
    }
}

/*fog { 
	fog_type   2
	distance   70
	color      White*0.75
	fog_offset 0.1
	fog_alt    1.5
	turbulence 1.8
}*/   

camera {
	location <0, 0, 0.1>
	look_at <0, 0, 0>
	angle 100
	translate <0,5,35>
	rotate <85,0,50>
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

//-----------pyramid parameters
#declare Top_Width = 3.00;   // half width at the top
#declare Base_Width = 14.50;  // half width at the base
#declare Total_Height = 14.50; // total height of the pyramid
#declare Number_of_Steps = 8; // number of steps
//-------------------------------------

#include "env4.inc"
#include "inga.pov"

object{board}
#declare R = 25;
wall_section(R, 0, 80, 5)
wall_section(R, 90, 80, 5)

object{hollow_pyramid rotate 20*z}
