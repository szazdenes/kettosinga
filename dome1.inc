#declare R = 1;
#declare deg_step = 20 * pi/180.0; //deg
#declare rot_step = 60 * pi/180.0; //deg

#declare R_inner = 10;
#declare start_rotpos = 0 * pi/180.0; //deg

#for (rot, start_rotpos, start_rotpos + 2*pi, rot_step)

	#declare coloumnCenterX = R_inner * cos(rot);
	#declare coloumnCenterY = R_inner * sin(rot);

	union{
		#for (deg, 0, 2*pi, deg_step)
	
			#declare cylinderUnitStartPosX = coloumnCenterX + R * cos(deg);
			#declare cylinderUnitStartPosY = coloumnCenterY + R * sin(deg);
			#declare cylinderUnitStartPosZ = 0;
			#declare cylinderUnitEndPosX = coloumnCenterX + R * cos(deg);;
			#declare cylinderUnitEndPosY = coloumnCenterY + R * sin(deg);;
			#declare cylinderUnitEndPosZ = 10;

			cylinder {
				<cylinderUnitStartPosX, cylinderUnitStartPosY, cylinderUnitStartPosZ>,     // Center of one end
				<cylinderUnitEndPosX, cylinderUnitEndPosY, cylinderUnitEndPosZ>,     // Center of other end
				0.20            // Radius
				texture { 
					pigment { color Grey }
				}
			}
	

		#end
	}

#end

difference{
	sphere{<0,0,0>, 12}
	sphere{<0,0,0>, 8}
	box{
		<12,12,0>
		<-12.01,-12.01,-12.01>
	}
	pigment{color Red}
	translate 10*z
}
