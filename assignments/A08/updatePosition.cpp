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

	float SPEED = 1.1;							// > 1 -> faster, < 1 -> slower
	static glm::vec3 pos = glm::vec3(-3, 0, 2); // player position,
												// initialized randomly
	static glm::mat4 out;						// Mc I think

	glm::vec3 CamDir[4]{
		glm::vec3(-1, 0, 0), // left
		glm::vec3(1, 0, 0),	 // right
		glm::vec3(0, 0, -1), // up
		glm::vec3(0, 0, 1)	 // down
	};

	// in order: east, north, west and south
	float yawAngles[4] = {0.0f, 90.0f, 180.0f, 270.0f};

	// common WASD input control
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		pos += SPEED * CamDir[0] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles[2], 0.0f));
	}
	// right
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		pos += SPEED * CamDir[1] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles[0], 0.0f));
	}
	// up
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		pos += SPEED * CamDir[2] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles[1], 0.0f));
	}
	// down
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		pos += SPEED * CamDir[3] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles[3], 0.0f));
	}

	return out;
}