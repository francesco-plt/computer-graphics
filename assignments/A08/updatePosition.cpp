#include <glm/gtx/euler_angles.hpp>
// Create the world matrix for the robot

// function to create world matrix from assignment 7
glm::mat4 eulerWM(glm::vec3 pos, glm::vec3 YPR)
{
	glm::mat4 MEa = glm::eulerAngleYXZ(glm::radians(YPR.y), glm::radians(YPR.x), glm::radians(YPR.z));
	return glm::translate(glm::mat4(1.0), pos) * MEa;
}

glm::mat4 getRobotWorldMatrix(GLFWwindow *window)
{
	// just setting deltaT to check how much time has passed
	// between getRobotWorldMatrix calls
	static auto startTime = std::chrono::high_resolution_clock::now();
	static float lastTime = 0.0f;
	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	float deltaT = time - lastTime;
	lastTime = time;

	float XSPEED = 1.1;							// > 1 -> faster, < 1 -> slower
	float YSPEED = 1.8;							// > 1 -> faster, < 1 -> slower
	float DIAGSPEED = 0.8;						// > 1 -> faster, < 1 -> slower
	static glm::vec3 pos = glm::vec3(-3, 0, 2); // player position,
												// initialized randomly
	static glm::mat4 out;						// robot world matrix I think

	glm::vec3 CamDir[4]{
		glm::vec3(-1, 0, 0), // east
		glm::vec3(1, 0, 0),	 // west
		glm::vec3(0, 0, -1), // north
		glm::vec3(0, 0, 1)	 // south
	};

	// in order: east, north, west and south
	float yawAngles[5] = {0.0f, 90.0f, 180.0f, 270.0f, 360.f};
	float yawDiagAngles[4] = {45.0f, 135.0f, 225.0f, 315.0f};

	// common WASD input control
	// west
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		pos += XSPEED * CamDir[0] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles[2], 0.0f));
	}
	// east
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		pos += XSPEED * CamDir[1] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles[0], 0.0f));
	}
	// north
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		pos += YSPEED * CamDir[2] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles[1], 0.0f));
	}
	// south
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		pos += YSPEED * CamDir[3] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles[3], 0.0f));
	}
	// north-west
	if (glfwGetKey(window, GLFW_KEY_A) && glfwGetKey(window, GLFW_KEY_W))
	{
		pos += DIAGSPEED * CamDir[0] * CamDir[2] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawDiagAngles[1], 0.0f));
	}
	// north-east
	if (glfwGetKey(window, GLFW_KEY_W) && glfwGetKey(window, GLFW_KEY_D))
	{
		pos += DIAGSPEED * CamDir[2] * CamDir[1] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawDiagAngles[0], 0.0f));
	}
	// south-east
	if (glfwGetKey(window, GLFW_KEY_D) && glfwGetKey(window, GLFW_KEY_S))
	{
		pos += DIAGSPEED * CamDir[1] * CamDir[3] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawDiagAngles[3], 0.0f));
	}
	// south-west
	if (glfwGetKey(window, GLFW_KEY_A) && glfwGetKey(window, GLFW_KEY_S))
	{
		pos += DIAGSPEED * CamDir[0] * CamDir[3] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawDiagAngles[2], 0.0f));
	}

	return out;
}