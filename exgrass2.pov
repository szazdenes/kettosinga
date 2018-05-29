// ======================================
// Example of use of the Makegrass macro
// -----------------------------------------
// Made for Persistence of vision 3.6
// ==========================================  
// Copyright 1999-2004 Gilles Tran http://www.oyonale.com
// -----------------------------------------
// This work is licensed under the Creative Commons Attribution License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by/2.0/ 
// or send a letter to Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.
// You are free:
// - to copy, distribute, display, and perform the work
// - to make derivative works
// - to make commercial use of the work
// Under the following conditions:
// - Attribution. You must give the original author credit.
// - For any reuse or distribution, you must make clear to others the license terms of this work.
// - Any of these conditions can be waived if you get permission from the copyright holder.
// Your fair use and other rights are in no way affected by the above. 
// ==========================================  
// Freshly cut grass
// --------------------------------------
#include "colors.inc"
#include "mgrass.inc"

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
#declare fname = "fgrass2.inc"     // name of the mesh file to create

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
	texture{T_Grass scale 40}
	rotate <95, 0, 45>
	translate <0,-6,0>	
}  
