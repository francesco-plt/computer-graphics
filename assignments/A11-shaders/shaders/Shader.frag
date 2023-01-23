/*
	This shader is needed to correctly display colors on the screen.
	Whenever we start the application we want to see the starship with
	flashing colors

	Variables:
	vec4 outColor = time dependent color
	The first three of the four elements are respectively the red, green and blue components of the 
	color, all in the 0-1 range. The last element of the vector is the transparency, and should be always 
	set to 1 to avoid graphic card dependent showing problems.
	
	The fragment shader can use float time; component of the black
	called gubo to have a timer count. In particular, it is a number in the 
	range 0-1, representing the current	fraction of second. The way in which 
	the color alternates is left to the	student, and can be anything.
*/

#version 450

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

// rotating palette basing on time t
vec3 palette(float t, vec3 a, vec3 b, vec3 c, vec3 d) {
	float p = 6.28318;
    return a + b * cos(p * (c * t + d));
}

void main() {

	/*
	color(t) = a + b * cos[2*pi+(c*t+d)]

	in order to get hue variation the four parameters a, b, c and d must be vectors of three components (red, gree, blue).
	If you need to ensure the palettes cycle over the 0..1 interval exactly, then you'll need to make c an integer number of halves
	(0.0, 0.5, 1.0, 1.5, 2.0, ...) and d an integer number of thirds (0.0, 0.33, 0.66, 1.0).

	a					b				c				d
	0.5, 0.5, 0.5		0.5, 0.5, 0.5	1.0, 1.0, 1.0	0.00, 0.33, 0.66
	*/

	vec3 a = vec3(0.5, 0.5, 0.5);
	vec3 b = vec3(0.5, 0.5, 0.5);
	vec3 c = vec3(1.0, 1.0, 1.0);
	vec3 d = vec3(0.00, 0.33, 0.66);
	float t = gubo.time;
	outColor = vec4(palette(t, a, b, c, d), 1.0);
}
