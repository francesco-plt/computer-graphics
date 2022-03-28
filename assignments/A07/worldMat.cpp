// Create a world matrix using position, Euler angles, and size
// Euler angles are passed in YPR parameter:
// YPR.x : Yaw
// YPR.y : Pitch
// YPR.z : Roll
// Mw = T * Ry * Rx * Rz * S
// MEa = Ry * Rx * Rz
glm::mat4 MakeWorldMatrixEuler(glm::vec3 pos, glm::vec3 YPR, glm::vec3 size)
{
	glm::mat4 MEa = glm::eulerAngleYXZ(glm::radians(YPR.y), glm::radians(YPR.x), glm::radians(YPR.z));
	return glm::translate(glm::mat4(1.0), pos) * MEa * glm::scale(glm::mat4(1.0), size);
}

// Create a world matrix using position, quaternion angles, and size
glm::mat4 MakeWorldMatrixQuat(glm::vec3 pos, glm::quat rQ, glm::vec3 size)
{
	return glm::translate(glm::mat4(1.0), pos) * glm::mat4(rQ) * glm::scale(glm::mat4(1.0), size);
}
