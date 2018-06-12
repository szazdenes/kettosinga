#include "colors.inc"
#include "textures.inc"

#declare board2 = plane{
	<0, 0, 1>, 0
	pigment {
		granite
		turbulence 3
		color_map {
			[0.000 color rgb <0.5, 0.5, 0.2>]
			[0.25 color rgb <0.7, 1, 0.2>]
			[0.5 color rgb <1, 0.4, 0.2>]
			[0.75 color rgb <.5, 0.9, 0.2>]
			[1 color rgb <0.3, 0.9, 0.2>]
		}
		scale 0.035
	}
}

//basic values
#declare node_rad=0.1;
#declare link_rad=0.1;
#declare dome_rad=9.25;
#declare dome_rec_depth=3;

//recursive geodesic triangle subdivision
#macro tri1(a,b,c,depth)
	#if (depth < dome_rec_depth)
		#local ab= vnormalize(a+b)*dome_rad;
		#local bc= vnormalize(b+c)*dome_rad;
		#local ca= vnormalize(c+a)*dome_rad;
		tri1(bc,ca,ab,depth+1)
		tri1(a,ab,ca,depth+1)
		tri1(ab,b,bc,depth+1)
		tri1(ca,bc,c,depth+1)
	#else
		sphere{a, node_rad}
		sphere{c, node_rad}
		cylinder{a,b,link_rad}
		cylinder{b,c,link_rad}
		cylinder{c,a,link_rad}
	#end
#end

//declare corners of octahedron
#declare v1=-x * dome_rad;
#declare v2=-y * dome_rad;
#declare v3= x * dome_rad;
#declare v4= y * dome_rad;
#declare v5= z * dome_rad;
#declare v6=-z * dome_rad;

#declare dome_net = union{
    tri1(v1,v2,v5,0)
    tri1(v2,v3,v5,0)
    tri1(v3,v4,v5,0)
    tri1(v4,v1,v5,0)
    tri1(v1,v2,v6,0)
    tri1(v2,v3,v6,0)
    tri1(v3,v4,v6,0)
    tri1(v4,v1,v6,0)
    pigment{Dark_Wood scale 0.3}
    finish{specular 1}
}

//macro for grass simulation

#macro MakeBlade(doSmooth,posBlade,rotBlade,segBlade,lBlade,xBladeStart,xBladeEnd,zBladeStart,startBend,vBend,pwBend,dofold,dofile)
	#local lsegBlade=lBlade/segBlade;
	#if (dofold=true)
		#local nI=3;
	#else
		#local nI=2;
	#end                
	#local nJ=segBlade+1;
	#local nP=nI*nJ;
	#local P=array[nP]
	#local N=array[nP]  
	#local pBlade=<0,0,0>;              
	#local Count=0;                                       
	#local xBlade=xBladeStart;
	#local zBlade=zBladeStart;
	#if (dofold=true)
		#local P[0]=vaxis_rotate(-x*xBlade,y,rotBlade)+posBlade;
		#local P[1]=vaxis_rotate(z*zBlade,y,rotBlade)+posBlade;
		#local P[2]=vaxis_rotate(x*xBlade,y,rotBlade)+posBlade;
	#else
		#local P[0]=vaxis_rotate(-x*xBlade,y,rotBlade)+posBlade;
		#local P[1]=vaxis_rotate(x*xBlade,y,rotBlade)+posBlade;

	#end
	#local Count=1; 
	#local pBlade=vnormalize(startBend)*lsegBlade;
	// --------------------------------------
	// Fills the array of points
	// --------------------------------------
	#while (Count<nJ)          
		#local tBlade=Count/segBlade;
		// This is where the blade shape is defined
		#local pBlade=pBlade+lsegBlade*vnormalize(vnormalize(pBlade)+ vBend*pow(tBlade,pwBend));
		#local xBlade=xBladeStart+tBlade*(xBladeEnd-xBladeStart);
		#if (dofold=true)
		        #local zBlade=zBladeStart*(1-tBlade);
		        #local P[Count*nI]=vaxis_rotate(pBlade-x*xBlade,y,rotBlade)+posBlade;
		        #local P[Count*nI+1]=vaxis_rotate(pBlade+z*zBlade,y,rotBlade)+posBlade;
		        #local P[Count*nI+2]=vaxis_rotate(pBlade+x*xBlade,y,rotBlade)+posBlade;
		#else
		        #local P[Count*nI]=vaxis_rotate(pBlade-x*xBlade,y,rotBlade)+posBlade;
		        #local P[Count*nI+1]=vaxis_rotate(pBlade+x*xBlade,y,rotBlade)+posBlade;
		#end
		#local Count=Count+1;        
	#end
	// --------------------------------------
	// Calculates normals if doSmooth = true
	// --------------------------------------
	#if (doSmooth=true)
	#local N = array[nP] // Normales
	#local q=0;
	#while (q<nP)
	#local i=mod(q,nI);#local j=(q-i)/nI;
	#local V0 = q-nI-1;#if (i=0) #local V0=-1; #end
	#local V1 = q-nI;
	#local V2 = q-nI+1;#if (i=nI-1) #local V2=-1; #end
	#local V3 = q-1;#if (i=0) #local V3=-1; #end
	#local V4 = q;
	#local V5 = q+1;#if (i=nI-1) #local V5=-1; #end
	#local V6 = q+nI-1;#if (i=0) #local V6=-1; #end
	#local V7 = q+nI;
	#local V8 = q+nI+1;#if (i=nI-1) #local V8=-1; #end

	#if (j=0) #local V0=-1;#local V1=-1;#local V2=-1;#end
	#if (j=nJ-1) #local V6=-1;#local V7=-1;#local V8=-1; #end

	#local N[q]=<0,0,0>;
	#local k=0;
	#if (V5>-1 & V8>-1) #local N[q]=N[q]+vcross(P[V4]-P[V5],P[V8]-P[V4]);#local k=k+1;#end
	#if (V2>-1 & V5>-1) #local N[q]=N[q]+vcross(P[V4]-P[V2],P[V5]-P[V4]);#local k=k+1;#end
	#if (V1>-1 & V2>-1) #local N[q]=N[q]+vcross(P[V4]-P[V1],P[V2]-P[V4]);#local k=k+1;#end
	#if (V0>-1 & V1>-1) #local N[q]=N[q]+vcross(P[V4]-P[V0],P[V1]-P[V4]);#local k=k+1;#end
	#if (V3>-1 & V0>-1) #local N[q]=N[q]+vcross(P[V4]-P[V3],P[V0]-P[V4]);#local k=k+1;#end
	#if (V6>-1 & V3>-1) #local N[q]=N[q]+vcross(P[V4]-P[V6],P[V3]-P[V4]);#local k=k+1;#end
	#if (V7>-1 & V6>-1) #local N[q]=N[q]+vcross(P[V4]-P[V7],P[V6]-P[V4]);#local k=k+1;#end
	#if (V8>-1 & V7>-1) #local N[q]=N[q]+vcross(P[V4]-P[V8],P[V7]-P[V4]);#local k=k+1;#end
	#local N[q]=N[q]/k;
	#local q=q+1;#end
	#end
	// --------------------------------------
	// Writes the triangles
	// --------------------------------------

	#local q=0;
	#while (q<(nI*(nJ-1)-1))
	#local i=mod(q,nI);
	#local j=(q-i)/nI;
	#if (i <nI-1)
		#if (doSmooth=true)
		        #if (dofile=true)
		                #write(filehandle,"smooth_triangle{<",P[q].x,",",P[q].y,",",P[q].z,">,<",N[q].x,",",N[q].y,",",N[q].z,">,<",P[q+1].x,",",P[q+1].y,",",P[q+1].z,">,<",N[q+1].x,",",N[q+1].y,",",N[q+1].z,">,<",P[q+nI+1].x,",",P[q+nI+1].y,",",P[q+nI+1].z,">,<",N[q+nI+1].x,",",N[q+nI+1].y,",",N[q+nI+1].z,">}\n")
		                #write(filehandle,"smooth_triangle{<",P[q].x,",",P[q].y,",",P[q].z,">,<",N[q].x,",",N[q].y,",",N[q].z,">,<",P[q+nI].x,",",P[q+nI].y,",",P[q+nI].z,">,<",N[q+nI].x,",",N[q+nI].y,",",N[q+nI].z,">,<",P[q+nI+1].x,",",P[q+nI+1].y,",",P[q+nI+1].z,">,<",N[q+nI+1].x,",",N[q+nI+1].y,",",N[q+nI+1].z,">}\n")
		        #else
		                smooth_triangle{P[q],N[q],P[q+1],N[q+1],P[q+nI+1],N[q+nI+1]}
		                smooth_triangle{P[q],N[q],P[q+nI],N[q+nI],P[q+nI+1],N[q+nI+1]}
		        #end

		#else        
		        #if (dofile=true)
		                #write(filehandle,"triangle{<",P[q].x,",",P[q].y,",",P[q].z,">,<",P[q+1].x,",",P[q+1].y,",",P[q+1].z,">,<",P[q+nI+1].x,",",P[q+nI+1].y,",",P[q+nI+1].z,">}\n")
		                #write(filehandle,"triangle{<",P[q].x,",",P[q].y,",",P[q].z,">,<",P[q+nI].x,",",P[q+nI].y,",",P[q+nI].z,">,<",P[q+nI+1].x,",",P[q+nI+1].y,",",P[q+nI+1].z,">}\n")
		        #else                        
		                triangle{P[q],P[q+1],P[q+nI+1]}
		                triangle{P[q],P[q+nI],P[q+nI+1]}
		        #end
		#end       
	#end
	#local q=q+1;#end

#end

#macro MakeGrassPatch(lPatch,nBlade,ryBlade,segBlade,lBlade,wBlade,wBladeEnd,doSmooth,startBend,vBend,pwBend,rd,stdposBlade,stdrotBlade,stdBlade,stdBend,dofold,dofile,fname)
	#if(dofile=true)          
		#warning concat(fname," mesh file creation starts\n")

		#fopen filehandle fname write  // creates the leaf mesh (individual leaf)
		#write(filehandle,"mesh{\n")
		#else
		mesh{
	#end
	#local iBlade=lPatch/(nBlade-1);
	#local s1=seed(rd);
	#local zCount=0;
	#while (zCount<nBlade)
		#local xCount=0;                          
		
		#while (xCount<nBlade)                                          

		        #local posBlade=<xCount*iBlade,0,zCount*iBlade>+<iBlade*(0.5-rand(s1))*stdposBlade,0,iBlade*(0.5-rand(s1))*stdposBlade>;
		        #local rotBlade=ryBlade+(0.5-rand(s1))*stdrotBlade;
	//                #local lBladetmp=max(lBlade*0.3,lBlade+(0.5-rand(s1))*stdlBlade);     
		        #local scBlade=max(0.5,(0.5-rand(s1))*stdBlade*2);
		        #local lBladetmp=lBlade*scBlade;     
		        #local xBladeStart=wBlade*scBlade;
		        #local xBladeEnd=wBladeEnd*scBlade;
		        #local zBladeStart=xBladeStart*0.5;
		        #local vBendtmp=vBend + <(0.5-rand(s1))*0.3,0.5-rand(s1),rand(s1)>*stdBend;
		        MakeBlade(doSmooth,posBlade,rotBlade,segBlade,lBladetmp,xBladeStart,xBladeEnd,zBladeStart,startBend,vBendtmp,pwBend,dofold,dofile)
		        #warning concat("blade ",str(zCount*nBlade+xCount+1,0,0),"/",str(nBlade*nBlade,0,0),"\n")

		        #local xCount=xCount+1;
		#end
		#local zCount=zCount+1;
	#end

	#if(dofile = true)
		#write (filehandle,"translate <",-lPatch/2,",0,",-lPatch/2,">}\n")
		#fclose filehandle
		#warning concat(fname," file created\n")
	#else
		translate <-lPatch/2,0,-lPatch/2>
		}
		
	#end

#end
