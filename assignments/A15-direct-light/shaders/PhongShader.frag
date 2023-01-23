/*
	In this assignment you have to complete the Fragment Shader contained in file 
	shaders/PhongShader.frag , to implement Direct, Point and Spot light models
*/
#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec3 lightPos;
	vec3 lightColor;
	vec3 eyePos;
	vec4 coneInOutDecayExp;
	vec4 selector;
} gubo;




/**** Modify from here *****/

/*
	For each light model:
	- function ending with _light_dir() should return a vec3 vector containing the direction of the light for the 
	considered point on the object
	- function _light_color() should return a vec3 containing the RGB color of the light,
	which includes both the hue and the intensity of the considered source.
	
	Both functions receives an argument vec3 pos, containg the world space position of the considered
	point on the object. An uniform block called gubo, contains all the parameters required to 
	implement the light models.

	all the needed parameters are stored in the uniform block gubo:
	- gubo.lightDir -> a vec3 containing the direction of the light (for spot and directional lights).
	- gubo.lightPos -> a vec3 containing the position of the light (for spot and point lights).
	- gubo.lightColor -> a vec3 containing the basic color of the light.
	- gubo.coneInOutDecayExp.x-> a float component containing the cosine of the outer angle of a spot light.
	- gubo.coneInOutDecayExp.y-> a float component containing the cosine of the inner angle of a spot light.
	- gubo.coneInOutDecayExp.z-> a float component containing the basic distance g for both spot and point lights.
	- gubo.coneInOutDecayExp.w-> a float component containing the denominator exponent b for both spot and point lights:
		0 for no decay, 1 for linear decay and 2 for quadratic fading.
*/

/*
	direct light
	it is used to model distant sources, like the sunlight.
	Rays are parallel to each other and constant in color and intensity.
*/

// direction
vec3 direct_light_dir(vec3 pos) {
	return gubo.lightDir;
}
// color
vec3 direct_light_color(vec3 pos) {
	return gubo.lightColor;
}

/*
	point light
	point light source that emit light from fixed point in
	the space and do not have a direction. To reproduce the
	physical properties of light sources, point lights are
	characterized by a decay factor.
*/

// direction
vec3 point_light_dir(vec3 pos) {
	// position of the light = position of the light - position of the object
	// note: light direction should be normalized to make it an unitary vector
	return normalize(gubo.lightPos - pos);
}

// we need to take into account the decay factor:
// the intensity reduces at a rate that is proportional
// to the inverse of the square of the distance.
vec3 point_light_color(vec3 pos) {
	float g = gubo.coneInOutDecayExp.z;		// basic distance
	vec3 p = gubo.lightPos;					// position of the light
	vec3 x = pos;							// position of the object
	float b = gubo.coneInOutDecayExp.w;		// decay exponent
	vec3 l = gubo.lightColor;				// basic color of the light
	float dp = length(p - x);				// distance between the light and the object
	return pow(g/dp, b) * l;
}

/*
	spot light
	spot lights are special projectors that are used to illuminate 
	specific objects or locations. They are conic sources characterized by
	a direction d and a position p. For the implementation of the spot lights,
	usually the cosine of the half-angles of the inner and outer cones cin and cout are used
*/

// direction
vec3 spot_light_dir(vec3 pos) {
	return normalize(gubo.lightPos - pos);
}
// color
vec3 spot_light_color(vec3 pos) {
	// L is equal to point light
	float g = gubo.coneInOutDecayExp.z;		// basic distance
	vec3 p = gubo.lightPos;					// position of the light
	vec3 x = pos;							// position of the object
	float dc = 1/pow(g, 2);					// decay constant (0.5 if constant)
	float b = gubo.coneInOutDecayExp.w;		// decay exponent
	vec3 l = gubo.lightColor;				// basic color of the light
	float dp = length(p - x);				// distance between the light and the object
	vec3 L = pow(g/dp, dc- b) * l;

	// this is new: for the spot light, we need to take into account the
	// angle of the cone we use the cosine of the half-angle of the cone
	// f = cone dimming effect = clamp(cosine of light direction vector
	// and the direction of the spot)
	float cout = gubo.coneInOutDecayExp.x;
	float cin = gubo.coneInOutDecayExp.y;
	float alpha = dot(normalize(gubo.lightDir), normalize(gubo.lightPos - pos));
	float f = clamp((alpha - cout) / (cin - cout), 0.0, 1.0);
	return L * f;
}

/**** To here *****/

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	vec3 lD;	// light direction from the light model
	vec3 lC;	// light color and intensity from the light model
	
	lD = direct_light_dir(fragPos) * gubo.selector.x +
	     point_light_dir(fragPos)  * gubo.selector.y +
	     spot_light_dir(fragPos)   * gubo.selector.z;
	lC = direct_light_color(fragPos) * gubo.selector.x +
	     point_light_color(fragPos)  * gubo.selector.y +
	     spot_light_color(fragPos)   * gubo.selector.z;

	vec3 Diffuse = (texture(texSampler, fragTexCoord).rgb * gubo.selector.w + vec3(1,1,1) * (1-gubo.selector.w)) * (max(dot(Norm, lD),0.0f) );
	vec3 Specular = vec3(pow(max(dot(EyeDir, -reflect(lD, Norm)),0.0f), 64.0f));
	
	outColor = vec4((Diffuse + Specular) * lC, 1.0f);	
}