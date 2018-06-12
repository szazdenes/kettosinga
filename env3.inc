#include "colors.inc"
#include "textures.inc"
#include "shapes3.inc"
#include "shapes.inc"

#declare board = plane{
	<0, 0, 1>, 0
	pigment {
		checker color Black color White
	}
}

#local wall_height = 10;

#declare walls = difference{
	box{
		<1,1,0>
		<-1,-1,-1>
		hollow
	}
	box{
		<0.99,0.99,0.1>
		<-0.99,-0.99,-1>
	}
	texture{Glass}
	scale <12,12,wall_height>
	translate wall_height*z
}


//macro for bench

#macro Chair_s00 ( Chair__Height, // total height
                    Seat__Height, 
                   Chair__Half_Width, 
                   Chair__Feet_Radius, 
                 ) 

	#local CR = Chair__Feet_Radius; 
	#local CW = Chair__Half_Width - CR; 
	#local CH = Chair__Height - CR; 
	#local SH =  Seat__Height - CR; 

	#local SW = Chair__Half_Width ; 
	#local ST = 2*CR ; 

	union{ 
		union{
			// seat
			box { <-CW, 0.00, -CW>,< CW, 0, CW>  translate<0,SH,0> }  
			// front feet
			cylinder { <0,0,0>,<0,SH,0>, CR translate< CW,0,-CW> } 
			cylinder { <0,0,0>,<0,SH,0>, CR translate<-CW,0,-CW> }
			// frontside horizontal seat level
			cylinder { <-CW,0,  0>,< CW,0, 0>, CR  translate<0,SH, CW> }
			cylinder { <-CW,0,  0>,< CW,0, 0>, CR  translate<0,SH,-CW> }
			cylinder { <  0,0,-CW>,<  0,0,CW>, CR  translate< CW,SH,0> }
			cylinder { <  0,0,-CW>,<  0,0,CW>, CR  translate<-CW,SH,0> }
			// frontside horizontal seat level
			sphere{ < CW,SH,-CW>, CR  } 
			sphere{ <-CW,SH,-CW>, CR  } 
			// backside feet
			cylinder { <0,0,0>,<0,CH,0>, CR translate< CW,0, CW> }
			cylinder { <0,0,0>,<0,CH,0>, CR translate<-CW,0, CW> }
			// backside horizontal upper
			cylinder { <-CW,CH,0>,< CW,CH,0>, CR  translate <0,0,CW> }
			sphere{ < CW,CH, CW>, CR } 
			sphere{ <-CW,CH, CW>, CR } 
			// backside horizontal seat level
			sphere{ < CW,SH, CW>, CR } 
			sphere{ <-CW,SH, CW>, CR } 

		}

		// back
		object { // Round_Box(A, B, WireRadius, UseMerge)
			 Round_Box(<-SW,SH+(CH-SH)/2,CW-2*CR>,<SW,CH+CR,CW>, CR/2 , 0)  
			 scale<1,1,1>  rotate<0, 0,0> translate<0,0,0>
		       } 
		// seat
		object { // Round_Box(A, B, WireRadius, UseMerge)
			 Round_Box(<-SW,0,-SW>,<SW,2*CR,CW>, CR , 0)  
			 scale<1,1,1>  rotate<0, 0,0> translate<0,SH,0>
		       } 
		
	} 
#end

#local column_width = 1.5;
#local column_pos = 11.99-column_width;
#declare columns = union{
	Column_N_AB(4, <column_pos,column_pos,0>, <column_pos,column_pos,wall_height>, column_width)
	Column_N_AB(4, <column_pos,-column_pos,0>, <column_pos,-column_pos,wall_height>, column_width)
	Column_N_AB(4, <-column_pos,column_pos,0>, <-column_pos,column_pos,wall_height>, column_width)
	Column_N_AB(4, <-column_pos,-column_pos,0>, <-column_pos,-column_pos,wall_height>, column_width)
	texture{Yellow_Pine scale 0.5}
}

#declare bench = object{
	Chair_s00 ( 3.50, // Total_Chair_Height, 
                    1.75, // Seat_Height, 
                    5.0,// Chair_Half_Width 
                    0.3,// Chair_Feet_Radius,
                  ) 
        texture{ White_Marble scale 0.1} 
}

#declare cover = union{
	
	difference{	
		difference{
			cylinder{<0,1,0>, <0,-1,0>, 4}
			cylinder{<0,1,0>, <0,-1,0>, 3.99}
			box{<1.1,1.1,0>, <-1.1,-1.1,-1.1> scale 4}
			scale<3,12,1>
			translate wall_height*z			
		}
		sphere{<0,0,1> 10.01 scale<1,1,0.8> translate (wall_height+2)*z}
	}

	difference{
		sphere{<0,0,1> 10.01 scale<1,1,0.8> translate (wall_height+2)*z}
		sphere{<0,0,1> 10 scale<1,1,0.8> translate (wall_height+2)*z}
		difference{
			cylinder{<0,1,0>, <0,-1,0>, 4}
			box{<1.1,1.1,0>, <-1.1,-1.1,-1.1> scale 4}
			scale<3,12,1>
			translate wall_height*z			
		}
		box{<1,1,0>, <-1,-1,-1> scale 10.01 translate wall_height*z}
		
	}
	texture{Yellow_Pine scale 0.5}
}
