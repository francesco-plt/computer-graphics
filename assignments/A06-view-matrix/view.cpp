// Create a look in (view) direction matrix:
// Mc = Tpos * Ry_alpha * Rx_beta * Rz_rho, Mc = camera matrix
// Pos    -> Position of the camera
// Angs.x -> direction (alpha)
// Angs.y -> elevation (beta)
// Angs.z -> roll (rho)
glm::mat4 LookInDirMat(glm::vec3 Pos, glm::vec3 Angs)
{
	return glm::rotate(glm::mat4(1.0), -Angs.z, glm::vec3(0, 0, 1)) *
		   glm::rotate(glm::mat4(1.0), -Angs.y, glm::vec3(1, 0, 0)) *
		   glm::rotate(glm::mat4(1.0), -Angs.x, glm::vec3(0, 1, 0)) *
		   glm::translate(glm::mat4(1.0), -Pos);
}

// more about building Mv for a lookin view matrix:
// with alpha=0 the camera looks North, while with alpha=90
// the camera looks West. South is alpha=180 and East is alpha=-90.
// A positive angle beta>0 makes the camera look up.
// A positive angle rho>0 turns the camera counterclockwise.
// So basically we translated the 3D camera object in the position from
// which we want to look (Pos), and then we apply rotate transformation to
// shape the looking from direction

// Create a look at matrix
// Pos    -> Position of the camera (c)
// aim    -> Posizion of the target (a)
// Roll   -> roll (rho)
glm::mat4 LookAtMat(glm::vec3 Pos, glm::vec3 aim, float Roll)
{
	// glm::lookAt() functions: creates a
	// Look-at matrix starting from three glm::vec3 vectors
	// representing respectively the center of the camera, the point it
	// targets, and it up-vector
	return glm::lookAt(Pos, aim, glm::vec3(0.0f, 1.0f, 0.0f));
}
