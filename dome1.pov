#version 3.7;
global_settings { assumed_gamma 1.0}

#include "colors.inc"
#include "textures.inc"
#include "shapes3.inc"
#include "stones.inc"

background { color White }

camera {
	fisheye
	location <0, 0, -0.1>
	up y
	right x
	angle 180
	look_at <0, 0, 1>
	translate <0,0,0>
	rotate <0,0,0>
	
}

/*camera {
	location <0, 0, -0.1>
	look_at <0, 0, 1>
	angle 140
	translate <0,0,0>
	rotate 90*pi/180.0*x
}*/

light_source {
	<0.0,0.0,0.0> color rgb <1.0, 1.0, 1.0>
	shadowless
}


#include "dome1.inc"
