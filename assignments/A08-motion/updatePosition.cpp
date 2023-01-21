#include <glm/gtx/euler_angles.hpp>

// World matrix for the robot

// function to create world matrix from assignment 7
glm::mat4 eulerWM(glm::vec3 pos, glm::vec3 YPR)
{
	glm::mat4 MEa = glm::eulerAngleYXZ(glm::radians(YPR.y), glm::radians(YPR.x), glm::radians(YPR.z));
	return glm::translate(glm::mat4(1.0), pos) * MEa;
}

glm::mat4 getRobotWorldMatrix(GLFWwindow *window)
{
	// just setting deltaT to check how much
	// time has passed between calls
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

	std::unordered_map<std::string, glm::vec3> CamDir;
	CamDir["east"] = glm::vec3(1, 0, 0);
	CamDir["west"] = glm::vec3(-1, 0, 0);
	CamDir["north"] = glm::vec3(0, 0, -1);
	CamDir["south"] = glm::vec3(0, 0, 1);

	std::unordered_map<std::string, float> yawAngles;
	yawAngles["east"] = 0.0f;
	yawAngles["nort-east"] = 45.0f;
	yawAngles["north"] = 90.0f;
	yawAngles["north-west"] = 135.0f;
	yawAngles["west"] = 180.0f;
	yawAngles["south-west"] = 225.0f;
	yawAngles["south"] = 270.0f;
	yawAngles["south-east"] = 315.0f;

	// common WASD input control
	// west
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		pos += XSPEED * CamDir["west"] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles["west"], 0.0f));
	}
	// east
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		pos += XSPEED * CamDir["east"] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles["east"], 0.0f));
	}
	// north
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		pos += YSPEED * CamDir["north"] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles["north"], 0.0f));
	}
	// south
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		pos += YSPEED * CamDir["south"] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles["south"], 0.0f));
	}
	// north-west
	if (glfwGetKey(window, GLFW_KEY_A) && glfwGetKey(window, GLFW_KEY_W))
	{
		pos += DIAGSPEED * CamDir["north"] * CamDir["wests"] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles["north-west"], 0.0f));
	}
	// north-east
	if (glfwGetKey(window, GLFW_KEY_W) && glfwGetKey(window, GLFW_KEY_D))
	{
		pos += DIAGSPEED * CamDir["north"] * CamDir["east"] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles["nort-east"], 0.0f));
	}
	// south-east
	if (glfwGetKey(window, GLFW_KEY_D) && glfwGetKey(window, GLFW_KEY_S))
	{
		pos += DIAGSPEED * CamDir["south"] * CamDir["east"] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles["south-east"], 0.0f));
	}
	// south-west
	if (glfwGetKey(window, GLFW_KEY_A) && glfwGetKey(window, GLFW_KEY_S))
	{
		pos += DIAGSPEED * CamDir["south"] * CamDir["west"] * deltaT;
		out = eulerWM(pos, glm::vec3(0.0f, yawAngles["south-west"], 0.0f));
	}

	return out;
}