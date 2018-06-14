#version 3.7;
global_settings { assumed_gamma 1.0}

#include "textures.inc"
#include "colors.inc" 

sky_sphere {
	
	pigment {image_map {png "skygrad.png" map_type 1 interpolate 2} scale -1 rotate -90*x }
	pigment{ 
		bozo turbulence 0.75
		octaves 6  omega 0.7
		lambda 2  phase 0.15
		color_map {
			[0.00 color rgb <1,1,1>*0.95]
			[0.05 color rgb <1,1,1>*1.25]
			[0.15 color rgb <1,1,1>*0.85]
			[0.55 color rgbt<1,1,1,1>]
			[1.00 color rgbt<1,1,1,1>]
		} 
		translate< 3, 0,-1>
		scale<0.3, 0.4, 0.2>*3
		rotate <0,220,90>
	} 
}

#declare cam1 = camera {
	location <0, 0, 0.1>
	look_at <0, 0, 0>
	angle 100
	translate <0,15,65>
	rotate <80,0,135>
}

#declare cam2 = camera {
	fisheye
	location <0, 0, 0.1>
	up y
	right 1.*x
	angle 180
	look_at <0, 0, 1>
	translate <0,0,8>
	rotate <0,0,0>
}

camera{cam1}

light_source {
	<0.0,0.0,1000.0> color rgb <0.5, 0.5, 0.5>
	shadowless
}

light_source {
	<0.0,500.0,0.0> color rgb <1.0, 1.0, 1.0>
	shadowless
}

light_source {
	<0.0,0.0,8.0> color rgb <1.0, 1.0, 1.0>
	shadowless
}

//-------------------------inga parameters
#declare height = 56;
#declare grav = 9.81;
#declare time_step = 0.01;
#declare length1 = 23.5;
#declare length2 = 23.5;
#declare m1 = 1;
#declare m2 = 1;
#declare theta1_0 = 20;	//deg
#declare theta2_0 = 0;	//deg
#declare w1_0 = 0; //angular velocity
#declare w2_0 = 0;
//---------------------------------------

//----------------------pylon parameters
#declare Texture1 = texture{
	/*pigment{ color rgb<1,1,1>}
	finish { diffuse 0.9 phong 1}*/
	Brass_Valley scale 0.3
}
#declare Texture2 = texture{
	/*pigment{ color rgb<1,1,1>*0.7}
	finish { diffuse 0.9 phong 1}*/
	Rusty_Iron scale 0.3
}
#declare R1 = 0.30; // main radius
#declare R2 = 0.15; // diagonals radius
#declare W = 15.00-R1;// half width(outline!)
#declare H = 8.00;   // height   

#declare Nr = 0;     
#declare EndNr = 6; 
//-------------------------------------

//-----------------hill parameters
#declare HF_Res_X = 500; // number of points in x
#declare HF_Res_Y = 500; // number of points in y
//----------------------------------

#declare R = 20;
#declare height_platform = 7;

#include "env5.inc"
#include "inga.pov"

object{water}
union{
	object{circularBase}
	object{platform translate height_platform*z}
}
object{canoe rotate -20*z translate <30*cos(60*pi/180),30*sin(60*pi/180),1>}
object{canoe rotate 70*z translate <50*cos(160*pi/180),50*sin(160*pi/180),1>}
object{canoe rotate 40*z translate <30*cos(300*pi/180),30*sin(300*pi/180),1>}

object{pylon}

makeHills(HF_Res_X, HF_Res_Y, 1000*cos(150*pi/180), 1000*sin(150*pi/180))
makeHills(HF_Res_X, HF_Res_Y, 1000*cos(170*pi/180), 1000*sin(170*pi/180))
makeHills(HF_Res_X, HF_Res_Y, 1000*cos(210*pi/180), 1000*sin(190*pi/180))
makeHills(HF_Res_X, HF_Res_Y, 1000*cos(230*pi/180), 1000*sin(210*pi/180))
makeHills(HF_Res_X, HF_Res_Y, 1000*cos(250*pi/180), 1000*sin(230*pi/180))


