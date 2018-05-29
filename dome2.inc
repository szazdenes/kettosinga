#include "colors.inc"
#include "textures.inc"

#declare board2 = plane{
	<0, 0, 1>, 0
	pigment {
		Tan*0.3 
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
    pigment{Dark_Wood}
    finish{specular 1}
}
