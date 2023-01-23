#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	// Direct lights parameters (for diffuse and specular)
	vec3 lightDir0;
	vec3 lightColor0;
	vec3 lightDir1;
	vec3 lightColor1;
	vec3 lightDir2;
	vec3 lightColor2;
	vec3 lightDir3;
	vec3 lightColor3;

	// Ambient light parameters
	vec3 AmbColor;
	vec3 TopColor;
	vec3 DzColor;
	vec3 DxColor;
	// + Bottom color for Hemispheric light
	// + Constant term for Spherical Harmonics light
	// + DyColor for Spherical Harmonics light
	
	// Other parameters (not relevant for the exercise solution)
	vec3 eyePos;
	vec4 selector;
} gubo;

/**** Modify from here *****/

// same as in BRDFShader.vert fist of all
// we need to update the location id:
layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

// note: l_A from the slides is gubo.AmbColor

// Oren Nayar Diffuse + Ambient
// No Specular
// One directional light (lightDir0 and lightColor0)
vec3 Case1_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca, float sigma) {

	// Parameters are:
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cd : main color (diffuse color)
	// vec3 Ca : ambient color
	// float sigma : roughness of the material

	// Diffuse reflection model (Oren Nayar) computation
	vec3 L =  gubo.lightDir0;
	vec3 C = gubo.lightColor0;
	float thi = acos(dot(L, N));
	float thr = acos(dot(V, N));
	float alpha = max(thi, thr);
	float beta = min(thi, thr);
	float A = 1 - 0.5 * pow(sigma, 2) / (pow(sigma, 2) + 0.33);
	float B = 0.45 * pow(sigma, 2) / (pow(sigma, 2) + 0.09);
	vec3 vi = normalize(L - dot(L, N) * N);
	vec3 vr = normalize(V - dot(V, N) * N);
	float G = max(dot(vi, vr), 0.0);
	vec3 L1 = C * clamp(dot(L, N), 0.0, 1.0);
	vec3 oren_nayar_color = L1 * (A + B * G * sin(alpha) * tan(beta));
	// aka: reflection_model = model_color * main_color
	vec3 reflect_model = oren_nayar_color * Cd;

	// Ambient reflection model computation
	// aka: ambient_model = basic ambient color. * ambient color of the surface
	vec3 amb_model = gubo.AmbColor * Ca;

	return reflect_model + amb_model;
}

// Lambert Diffuse + Hemispheric
// No Specular
// One directional light (lightDir0 and lightColor0)
// Hemispheric light oriented along the y-axis
vec3 Case2_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca) {

	// Parameters are:
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cd : main color (diffuse color) = f_A(x,omega_r)
	// vec3 Ca : ambient color

	// Diffuse reflection model (Lambert) computation
	vec3 L =  gubo.lightDir0; 	// d = direction vector
	vec3 C = gubo.lightColor0;
	vec3 lambert_color = C * max(dot(L, N), 0.0);
	vec3 reflect_model = lambert_color * Cd;

	// Ambient reflection model computation
	vec3 ld = gubo.AmbColor;
	vec3 lu = gubo.TopColor;
	vec3 hemiCol = ((dot(N, L) + 1) / 2) * lu + (1 - (dot(N, L) + 1) / 2) * ld;
	vec3 amb_model = hemiCol * Ca;
	
	return reflect_model + amb_model;
}

// Spherical Harmonics
// Blinn Specular
// Four directional lights (lightDir0 to lightDir3, and lightColor0 to lightColor3)
vec3 Case3_Color(vec3 N, vec3 V, vec3 Cs, vec3 Ca, float gamma)  {

	// Parameters are:
	// vec3 N : normal vector
	// vec3 V : view direction
	// vec3 Cs : specular color
	// vec3 Ca : ambient color
	// float gamma : Blinn exponent

	// Specular reflection model (Blinn) computation
	// we have one blinn_color component for each light
	vec3 L0 =  gubo.lightDir0;
	vec3 L1 =  gubo.lightDir1;
	vec3 L2 =  gubo.lightDir2;
	vec3 L3 =  gubo.lightDir3;
	vec3 h0 = normalize(L0 + V);
	vec3 h1 = normalize(L1 + V);
	vec3 h2 = normalize(L2 + V);
	vec3 h3 = normalize(L3 + V);
	vec3 C = gubo.lightColor0;
	vec3 blinn_color0 = C * pow(max(dot(N, h0), 0.0), gamma);
	vec3 blinn_color1 = C * pow(max(dot(N, h1), 0.0), gamma);
	vec3 blinn_color2 = C * pow(max(dot(N, h2), 0.0), gamma);
	vec3 blinn_color3 = C * pow(max(dot(N, h3), 0.0), gamma);
	vec3 reflect_model = (
		blinn_color0 + blinn_color1 + blinn_color2 + blinn_color3
	) * Cs;

	vec3 shCol = gubo.AmbColor + N.x * gubo.DxColor + N.z * gubo.DzColor;
	vec3 amb_model = shCol * Ca;
	
	return reflect_model + amb_model;
}

/**** To here *****/

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	float AmbFact = 0.025;
	
	vec3 DifCol = texture(texSampler, fragTexCoord).rgb * gubo.selector.w +
				  vec3(1,1,1) * (1-gubo.selector.w);

	vec3 CompColor = gubo.selector.x *
						Case1_Color(Norm, EyeDir, DifCol, DifCol, 1.2f) +
					 gubo.selector.y *
						Case2_Color(Norm, EyeDir, DifCol, DifCol) +
					 gubo.selector.z *
						Case3_Color(Norm, EyeDir, vec3(1.0f,1.0f,1.0f), DifCol, 200.0f);
	
	outColor = vec4(CompColor, 1.0f);	
}