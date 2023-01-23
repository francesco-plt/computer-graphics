/*
	World Matrix Mw: local coordinates -> global ones [ + transformations ]
	Mw generated using position, Euler angles and size.
	Euler angles are passed in YPR parameter:
	- YPR.x : Yaw
	- YPR.y : Pitch
	- YPR.z : Roll
*/

glm::mat4 MakeWorldMatrixEuler(glm::vec3 pos, glm::vec3 YPR, glm::vec3 size)
{
	glm::mat4 MEa = glm::eulerAngleYXZ(glm::radians(YPR.y), glm::radians(YPR.x), glm::radians(YPR.z)); // Rotation matrix from Euler angles
	return glm::translate(glm::mat4(1.0), pos) * MEa * glm::scale(glm::mat4(1.0), size);			   // World matrix
}

// Same Mw but with quaternion angles
glm::mat4 MakeWorldMatrixQuat(glm::vec3 pos, glm::quat rQ, glm::vec3 size)
{
	return glm::translate(glm::mat4(1.0), pos) * glm::mat4(rQ) * glm::scale(glm::mat4(1.0), size);
}