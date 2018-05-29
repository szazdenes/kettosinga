#version 3.7;
global_settings { assumed_gamma 1.0}

#include "textures.inc"

sky_sphere {
    pigment {
       Blue_Sky
    }
}

sphere {
	0*x,1800
	pigment {
		image_map {png "volgy2W.png" map_type 1 interpolate 2} 
		scale -1
		rotate -90*x 
	}
	hollow
	finish {ambient 0.2 diffuse 0.0}
}

camera {
	location <0, 0, 0.1>
	look_at <0, 0, 0>
	angle 100
	translate <0,5,25>
	rotate <90,0,45>
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

#include "dome2.inc"
#include "inga.pov"
#include "exgrass2.pov"

object{
	dome_net
	translate 5*z
}             
object{board2}
