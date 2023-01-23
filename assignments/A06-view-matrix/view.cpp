// Create a look in (view) direction matrix:
// Mc = Tpos * Ry_alpha * Rx_beta * Rz_rho, Mc = camera matrix
// Pos    -> Position of the camera
// Angs.x -> direction (alpha)
// Angs.y -> elevation (beta)
// Angs.z -> roll (rho)
glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs)
{
	glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	return glm::rotate(glm::mat4(1.0), -Angs.z, zAxis) *
		   glm::rotate(glm::mat4(1.0), -Angs.y, xAxis) *
		   glm::rotate(glm::mat4(1.0), -Angs.x, yAxis) *
		   glm::translate(glm::mat4(1.0), -Pos);
}

// with alpha=0 the camera looks North, while with alpha=90
// the camera looks West. South is alpha=180 and East is alpha=-90.
// A positive angle beta>0 makes the camera look up.
// A positive angle rho>0 turns the camera counterclockwise.
// 1. Translate 3D camera object in the position from which we want to look (Pos)
// 2. we apply rotate transformation to shape the looking from direction

// Create a look at matrix
// Pos    -> Position of the camera (c)
// aim    -> Posizion of the target (a)
// Roll   -> roll (rho)
glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll)
{
	// glm::lookAt() output: Look-at matrix
	glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	return glm::lookAt(Pos, aim, yAxis);
}
