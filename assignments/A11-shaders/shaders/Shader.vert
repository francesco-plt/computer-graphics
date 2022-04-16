/*
	This shader is needed in order for us to be able to move
	the camera around the scene.
	
	Variables:
	vec3 inPosition = cartesian local coordinates of each vertex
	mat4 worldMat = world matrix
	mat4 viewMat = view matrix
	mat4 prjMat = projection matrix
	vec4 gl_Position = clipping coordinates of the vertex
*/

#version 450

layout(set = 0, binding = 0) uniform UniformBufferObject {
	mat4 worldMat;
	mat4 viewMat;
	mat4 prjMat;
} ubo;

layout(location = 0) in vec3 inPosition;

layout(location = 0) out float real;
layout(location = 1) out float img;

void main() {
	gl_Position = ubo.prjMat * ubo.viewMat * ubo.worldMat * vec4(inPosition, 1.0);
}