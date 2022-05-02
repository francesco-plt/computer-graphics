#define GLM_FORCE_DEPTH_ZERO_TO_ONE

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 90o
glm::mat4 PO1(float a)
{
	// perspective() function computes the perspective projection matrix specifying Fov and aspect ratio
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), a, 0.1f, 9.9f);
	// Vulkan and OpenGL matrices for Fov/Aspect ratio projection differ only for the sign of the element in the second row / second column
	// it's better to change the sign instead of mirroring
	proj[1][1] *= -1;
	return proj;
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 120o
glm::mat4 PO2(float a)
{
	glm::mat4 proj = glm::perspective(glm::radians(120.0f), a, 0.1f, 9.9f);
	proj[1][1] *= -1;
	return proj;
}

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 30o
glm::mat4 PO3(float a)
{
	glm::mat4 proj = glm::perspective(glm::radians(30.0f), a, 0.1f, 9.9f);
	proj[1][1] *= -1;
	return proj;
}

// Create a matrix for Perspecrtive projection, with the given aspect ratio a.
// Here the perspective should only show the left side of the view
// with a FovY = 90o. Here r=0, and l, t and b should be computed
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
