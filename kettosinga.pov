#version 3.7;
global_settings { assumed_gamma 1.0}

#include "colors.inc"
#include "textures.inc"
#include "shapes3.inc"
#include "stones.inc"

camera {
	location <0, 0, 0.1>
	look_at <0, 0, 0>
	angle 100
	translate <0,5,25>
	rotate <90,0,45>
}


background { color White }
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


#declare height = 20;
#include "dome1.inc"

#declare grav = 9.81;
#declare time_n = clock;
#declare time_step = 0.01;

#declare length1 = 8;
#declare length2 = 8;
#declare m1 = 1;
#declare m2 = 1;
#declare theta1_0 = 50;	//deg
#declare theta2_0 = 0;	//deg

#declare w1_0 = 0; //angular velocity
#declare w2_0 = 0;

#declare theta1 = theta1_0 * pi/180.0;  //rad
#declare theta2 = theta2_0 * pi/180.0;	//rad
#declare w1 = w1_0;
#declare w2 = w2_0;

#include "kettosinga.inc"

#declare startPos1x = 0;
#declare startPos1y = 0;
#declare endPos1x = startPos1x + length1 * sin(theta1);
#declare endPos1y = startPos1y - length1 * cos(theta1);
#declare startPos2x = endPos1x;
#declare startPos2y = endPos1y;
#declare endPos2x = startPos2x + length2 * sin(theta2);
#declare endPos2y = startPos2y - length2 * cos(theta2);

union{
	cylinder {
		<startPos1x, 0, height + startPos1y>,     // Center of one end
		<endPos1x, 0, height + endPos1y>,     // Center of other end
		0.05            // Radius
		texture { 
			pigment { color Black }
		}
	}
	sphere{
		<endPos1x, 0, height + endPos1y>,
		0.5
		texture {
			pigment { color Red }			
		}
	}

	cylinder {
		<startPos2x, 0, height + startPos2y>,     // Center of one end
		<endPos2x, 0, height + endPos2y>,     // Center of other end
		0.05            // Radius
		texture { 
			pigment { color Black }
		}
	}
	sphere{
		<endPos2x, 0, height + endPos2y>,
		0.5
		texture {
			pigment { color Blue }			
		}
	}
}

