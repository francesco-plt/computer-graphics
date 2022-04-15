function buildGeometry() {
	var i;
	var j;
	var x;
	var z;
	

	// Draws function y = sin(x) * cos(z) with -3 <= x <= 3 and -3 <= z <= 3.
	///// Creates vertices
	var vert2 = [];
	for(i = 0; i <= 60; i++) {
		for(j = 0; j <= 60; j++) {
			x = (i - 30)/10;
			z = (j - 30)/10;
			vert2[i*61+j] = [x, Math.sin(x)*Math.cos(z), z];
		}
	}
	////// Creates indices
	var ind2 = [];
	for(i = 0; i < 60; i++) {
		for(j = 0; j < 60; j++) {
			ind2[6*(i*60+j)  ] = 61*j+i;
			ind2[6*(i*60+j)+1] = 61*j+i+1;
			ind2[6*(i*60+j)+2] = 61*(j+1)+i+1;
			ind2[6*(i*60+j)+3] = 61*j+i;
			ind2[6*(i*60+j)+4] = 61*(j+1)+i+1;
			ind2[6*(i*60+j)+5] = 61*(j+1)+i;
		}
	}


	var color2 = [0.0, 0.0, 1.0];
	addMesh(vert2, ind2, color2);






	// Draws a Half Sphere
	///// Creates vertices
	var vert3 = [];
	var vert3 = [];
	for(i = 0; i <= 6; i++) {
		for(j = 0; j <= 12; j++) {
			x = Math.sin(15*i* Math.PI / 180)*Math.cos(30*j* Math.PI / 180);
			z = Math.sin(15*i* Math.PI / 180)*Math.sin(30*j* Math.PI / 180);
			vert3[i*13+j] = [x, Math.cos(15*i* Math.PI / 180), z];
		}
	}
		
	////// Creates indices
	var ind3 = [];
	for(i = 0; i < 6; i++) {
		for(j = 0; j < 12; j++) {
			ind3[6*(i*12+j)  ] = i*13+j;
			ind3[6*(i*12+j)+1] = i*13+j+1;
			ind3[6*(i*12+j)+2] = (i+1)*13+j;
			ind3[6*(i*12+j)+3] = i*13+j+1;
			ind3[6*(i*12+j)+4] = (i+1)*13+j+1;
			ind3[6*(i*12+j)+5] = (i+1)*13+j;

		}
	}

	var color3 = [0.0, 1.0, 0.0];
	addMesh(vert3, ind3, color3);
}

