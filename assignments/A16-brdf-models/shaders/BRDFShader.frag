#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir0;
	vec3 lightColor0;
	vec3 lightDir1;
	vec3 lightColor1;
	vec3 lightDir2;
	vec3 lightColor2;
	vec3 lightDir3;
	vec3 lightColor3;
	vec3 eyePos;
	vec4 selector;
} gubo;

/**** Modify from here *****/

/*
	For each light model, function ending with ..._BRDF() should return a vec3 vector containing the RGB 
	color computed by the model. Each function receives the following parameters:
	- vec3 L: direction of the light (unitary vector)
	- vec3 N: direction of the surface normal (unitary vector)
	- vec3 V: direction of the view vector (unitary vector)
	- vec3 C: color of the surface (RGB vector)
*/

vec3 Lambert_Diffuse_BRDF(vec3 L, vec3 N, vec3 V, vec3 C) {

	// lambert diffuse BRDF
	return C * max(dot(L, N), 0.0);
}

// additional parameter:
// float sigma : roughness of the material
vec3 Oren_Nayar_Diffuse_BRDF(vec3 L, vec3 N, vec3 V, vec3 C, float sigma) {
	float thi = acos(dot(L, N));
	float thr = acos(dot(V, N));	// V = omega_r
	float alpha = max(thi, thr);
	float beta = min(thi, thr);
	float A = 1 - 0.5 * pow(sigma, 2) / (pow(sigma, 2) + 0.33);
	float B = 0.45 * pow(sigma, 2) / (pow(sigma, 2) + 0.09);
	vec3 vi = normalize(L - dot(L, N) * N);
	vec3 vr = normalize(V - dot(V, N) * N);
	float G = max(dot(vi, vr), 0.0);
	vec3 L1 = C * clamp(dot(L, N), 0.0, 1.0);
	
	return L1 * (A + B * G * sin(alpha) * tan(beta));
}

// Phong Specular BRDF model
// additional parameter:
// float gamma : exponent of the cosine term
vec3 Phong_Specular_BRDF(vec3 L, vec3 N, vec3 V, vec3 C, float gamma)  {
	// reflection happens in the opposite direction
	// For this reason the minus sign is required
	vec3 r = - reflect(L, N);
	float intensity = pow(clamp(dot(V, r), 0.0, 1.0), gamma);
	return C * intensity;
}

// Toon Diffuse Brdf
// additional parameters:
// vec3 Cd : color to be used in dark areas
// float thr : color threshold
vec3 Toon_Diffuse_BRDF(vec3 L, vec3 N, vec3 V, vec3 C, vec3 Cd, float thr) {
	float thr2 = 0.07;
	vec3 Cd1 = 0.002f * C;
	if (dot(L, N) < thr2) {
		return Cd1;
	} else if(dot(L, N) < thr) {
		return Cd;
	} else {
		return C;
	}
}

// Directional light direction
// additional parameter:
// float thr : color threshold
vec3 Toon_Specular_BRDF(vec3 L, vec3 N, vec3 V, vec3 C, float thr)  {

	vec3 Ms0 =  C;
	vec3 Ms1 =  vec3(0, 0, 0);	// light color in shadow
	vec3 r = - reflect(L, N);
	if(dot(V, r) < thr) {
		return Ms1;
	} else {
		return Ms0;
	}
}


/**** To here *****/




vec3 BRDF_D(vec3 L, vec3 N, vec3 V, vec3 C) {
	return gubo.selector.x * Lambert_Diffuse_BRDF(L, N, V, C) +
		   (1.0 - gubo.selector.x) * (1.0 - gubo.selector.y) * 
		   			Toon_Diffuse_BRDF(L, N, V, C, 0.2f * C, 0.5) +
		   (1.0 - gubo.selector.x) * (gubo.selector.y) * 
		   			Oren_Nayar_Diffuse_BRDF(L, N, V, C, 1.5);
}

vec3 BRDF_S(vec3 L, vec3 N, vec3 V, vec3 C) {
	return Phong_Specular_BRDF(L, N, V, C, 200.0f) * gubo.selector.z +
		   (1.0 - gubo.selector.x) * (1.0 - gubo.selector.y) * 
		   			Toon_Specular_BRDF(L, N, V, vec3(1,1,1), 0.97f);
}

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	float AmbFact = 0.025;
	
	vec3 DiffColor = texture(texSampler, fragTexCoord).rgb * gubo.selector.w + vec3(1,1,1) * (1-gubo.selector.w);
	vec3 Diffuse = vec3(0,0,0);
	
	Diffuse += BRDF_D(gubo.lightDir0, Norm, EyeDir, DiffColor) * gubo.lightColor0;
	Diffuse += BRDF_D(gubo.lightDir1, Norm, EyeDir, DiffColor) * gubo.lightColor1;
	Diffuse += BRDF_D(gubo.lightDir2, Norm, EyeDir, DiffColor) * gubo.lightColor2;
	Diffuse += BRDF_D(gubo.lightDir3, Norm, EyeDir, DiffColor) * gubo.lightColor3;
	
	vec3 Specular = vec3(0,0,0);
	Specular += BRDF_S(gubo.lightDir0, Norm, EyeDir, vec3(1,1,1)) * gubo.lightColor0;
	Specular += BRDF_S(gubo.lightDir1, Norm, EyeDir, vec3(1,1,1)) * gubo.lightColor1;
	Specular += BRDF_S(gubo.lightDir2, Norm, EyeDir, vec3(1,1,1)) * gubo.lightColor2;
	Specular += BRDF_S(gubo.lightDir3, Norm, EyeDir, vec3(1,1,1)) * gubo.lightColor3;

	vec3 Ambient = AmbFact * DiffColor;
	
	outColor = vec4(Diffuse + Specular + Ambient, 1.0f);	
}