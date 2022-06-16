#include <GLFW/glfw3.h>

void createSpring(int springRes, int cylinderRes, float springRadius, float cylinderRadius, float coilDistance)
{
    float pi = M_PI;
    float var = (coilDistance + 2 * cylinderRadius) / 2;

    for (int i = 0; i < springRes; i++)
    {
        for (int j = 0; j < cylinderRes; j++)
        {
            glm::vec4 cylinderVector = glm::mat4(glm::quat(glm::vec3(0, 0, 2 * j * pi / cylinderRes))) * glm::vec4(cylinderRadius, 0, 1, 1);
            glm::vec4 vert = glm::mat4(glm::quat(glm::vec3(0, 2 * i * pi / 18, 0))) * (glm::vec4(0, var, 0, 1) * float(i) * springRadius * cylinderVector);

            M3_vertices.push_back(vert.x);
            M3_vertices.push_back(vert.y);
            M3_vertices.push_back(vert.z);
        }
    }
}