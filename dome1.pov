#version 3.7;
global_settings { assumed_gamma 1.0}

#include "colors.inc"
#include "textures.inc"
#include "shapes3.inc"
#include "stones.inc"

background { color White }

camera {
	fisheye
	location <0, 0, 0>
	up y
	right x
	angle 180
	look_at <0, 0, 1>
}

light_source {
	<0.0,0.0,0.0> color rgb <1.0, 1.0, 1.0>
	shadowless
}

#include "dome1.inc"
