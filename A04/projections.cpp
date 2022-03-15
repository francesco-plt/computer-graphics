#define GLM_FORCE_DEPTH_ZERO_TO_ONE

glm::mat4 orth(float a)
{
	// w, n, f are given by exercise text
	float w = 2;
	float l = -w;
	float r = w;
	float b = -w / a;
	float t = w / a;
	float n = -4;
	float f = 12;
	return glm::scale(glm::mat4(1.0), glm::vec3(1, -1, 1)) * glm::ortho(l, r, b, t, n, f);
}

// Create a matrix for Isometric projection with the given aspect ration a
glm::mat4 PO1(float a)
{
	glm::mat4 rot1 = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rot2 = glm::rotate(glm::mat4(1), glm::radians(35.26f), glm::vec3(1.0f, 0.0f, 0.0f));
	return orth(a) * rot2 * rot1;
}

// Create a matrix for Dimnetric projection (alpha = 45 degree)
// with the given aspect ration a
glm::mat4 PO2(float a)
{
	glm::mat4 rot1 = glm::rotate(glm::mat4(1), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rot2 = glm::rotate(glm::mat4(1), glm::radians(45.00f), glm::vec3(1.0f, 0.0f, 0.0f));
	return orth(a) * rot2 * rot1;
}

// Create a matrix for Trimetric projection (alpha = 45 degree, beta = 60 degree)
// with the given aspect ration a
glm::mat4 PO3(float a)
{
	glm::mat4 rot1 = glm::rotate(glm::mat4(1), glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rot2 = glm::rotate(glm::mat4(1), glm::radians(45.00f), glm::vec3(1.0f, 0.0f, 0.0f));
	return orth(a) * rot2 * rot1;
}

// Create a matrix for Cabinet projection (alpha = 45)
// with the given aspect ration a
glm::mat4 PO4(float a)
{
	glm::mat4 shear = glm::mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		-0.5 * cos(45.0f), -0.5 * sin(45.0f), 1, 0,
		0, 0, 0, 1);
	return orth(a) * shear;
}
