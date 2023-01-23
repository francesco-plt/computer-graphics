#define GLM_FORCE_DEPTH_ZERO_TO_ONE

// othogonal: perpendicular to plane (xy, yz, zx)
// axonometric: see all faces of the object
glm::mat4 vk_ortho(float a)
{
	// w, n, f are given by exercise text
	float w = 2;
	float n = -4;
	float f = 12;

	float l = -w;
	float r = w;
	float t = w / a;
	float b = -w / a;

	// orthographic projection matrix with boundaries
	// y-axis flip to match vulkan conventions
	// input: dimensions of the view frustum
	// output: orthographic projection matrix
	return glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::ortho(l, r, b, t, n, f);
}

// Create a matrix for Isometric projection with the given aspect ration a
glm::mat4 PO1(float a)
{
	// axes angled at 120° one from the other
	glm::mat4 rot1 = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rot2 = glm::rotate(glm::mat4(1), glm::radians(35.26f), glm::vec3(1.0f, 0.0f, 0.0f));
	return vk_ortho(a) * rot2 * rot1;
}

// Dimetric projections have two different units:
// one for the x and z-axis and one for the y-axis

// Create a matrix for Dimnetric projection (alpha = 45 degree)
// with the given aspect ration a
glm::mat4 PO2(float a)
{
	glm::mat4 rot1 = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rot2 = glm::rotate(glm::mat4(1), glm::radians(45.00f), glm::vec3(1.0f, 0.0f, 0.0f));
	return vk_ortho(a) * rot2 * rot1;
}

// Trimetric projections allow a different unit for the three axes

// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
// with the given aspect ration a
glm::mat4 PO3(float a)
{
	glm::mat4 rot1 = glm::rotate(glm::mat4(1), glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rot2 = glm::rotate(glm::mat4(1), glm::radians(45.00f), glm::vec3(1.0f, 0.0f, 0.0f));
	return vk_ortho(a) * rot2 * rot1;
}

// Cavalier: the length of the z-axis is halved, and it is
// oriented at a different angle w.r.t. the other ones

// Create a matrix for Cabinet projection (alpha = 45)
// with the given aspect ration a
glm::mat4 PO4(float a)
{
	float alpha = glm::radians(45.0f);
	float rho = 0.5f;
	glm::mat4 shear = glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		-rho * cos(alpha), -rho * sin(alpha), 1, 0,
		0, 0, 0, 1);
	return vk_ortho(a) * shear;
}
