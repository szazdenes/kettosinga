#include "colors.inc"
#include "textures.inc"
#include "metals.inc"


#declare R = 1;
#declare deg_step = 20 * pi/180.0; //deg
#declare rot_step = 60 * pi/180.0; //deg

#declare R_inner = 10;
#declare start_rotpos = 0 * pi/180.0; //deg


#declare board = plane{
	<0, 0, 1>, 0
	pigment {
		checker color White, color Black 
	}
}

#declare coloumns = union{
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
    					pigment { White_Marble }
    				}
    			}
    		#end
    	}
    
    #end
    
    difference{
    	difference{
    		sphere{<0,0,0>, 11.5}
    		sphere{<0,0,0>, 8.5}
    		box{
    			<11.5,11.5,0>
    			<-11.51,-11.51,-11.51>
    		}
    	}
    	union{
    		#for (deg, 30*pi/180, 360*pi/180, 60*pi/180)
    		cylinder {< 0, 0, 0>, < 15*cos(deg), 15*sin(deg), 2>, 4}
    		cylinder {< 0, 0, 0>, < 15*cos(deg), 15*sin(deg), 8>, 4}
    		#end
    	}
    	
    	texture{ pigment{ White_Marble } }  
    	scale<1,1,0.5>
    	translate 10*z
    } 
}

#declare dome = union{
    union{
    	difference{
    		sphere{<0,0,0>, 12.5}
    		sphere{<0,0,0>, 12}
    		box{
    			<12.5,12.5,0>
    			<-12.51,-12.51,-12.51>
    		}
    		scale<1,1,0.5>
    	}
    	difference{
    		cylinder{<0,0,0>, <0,0,-5>, 12.5}
    		cylinder{<0,0,0>, <0,0,-5>, 12 open}
    	}
    	texture{ T_Copper_3A }   
    	translate 10*z
    }
    
}

 
union{
    object{coloumns}
    object{dome}    
    rotate 30*z
}

                  
object{board}