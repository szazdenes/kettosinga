#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"
#include "stones.inc"

#declare board = plane{
	<0, 0, 1>, 0
	texture{ pigment{ color rgb<0.35,0.65,0.0>*0.45 }
                 normal { bumps 0.75 scale 0.015 }
                 finish { phong 0.1 }
               } 
}

#declare coloumn_wall = difference{
	#local r_cyl = 1.0;
	#local height = 15;
	cylinder {
		<0, 0, 0>,     // Center of one end
		<0, 0, height>,     // Center of other end
		r_cyl            // Radius	
	}
	
	#for(deg, 0, 360*pi/180, 20*pi/180)
		cylinder {
			<r_cyl*cos(deg), r_cyl*sin(deg), 0>,     // Center of one end
			<r_cyl*cos(deg), r_cyl*sin(deg), height>,     // Center of other end
			0.15            // Radius	
		}
	#end
	texture { 
		T_Stone2 
		scale 0.1
		finish { phong 0.1 }
	}
}

#macro wall_section(R, section_start, section_length, step)
	#for(pos, section_start*pi/180, (section_start+section_length)*pi/180, step*pi/180)
		object{coloumn_wall translate <R*cos(pos), R*sin(pos), 0>}
	#end
#end

//-------------------create pyramid

#declare hollow_pyramid = union{
	#local Step_Height = Total_Height/Number_of_Steps;
	#local Step_Width  = (Base_Width-Top_Width)/(Number_of_Steps-1);

	#local Nr = 0;     
	#local EndNr = Number_of_Steps; 
	#while (Nr < EndNr-1)
		#local P_Width = Base_Width-Step_Width*Nr;
		#local P_Height = Step_Height;
		#local D = P_Width - (Base_Width-Step_Width*(Nr+1)); 
		difference{
			box{ <-P_Width, -P_Width, 0>,< P_Width, P_Width, P_Height>
			}
			box{ <-P_Width+D, -P_Width+D, -0.001>,< P_Width-D, P_Width-D, P_Height+0.001>
			}
			translate<0,0,Total_Height-(EndNr-Nr)*Step_Height>
			texture{
				/*pigment{ color rgb<0.9,0.78,0.6>}
				normal {
					pigment_pattern{ brick
					color rgb 0.2,
					color rgb 0.8
					scale 0.135
					translate<0,0,0>
					rotate<0,0,0>
				} 
				0.35 
				} 
				finish { diffuse 0.9 phong 0.1}*/ 
				NBbeerbottle
			}
		}
		#local Nr = Nr + 1;
	#end
	#local Nr = EndNr-1;
	#local P_Width = Base_Width-Step_Width*Nr;
	#local P_Height = Step_Height;
	#local D = P_Width - (Base_Width-Step_Width*(Nr+1)); 
	difference{
		box{ <-P_Width, -P_Width, 0>,< P_Width, P_Width, P_Height>
		}
		box{ <-P_Width+D, -P_Width+D, -0.001>,< P_Width-D, P_Width-D, P_Height-0.25>
		}
		translate<0,0,Total_Height-(EndNr-Nr)*Step_Height>
		texture{
			/*pigment{ color rgb<0.9,0.78,0.6>}
			normal {
				pigment_pattern{ brick
				color rgb 0.2,
				color rgb 0.8
				scale 0.135
				translate<0,0,0>
				rotate<0,0,0>
			} 
			0.35 
			} 
			finish { diffuse 0.9 phong 0.1}*/
			NBbeerbottle 
		}
	} 
}

//-------------------------create tree textures
#declare Stem_Texture = 
	texture{ pigment{ color rgb< 0.70, 0.56, 0.43>*0.25 } 
		normal { bumps 1.00 scale <0.025,0.075,0.025> }
		finish { phong 0.2 reflection 0.00}         
	} 

#declare Leaves_Texture_1 = 
	texture{ pigment{ color rgbf< 0.27, 0.36, 0.0, 0.1>*1.4 }   
		normal { bumps 0.15 scale 0.05 }
		finish { phong 1 reflection 0.00}
	} 

#declare Leaves_Texture_2 = 
	texture{ pigment{ color rgbf< 0.25, 0.35, 0.0, 0.1>*1.4 }   
		normal { bumps 0.15 scale 0.05 }
		finish { phong 0.2 reflection 0.00}
	}
