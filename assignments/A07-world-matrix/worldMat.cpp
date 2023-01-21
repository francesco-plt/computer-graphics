/*
	The World Matrix Mw transforms the local coordinates into the
	corresponding global ones, and it applies a series of translations,
	rotations (and possibly scaling and shears) to the local coordinates.

	Here we are creating a world matrix using position, Euler angles,
	and size. Euler angles are passed in YPR parameter:
	- YPR.x : Yaw
	- YPR.y : Pitch
	- YPR.z : Roll
*/

/*
	Mw = world matrix, Mw = T * Ry * Rx * Rz * S
	MEa = rotation matrix built from Euler angles, MEa = Ry * Rx * Rz
	To build Mw from MEa:
	Mw = Tpos * MEa * Scale_size
*/
glm::mat4 MakeWorldMatrixEuler(glm::vec3 pos, glm::vec3 YPR, glm::vec3 size)
{
	glm::mat4 MEa = glm::eulerAngleYXZ(glm::radians(YPR.y), glm::radians(YPR.x), glm::radians(YPR.z));
	return glm::translate(glm::mat4(1.0), pos) * MEa * glm::scale(glm::mat4(1.0), size);
}

/*
	Quaternion: mathematical object that is used to represent a
	rotation or a change in orientation in three-dimensional space.
	It is a four-dimensional extension of the complex numbers, and
	can be represented by a scalar (real) part and a vector (imaginary) part
*/

// Here we're using quaternion angles
glm::mat4 MakeWorldMatrixQuat(glm::vec3 pos, glm::quat rQ, glm::vec3 size)
{
	return glm::translate(glm::mat4(1.0), pos) * glm::mat4(rQ) * glm::scale(glm::mat4(1.0), size);
}
