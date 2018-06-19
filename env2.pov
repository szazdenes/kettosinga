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

//-------------------------inga parameters
#declare height = 14.25;
#declare grav = 9.81;
#declare time_step = 0.01;
#declare length1 = 7;
#declare length2 = 7;
#declare m1 = 1;
#declare m2 = 1;
#declare theta1_0 = 40;	//deg
#declare theta2_0 = 0;	//deg
#declare w1_0 = 0; //angular velocity
#declare w2_0 = 0;
//---------------------------------------

#include "env2.inc"
#include "inga.pov"

object{
	dome_net
	translate 5*z
}             
object{board2}

//---------------------------set grass parameters

#include "colors.inc"

#declare Blanc1=rgb<0.90,0.81,0.81>;

#declare Green1=rgb<230,170,50>/255;
#declare Green2=rgb<110,160,8>/255;
#declare Green1=rgb<0.4,1,0.3>*0.4;
#declare Green2=rgb<60,160,8>/255;
// --------------------------------------
// Grass texture
// --------------------------------------
#declare P_Spotted =pigment {
spotted
    color_map {
        [0.0, 0.2   color Tan*0.1 color Tan*0.4]
        [0.2, 0.3   color Tan*0.4 color Green1]
        [0.3, 1.01   color Green1 color Green1*1.2]
    }
}

#declare P_Earth =pigment {
    spotted
    color_map {
        [0 color Tan*0.3]
        [0.6 color Tan*0.3]
        [0.6 color Green1*0.4]
        [1   color Green1*0.4]
    }
}
#declare P_Green=pigment{Green2*1.3}
//#declare P_Spotted=pigment{Red}
//#declare P_Earth=pigment{Blue}
#declare T_Grass=texture {                  
    pigment {
        gradient y
        turbulence 0.2
        pigment_map {                                
            [0.0 P_Earth]
            [0.3 P_Green]
            [0.9 P_Spotted]
            [1.00 P_Earth]
        }
    }

    finish{ambient 0.01 diffuse 0.7 specular 0.2 roughness 0.015}
    scale <0.001,1,0.001>
 
} 
// --------------------------------------
// Patch parameters
// --------------------------------------
// Final number of triangles = nBlade x nBlade x segBlade x 2 (or 4 if dofold = true)
// --------------------------------------
#declare lPatch=80;               // size of patch
#declare nBlade=60;                // number of blades per line (there will be nBlade x nBlade blades)
//#declare nBlade=4;                // number of blades per line (there will be nBlade x nBlade blades)
#declare ryBlade = 0;            // initial y rotation of blade
#declare segBlade= 10;            // number of blade segments
#declare lBlade = 1.5;             // length of blade
#declare wBlade = 0.15;            // width of blade at start
#declare wBladeEnd = 0.01;         // width of blade at the end
#declare doSmooth=true;          // true makes smooth triangles
#declare startBend = <0,1,0.3>;   // bending of blade at start (<0,1,0>=no bending)
#declare vBend = <0,1,0>;         // force bending the blade (<0,1,1> = 45°)
#declare pwBend = 4;              // bending power (how slowly the curve bends)
#declare rd = 459;                // seed
#declare stdposBlade = 1;         // standard deviation of blade position 0..1
#declare stdrotBlade = 360;       // standard deviation of rotation
#declare stdBlade = 1.2;           // standard deviation of blade scale
#declare stdBend = 3;            // standard deviation of blade bending
#declare dofold = true;          // true creates a central fold in the blade (twice more triangles)
#declare dofile = true;          // true creates a mesh file
#declare fname = "fgrass.inc"     // name of the mesh file to create

// --------------------------------------
// Prairie parameters
// --------------------------------------
#declare nxPrairie=80;             // number of patches for the first line
#declare addPatches=15;            // number of patches to add at each line
#declare nzPrairie=45;             // number of lines of patches
#declare rd=seed(779);            // random seed
#declare stdscale=1;              // stddev of scale
#declare stdrotate=1;             // stddev of rotation
#declare doTest=false;            // replaces the patch with a sphere

// --------------------------------------
// Create the patch and the prairie
// --------------------------------------
#if (dofile=true) // if the patch is already created, turn off the next line
    MakeGrassPatch(lPatch,nBlade,ryBlade,segBlade,lBlade,wBlade,wBladeEnd,doSmooth,startBend,vBend,pwBend,rd,stdposBlade,stdrotBlade,stdBlade,stdBend,dofold,dofile,fname)
    #declare objectPatch=#include fname
#else        
    #declare objectPatch=object{MakeGrassPatch(lPatch,nBlade,ryBlade,segBlade,lBlade,wBlade,wBladeEnd,doSmooth,startBend,vBend,pwBend,rd,stdposBlade,stdrotBlade,stdBlade,stdBend,dofold,dofile,fname)}
#end        

object{MakePrairie(lPatch,nxPrairie,addPatches,nzPrairie,objectPatch,rd,stdscale,stdrotate,doTest)
	texture{T_Grass scale 1}
	rotate <90, 0, 45>
	translate <0,-4, 0>	
}  
