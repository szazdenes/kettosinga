#version 3.7;
global_settings { assumed_gamma 1.0}

#include "textures.inc"

sky_sphere {
    pigment {
       Blue_Sky
    }
}

/*camera {
	location <0, 0, 0.1>
	look_at <0, 0, 0>
	angle 100
	translate <0,5,25>
	rotate <90,0,45>
}*/

//light_source{ <300, 300, -1000> White }

camera {
	fisheye
	location <0, 0, 0.1>
	up y
	right 1.*x
	angle 180
	look_at <0, 0, 1>
	translate <0,0,0>
	rotate <0,0,0>
}


light_source {
	<0.0,0.0,0.0> color rgb <1.0, 1.0, 1.0>
	shadowless
}

#include "dome1.inc"
#include "inga.inc"

union{
    object{coloumns}
    object{dome}    
    rotate 30*z
}
               
object{board}
