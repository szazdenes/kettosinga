#include "colors.inc"
#include "textures.inc"
#include "shapes3.inc"
#include "chair_s00.inc"

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
	texture{Glass2}
	scale <12,12,wall_height>
	translate wall_height*z
}

#local column_width = 1.5;
#local column_pos = 11.99-column_width;
#declare columns = union{
	Column_N_AB(4, <column_pos,column_pos,0>, <column_pos,column_pos,wall_height>, column_width)
	Column_N_AB(4, <column_pos,-column_pos,0>, <column_pos,-column_pos,wall_height>, column_width)
	Column_N_AB(4, <-column_pos,column_pos,0>, <-column_pos,column_pos,wall_height>, column_width)
	Column_N_AB(4, <-column_pos,-column_pos,0>, <-column_pos,-column_pos,wall_height>, column_width)
	texture{Yellow_Pine}
}

#declare bench = object{
	Chair_s00 ( 3.50, // Total_Chair_Height, 
                    1.75, // Seat_Height, 
                    5.0,// Chair_Half_Width 
                    0.3,// Chair_Feet_Radius,
                  ) //---------------------------- 
        texture{ White_Marble } 
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
	texture{Yellow_Pine}
}
