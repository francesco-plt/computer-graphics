#define GLM_FORCE_DEPTH_ZERO_TO_ONE

// Create a matrix for Perspecrtive projection with the given aspect ratio a,
// and a FovY = 90o
glm::mat4 PO1(float a)
{
	glm::mat4 proj = glm::perspective(glm::radians(90.0f), a, 0.1f, 9.9f);
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
	return glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::frustum(l, 0.0f, b, t, 0.1f, 9.9f);
}
