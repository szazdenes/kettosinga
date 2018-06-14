#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"

#declare water = plane{
	<0, 0, 1>, 0
	material {
		texture {
			pigment {
				color rgb <0.4, 0.7, 0.9>
			}
			finish {
				ambient 0.0
				diffuse 0.0

				reflection {
					0.0, 1.0
					fresnel on
				}

				specular 0.4
				roughness 0.003
			}
			normal{ pigment_pattern{
				crackle
				colour_map { [0, rgb 0]
				[1, rgb 1] }
				turbulence 1.7
				translate <0,0,1>
				}
			0.5
			}
			scale <2.0,1,0.3>*2
			rotate<0,10,0>
			
		}
		interior {
			ior 1.3
		}
	}	
}

#declare trunk = object{
	isosurface { 
		function{-f_cylindrical(x,y,z)-f_agate(x*5,y*1.43,z*5)/8 + 0.2}
		threshold 0
		contained_by{box {<-1,-1,-1>,<1,1,1>}}
		max_gradient 3
		pigment {  
			wood
			color_map{
				[0.0 color rgb 2*<0.5019, 0.25, 0>/2.3]
				[1.0 color rgb 2*<0.5019, 0.2, 0>/3.5]
			}
			scale 0.08
			rotate x*90
			rotate y*30
			turbulence 0.06
			phase pi/2
		}
		finish{reflection 0.001 diffuse 0.4 crand .3 ambient 0}
	}
	rotate <90,0,0>
	scale<1.5,1.5,7>
}

#declare circularBase = union{
	#for(deg, 0, 360*pi/180, 60*pi/180)
		object{trunk translate<R*cos(deg), R*sin(deg), 0>}
	#end

}

#declare platform = object{
	cylinder{<0,0,0>,<0,0,1> 25
		texture{
			pigment {  
				wood
				color_map{
					[0.0 color rgb 2*<0.5019, 0.25, 0>/2.3]
					[1.0 color rgb 2*<0.5019, 0.2, 0>/3.5]
				}
				scale 0.08
				rotate x*90
				rotate y*30
				turbulence 0.06
				phase pi/2
			}
			finish{reflection 0.001 diffuse 0.4 crand .3 ambient 0}
		}
	}
}

#declare Canoe_outside = object{
	sphere {<0,0,0>,1 scale <3,1.5,1> rotate<0,0,0> translate<0,0.5,0> }
}

#declare canoe = union{
	intersection{
		object{ Canoe_outside }
		object{ Canoe_outside scale <0.98,0.85,0.94>  inverse}
		sphere {<0,0,0>,1 scale <2.5,1,20> rotate<0,0,0> translate<0,1.3,0>  inverse}
		texture{ 
			pigment{ color White*1.1}
			finish { phong 1}
		}
	}
	intersection{  
		object{ 
			Canoe_outside
			texture{ 
				pigment{ color White*1.1}
				finish { phong 1}
			}
		}
		union{
			box {<-0.20,0,-1>,<0.20,0.05,1> rotate<0,0,  0> translate< 0.0,0.21,0>}
			box {<-0.20,0,-1>,<0.20,0.05,1> rotate<0,0,-10> translate<-2.0,0.40,0>}
			box {<-0.20,0,-1>,<0.20,0.05,1> rotate<0,0, 10> translate< 2.0,0.40,0>}
			texture{ 
				pigment{ Dark_Wood scale 0.05}
				finish { phong 1}
			}
		}	
	}
	intersection{
		object{Canoe_outside}
		box {<-2.8,-0.1,-1>,<2.8,0.0,1>}
		texture{ 
			pigment{ color White*1.1}
			finish { phong 1}
		}
	}
	rotate 90*x
	scale 5
}

#declare canoe_deck = intersection{
	object{Canoe_outside}
	box {<-2.8,-0.1,-1>,<2.8,0.0,1> 
		texture{ 
			pigment{ color White*1.1}
			finish { phong 1}
		}
	}
	rotate 90*x
	scale 5
}

//-----------------create pylon
#macro Square_Quart (R1_, W_ ) 
	union{ 
		cylinder {<-W_,0,0>,<W_,0,0>,R1_ translate<0,0,-W_>}
		sphere   {<0,0,0>,R1_   translate<W,0,-W_>} 
	}
#end 

#macro Square (R10, W0) 
	union{  
		object{ Square_Quart(R10, W0) rotate<0,0*90,0>}
		object{ Square_Quart(R10, W0) rotate<0,1*90,0>}
		object{ Square_Quart(R10, W0) rotate<0,2*90,0>}
		object{ Square_Quart(R10, W0) rotate<0,3*90,0>}
	}
#end 

#macro Vertical_Element (R10, R20, W0, H0) 
	union{ 
		cylinder {<0,0,0>,<0,H0,0>,R10 translate<-W0,0,-W0>}
		// diagonal:
		cylinder{<-W0,0,0>,<W0,H0,0>,R20 translate<0,0,-W0+R20> }
		cylinder{<W0,0,0>,<-W0,H0,0>,R20 translate<0,0,-W0-R20> }
	}
#end 

#macro Element_4 (R11, R21, W1, H1)
union{ 
	object{ Square (R11, W1)}
	//vertical:
	object{ Vertical_Element(R11,R21,W1,H1) rotate<0,0*90,0>}
	object{ Vertical_Element(R11,R21,W1,H1) rotate<0,1*90,0>}
	object{ Vertical_Element(R11,R21,W1,H1) rotate<0,2*90,0>}
	object{ Vertical_Element(R11,R21,W1,H1) rotate<0,3*90,0>}
	translate<0,R1,0>}
#end 

#declare pylon = union{
	#while (Nr< EndNr) 
		object{ 
			Element_4(R1, R2, W, H)  texture{Texture1}
			translate<0,Nr*H,0>
		} 
		#declare Nr = Nr + 1;  

	#end 
	object{ 
		Square (R1, W)   texture{Texture1}
		translate<0,Nr*H+R1,0>
	}
	box {<-1,0,-1>,< 1,0.05,1> scale <W+0.1,1,W+0.1> texture{Texture1} translate (EndNr*H+R1)*y} 
	rotate 90*x
	translate<0,0,8>
	 
}

//----------------------hills
#declare SF = 
	function {
		pigment { 
			boxed 
			color_map {
				[0.0, color 0.0 ]
				[0.5, color 0.8 ]
				[1.0, color 1.0 ]
			} 
			scale <0.5,1,0.5>
			translate<0.5,0,0.5>
		} 
	} 

#declare HF_Function   =  function(x, y, z)
{ 1+f_snoise3d(x*10,y*10,z*10)*0.30   * SF(x,y,z).gray }

#declare HF_Amplitude    = 0.5;
#declare D = 0.00001;

#macro makeHills(HF_Res_X, HF_Res_Y, Pos_X, Pos_Y)
	union{ 
		intersection{
			height_field{
				function HF_Res_X, HF_Res_Y { HF_Function(x,0,y) * HF_Amplitude }
				translate<0,D-0.4 ,0>
			}
			box{ <D,-0.10,D>,<1-D,0.2-D,1-D>}
			translate<0,-0.10,0>
		}	
		
		texture { 
			pigment{ color rgb <1.00,0.95,0.8>}
			normal { bumps 0.75 scale 0.0025  }
			finish { phong 0.1 }
			scale 0.3 
		}
	
		rotate 90*x
		scale<500,500,1500> 
		translate<Pos_X,Pos_Y,0>
	}
#end
