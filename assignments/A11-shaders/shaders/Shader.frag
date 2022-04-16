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

layout(location = 0) in float real;
layout(location = 1) in float img;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
	float m_real = 0.0f, m_img = 0.0f, temp;
	int i;
	for(i = 0; i < 16; i++) {
		if(m_real * m_real + m_img * m_img > 4.0) {
			break;
		}
		temp = m_real * m_real - m_img * m_img + real;
		m_img = 2.0 * m_real * m_img + img;
		m_real = temp;
	}
	// outColor = vec4(
	// 	(float(i % 5) + sin(gubo.time*6.28)) / 5.0,	float(i % 10) / 10.0, float(i) / 15.0, 1.0
	// );
	outColor = vec4(
		rand(vec2(1.0, 1.0)),
		rand(vec2(1.0, 1.0)),
		rand(vec2(1.0, 1.0)),
		rand(vec2(1.0, 1.0))
	);
}