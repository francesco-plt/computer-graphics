#define GLM_FORCE_DEPTH_ZERO_TO_ONE

// Perspective projection
// aspect ratio a + FovY

// FovY = 90°
glm::mat4 PO1(float a)
{
	float fov = glm::radians(90.0f);
	float np = 0.1f;
	float fp = 9.9f;
	// perspective() output: perspective projection matrix
	glm::mat4 proj = glm::perspective(fov, a, np, fp);
	// matching vulkan convention for second row / second column item
	proj[1][1] *= -1;
	return proj;
}

// FovY = 120°
glm::mat4 PO2(float a)
{
	float fov = glm::radians(120.0f);
	float np = 0.1f;
	float fp = 9.9f;
	glm::mat4 proj = glm::perspective(fov, a, np, fp);
	proj[1][1] *= -1;
	return proj;
}

// // FovY = 30°
glm::mat4 PO3(float a)
{
	float fov = glm::radians(30.0f);
	float np = 0.1f;
	float fp = 9.9f;
	glm::mat4 proj = glm::perspective(fov, a, np, fp);
	proj[1][1] *= -1;
	return proj;
}

// FovY = 90°.
// The perspective should only show the left side of the view
// Here r=0, and l, t and b should be computed
// to match both the aspect ratio and the FovY
glm::mat4 PO4(float a)
{
	float np = 0.1f;
	float fp = 9.9f;
	float fov = glm::radians(90.0f);
	float l = -a * np * tan(glm::radians(90.0f) / 2);
	float r = 0.0f; // specified in the assignment
	float t = np * tan(glm::radians(90.0f) / 2);
	float b = -np * tan(glm::radians(90.0f) / 2);

	// flipping y-axis to match Vulkan convention
	glm::mat4 vk_fix = glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1));
	// frustum() output: perspective projection matrix
	return vk_fix * glm::frustum(l, r, b, t, np, fp);
}
