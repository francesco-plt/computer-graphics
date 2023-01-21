#define GLM_FORCE_DEPTH_ZERO_TO_ONE

// matrices for Perspective projection
// with the given aspect ratio a, and
// different FovY

// FovY = 90°
glm::mat4 PO1(float a)
{
	// perspective() function computes the perspective projection matrix specifying Fov and aspect ratio
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), a, 0.1f, 9.9f);
	// Vulkan and OpenGL matrices for Fov/Aspect ratio projection differ only for the sign of the element in the second row / second column
	// it's better to change the sign instead of mirroring
	proj[1][1] *= -1;
	return proj;
}

// FovY = 120°
glm::mat4 PO2(float a)
{
	glm::mat4 proj = glm::perspective(glm::radians(120.0f), a, 0.1f, 9.9f);
	proj[1][1] *= -1;
	return proj;
}

// // FovY = 30°
glm::mat4 PO3(float a)
{
	glm::mat4 proj = glm::perspective(glm::radians(30.0f), a, 0.1f, 9.9f);
	proj[1][1] *= -1;
	return proj;
}

// FovY = 90°.
// The perspective should only show the left side of the view
// Here r=0, and l, t and b should be computed
// to match both the aspect ratio and the FovY
glm::mat4 PO4(float a)
{
	float n = 0.1f;
	float f = 9.9f;
	float l = -a * n * tan(glm::radians(90.0f) / 2);
	float t = n * tan(glm::radians(90.0f) / 2);
	float b = -n * tan(glm::radians(90.0f) / 2);

	// added matrix product flips the y-axis to match the Vulkan conventions.
	glm::mat4 vk_fix = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1));
	//  frustum() function to compute the perspective projection matrix specifying the boundaries:
	return vk_fix * glm::frustum(l, 0.0f, b, t, 0.1f, 9.9f);
}
